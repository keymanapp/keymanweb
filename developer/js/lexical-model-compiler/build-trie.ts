/**
 * A word list is an array of pairs: the concrete word form itself, followed by
 * a non-negative count.
 */
type WordList = [string, number][];

/**
 * Returns a data structure suitable for use by the wordlist model.
 *
 * @param sourceFiles an array of the CONTENTS of source files
 *
 * @return a data structure that will be used internally by the wordlist
 *         implemention. Currently this is an array of [wordlist, count] pairs.
 */
export function createWordListDataStructure(sourceFiles: string[]): string {
  // NOTE: this generates a simple array of word forms --- not a trie!
  // In the future, this function may construct a true trie data structure,
  // but this is not yet implemented.
  let contents = sourceFiles.join('\n');
  return JSON.stringify(parseWordList(contents));
}

/**
 * Returns a data structure that can be loaded by the TrieModel.
 *
 * It implements a **weighted** trie, whose indices (paths down the trie) are
 * generated by a search key, and not concrete wordforms themselves.
 *
 * @param sourceFiles an array of source files that will be read to generate the trie.
 */
export function createTrieDataStructure(sourceFiles: string[], searchTermToKey?: (wf: string) => string): string {
  let wordlist =  parseWordList(sourceFiles.join('\n'));
  let trie = Trie.buildTrie(wordlist, searchTermToKey as Trie.Wordform2Key);
  return JSON.stringify(trie);
}

/**
 * Reads a tab-separated values file into a word list.
 *
 * Format specification:
 *
 *  - the file is a UTF-8 encoded text file
 *  - new lines are either LF or CRLF
 *  - the file either consists of a comment or an entry
 *  - comment lines MUST start with the '#' character on the very first column
 *  - entries are one to three columns, separated by the (horizontal) tab
 *    character
 *  - column 1 (REQUIRED): the wordform: can have any character except tab, CR,
 *    LF. Surrounding whitespace characters are trimmed.
 *  - column 2 (optional): the count: a non-negative integer specifying how many
 *    times this entry has appeared in the corpus. Blank means 'indeterminate'
 *  - column 3 (optional): comment: an informative comment, ignored by the tool.
 */
export function parseWordList(contents: string): WordList {
  // Supports LF or CRLF line terminators.
  const NEWLINE_SEPARATOR = /\u000d?\u000a/;
  const TAB = "\t";
  // TODO: format validation.
  let lines = contents.split(NEWLINE_SEPARATOR);

  let result: WordList = [];
  for (let line of lines) {
    if (line.startsWith('#') || line === "") {
      continue; // skip comments and empty lines
    }
    let [wordform, countText, _comment] = line.split(TAB);
    // Clean the word form.
    // TODO: what happens if we get duplicate forms?
    wordform = wordform.normalize('NFC').trim();
    countText = (countText || '').trim();
    let count = parseInt(countText, 10);

    // When parsing a decimal integer fails (e.g., blank or something else):
    if (!isFinite(count)) {
      // TODO: is this the right thing to do?
      // Treat it like a hapax legonmenom -- it exist, but only once.
      count = 1;
    }
    result.push([wordform, count]);
  }
  return result;
}

namespace Trie {
  /**
   * An **opaque** type for a string that is exclusively used as a search key in
   * the trie. There should be a function that converts arbitrary strings
   * (queries) and converts them into a standard search key for a given language
   * model.
   *
   * Fun fact: This opaque type has ALREADY saved my bacon and found a bug!
   */
  type SearchKey = string & { _: 'SearchKey'};

  /**
   * A function that converts a string (word form or query) into a search key
   * (secretly, this is also a string).
   */
  export interface Wordform2Key {
    (wordform: string): SearchKey;
  }

