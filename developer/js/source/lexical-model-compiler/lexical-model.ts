/**
 * Interfaces and constants used by the lexical model compiler. These target
 * the LMLayer's internal worker code, so we provide those definitions too.
 */

interface LexicalModelDeclaration {
  readonly format: 'trie-1.0'|'fst-foma-1.0'|'custom-1.0',
  //... metadata ...
}

/**
 * Keyman 14.0+ word breaker specification:
 *
 * Can support all old word breaking specification,
 * but can also be extended with options.
 *
 * @since 14.0
 */
interface WordBreakerSpec {
  readonly use: SimpleWordBreakerSpec;
  /**
   * If present, joins words that were split by the word breaker
   * together at the given strings. e.g.,
   *
   *    joinWordsAt: ['-'] // to keep hyphenated items together
   *
   * @since 14.0
   */
  readonly joinWordsAt?: string[];

  /**
   * Overrides word splitting behaviour for certain scripts.
   * For example, specifing that spaces break words in certain South-East
   * Asian scripts that otherwise do not use spaces.
   *
   * @since 14.0
   */
  readonly overrideScriptDefaults?: OverrideScriptDefaults;
}

/**
 * Simplified word breaker specification.
 *
 * @since 11.0
 */
type SimpleWordBreakerSpec = 'default' | 'ascii' | WordBreakingFunction;

/**
 * When configuring the default word breaker,
 * this allows you to override the default behaviour for the script.
 *
 * There is currently only one option:
 *
 * 'break-words-at-spaces'
 * : some some South-East Asian scripts conventionally do not use spaces to
 * break words. These scripts are:
 *
 *   * Burmese
 *   * Khmer
 *   * Thai
 *   * Laos
 *   * Katakana
 *
 * For these scripts, the default word breaker opts to break at **every**
 * letter/syllable/ideograph.  Some languages that use these scripts DO use
 * spaces. Enable 'break-words-at-spaces' to override the unwanted, default
 * behaviour for these scripts (breaking at every grapheme cluster).
 *
 * @since 14.0
 */
type OverrideScriptDefaults = 'break-words-at-spaces';


interface LexicalModelSource extends LexicalModelDeclaration {
  readonly sources: Array<string>;
  /**
   * The name of the type to instantiate (without parameters) as the base object for a custom predictive model.
   */
  readonly rootClass?: string

  /**
   * Which word breaker to use. Choose from:
   *
   *  - 'default' -- breaks according to Unicode UAX #29 §4.1 Default Word
   *    Boundary Specification, which works well for *most* languages.
   *  - 'ascii' -- a very simple word breaker, for demonstration purposes only.
   *  - word breaking function -- provide your own function that breaks words.
   *  - class-based word-breaker - may be supported in the future.
   */
  readonly wordBreaker?: WordBreakerSpec | SimpleWordBreakerSpec;

  /**
   * How to simplify words, to convert them into simplifired search keys
   * This often involves removing accents, lowercasing, etc.
   */
  readonly searchTermToKey?: (term: string) => string;

  /**
   * Punctuation and spacing suggested by the model.
   *
   * @see LexicalModelPunctuation
   */
  readonly punctuation?: LexicalModelPunctuation;
}

interface LexicalModelCompiled extends LexicalModelDeclaration {
  readonly id: string;
}