  // The following trie implementation has been (heavily) derived from trie-ing
  // by Conrad Irwin.
  //
  // trie-ing is distributed under the terms of the MIT license, reproduced here:
  //
  //   The MIT License
  //   Copyright (c) 2015-2017 Conrad Irwin <conrad.irwin@gmail.com>
  //   Copyright (c) 2011 Marc Campbell <marc.e.campbell@gmail.com>
  //
  //   Permission is hereby granted, free of charge, to any person obtaining a copy
  //   of this software and associated documentation files (the "Software"), to deal
  //   in the Software without restriction, including without limitation the rights
  //   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  //   copies of the Software, and to permit persons to whom the Software is
  //   furnished to do so, subject to the following conditions:
  //
  //   The above copyright notice and this permission notice shall be included in
  //   all copies or substantial portions of the Software.
  //
  //   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  //   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  //   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  //   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  //   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  //   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  //   THE SOFTWARE.
  //
  // See: https://github.com/ConradIrwin/trie-ing/blob/df55d7af7068d357829db9e0a7faa8a38add1d1d/LICENSE

  /**
   * An entry in the prefix trie. The matched word is "content".
   */
  interface Entry {
    content: string;
    key: SearchKey;
    weight: number;
  }

  /**
   * The trie is made up of nodes. A node can be EITHER an internal node (whose
   * only children are other nodes) OR a leaf, which actually contains the word
   * form entries.
   */
  type Node = InternalNode | Leaf;

  /**
   * An internal node.
   */
  interface InternalNode {
    type: 'internal';
    weight: number;
    // TODO: As an optimization, "values" can be a single string!
    values: string[];
    children: { [codeunit: string]: Node };
    unsorted?: true;
  }

  /**
   * A leaf node.
   */
  interface Leaf {
    type: 'leaf';
    weight: number;
    entries: Entry[];
    unsorted?: true;
  }

  /**
   * A sentinel value for when an internal node has contents and requires an
   * "internal" leaf. That is, this internal node has content. Instead of placing
   * entries as children in an internal node, a "fake" leaf is created, and its
   * key is this special internal value.
   *
   * The value is a valid Unicode BMP code point, but it is a "non-character".
   * Unicode will never assign semantics to these characters, as they are
   * intended to be used internally as sentinel values.
   */
  const INTERNAL_VALUE = '\uFDD0';

  /**
   * Builds a trie from a word list.
   *
   * @param wordlist    The wordlist with non-negative weights.
   * @param keyFunction Function that converts word forms into indexed search keys
   * @returns The root node as a JSON-serialiable object.
   */
  export function buildTrie(wordlist: WordList, keyFunction: Wordform2Key = defaultWordform2Key): object {
    return new Trie(keyFunction).buildFromWordList(wordlist).root;
  }

  /**
   * Wrapper class for the trie and its nodes and wordform to search
   */
  class Trie {
    readonly root = createRootNode();
    toKey: Wordform2Key;
    constructor(wordform2key: Wordform2Key) {
      this.toKey = wordform2key;
    }

    /**
     * Populates the trie with the contents of an entire wordlist.
     * @param words a list of word and count pairs.
     */
    buildFromWordList(words: WordList): Trie {
      for (let [wordform, weight] of words) {
        let key = this.toKey(wordform);
        addUnsorted(this.root, { key, weight, content: wordform }, 0);
      }
      sortTrie(this.root);
      return this;
    }
  }

  // "Constructors"
  function createRootNode(): Node {
    return {
      type: 'leaf',
      weight: 0,
      entries: []
    };
  }

  // Implement Trie creation.

  /**
   * Adds an entry to the trie.
   *
   * Note that the trie will likely be unsorted after the add occurs. Before
   * performing a lookup on the trie, use call sortTrie() on the root note!
   *
   * @param node Which node should the entry be added to?
   * @param entry the wordform/weight/key to add to the trie
   * @param index the index in the key and also the trie depth. Should be set to
   *              zero when adding onto the root node of the trie.
   */
  function addUnsorted(node: Node, entry: Entry, index: number = 0) {
    // Each node stores the MAXIMUM weight out of all of its decesdents, to
    // enable a greedy search through the trie.
    node.weight = Math.max(node.weight, entry.weight);

    // When should a leaf become an interior node?
    // When it already has a value, but the key of the current value is longer
    // than the prefix.
    if (node.type === 'leaf' && index < entry.key.length && node.entries.length >= 1) {
      convertLeafToInternalNode(node, index);
    }

    if (node.type === 'leaf') {
      // The key matches this leaf node, so add yet another entry.
      addItemToLeaf(node, entry);
    } else {
      // Push the node down to a lower node.
      addItemToInternalNode(node, entry, index);
    }

    node.unsorted = true;
  }

  /**
   * Adds an item to the internal node at a given depth.
   * @param item
   * @param index
   */
  function addItemToInternalNode(node: InternalNode, item: Entry, index: number) {
    let char = item.key[index];
    if (!node.children[char]) {
      node.children[char] = createRootNode();
      node.values.push(char);
    }
    addUnsorted(node.children[char], item, index + 1);
  }

  function addItemToLeaf(leaf: Leaf, item: Entry) {
    leaf.entries.push(item);
  }

  /**
   * Mutates the given Leaf to turn it into an InternalNode.
   *
   * NOTE: the node passed in will be DESTRUCTIVELY CHANGED into a different
   * type when passed into this function!
   *
   * @param depth depth of the trie at this level.
   */
  function convertLeafToInternalNode(leaf: Leaf, depth: number): void {
    let entries = leaf.entries;

    // Alias the current node, as the desired type.
    let internal = (<unknown> leaf) as InternalNode;
    internal.type = 'internal';

    delete leaf.entries;
    internal.values = [];
    internal.children = {};

    // Convert the old values array into the format for interior nodes.
    for (let item of entries) {
      let char: string;
      if (depth < item.key.length) {
        char = item.key[depth];
      } else {
        char = INTERNAL_VALUE;
      }

      if (!internal.children[char]) {
        internal.children[char] = createRootNode();
        internal.values.push(char);
      }
      addUnsorted(internal.children[char], item, depth + 1);
    }

    internal.unsorted = true;
  }

  /**
   * Recursively sort the trie, in descending order of weight.
   * @param node any node in the trie
   */
  function sortTrie(node: Node) {
    if (node.type === 'leaf') {
      if (!node.unsorted) {
        return;
      }

      node.entries.sort(function (a, b) { return b.weight - a.weight; });
    } else {
      // We MUST recurse and sort children before returning.
      for (let char of node.values) {
        sortTrie(node.children[char]);
      }

      if (!node.unsorted) {
        return;
      }

      node.values.sort((a, b) => {
        return node.children[b].weight - node.children[a].weight;
      });
    }

    delete node.unsorted;
  }

  /**
   * Converts word forms in into an indexable form. It does this by converting
   * the string to uppercase and trying to remove diacritical marks.
   *
   * This is a very naïve implementation, that I've only though to work on
   * languages that use the Latin script. Even then, some Latin-based
   * orthographies use code points that, under NFD normalization, do NOT
   * decompose into an ASCII letter and a combining diacritical mark (e.g.,
   * SENĆOŦEN).
   *
   * Use this only in early iterations of the model. For a production lexical
   * model, you SHOULD write/generate your own key function, tailored to your
   * language.
   */
  function defaultWordform2Key(wordform: string): SearchKey {
    // Use this pattern to remove common diacritical marks.
    // See: https://www.compart.com/en/unicode/block/U+0300
    const COMBINING_DIACRITICAL_MARKS = /[\u0300-\u036f]/g;
    return wordform
      .normalize('NFD')
      .toLowerCase()
      // remove diacritical marks.
      .replace(COMBINING_DIACRITICAL_MARKS, '') as SearchKey;
  }
}
