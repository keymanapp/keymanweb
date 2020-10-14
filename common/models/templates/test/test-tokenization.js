/*
 * Unit tests for common utility functions/methods.
 */

var assert = require('chai').assert;
var models = require('../').models;
var wordBreakers = require('@keymanapp/models-wordbreakers').wordBreakers;

describe.only('Tokenization functions', function() {
  describe('tokenize', function() {
    it('tokenizes English using defaults, pre-whitespace caret', function() {
      let context = {
        left: "The quick brown fox",
        right: " jumped over the lazy dog",
        startOfBuffer: true,
        endOfBuffer: true
      };

      let tokenization = models.tokenize(wordBreakers.default, context);

      let expectedResult = {
        left: ['The', 'quick', 'brown', 'fox'],
        right: ['jumped', 'over', 'the', 'lazy', 'dog'],
        caretSplitsToken: false
      };

      assert.deepEqual(tokenization, expectedResult);
    });

    it('tokenizes English using defaults, post-whitespace caret', function() {
      let context = {
        left: "The quick brown fox ",
        right: "jumped over the lazy dog",
        startOfBuffer: true,
        endOfBuffer: true
      };

      let tokenization = models.tokenize(wordBreakers.default, context);

      // Technically, we're editing the start of the first token on the right
      // when in this context.
      let expectedResult = {
        left: ['The', 'quick', 'brown', 'fox', ''],
        right: ['jumped', 'over', 'the', 'lazy', 'dog'],
        caretSplitsToken: true
      };

      assert.deepEqual(tokenization, expectedResult);
    });

    it('tokenizes English using defaults, splitting caret', function() {
      let context = {
        left: "The quick brown fox jum",
        right: "ped over the lazy dog",
        startOfBuffer: true,
        endOfBuffer: true
      };

      let tokenization = models.tokenize(wordBreakers.default, context);

      let expectedResult = {
        left: ['The', 'quick', 'brown', 'fox', 'jum'],
        right: ['ped', 'over', 'the', 'lazy', 'dog'],
        caretSplitsToken: true
      };

      assert.deepEqual(tokenization, expectedResult);
    });

    // For the next few tests:  a mocked wordbreaker for Khmer, a language
    // without whitespace between words.
    let mockedKhmerBreaker = function(text) {
      // Step 1:  Build constants for spans that a real wordbreaker would return.
      let srok = { // Khmer romanization of 'ស្រុក'
        text: 'ស្រុក',
        start: 0,
        end: 5,
        length: 5
      };

      let sro = { // Khmer romanization of 'ស្រុ'
        text: 'ស្រុ',
        start: 0,
        end: 4,
        length: 4
      };

      let k = { // Not the proper Khmer romanization; 'k' used here for easier readability.
        text: 'ក',
        start: 0,
        end: 1,
        length: 1
      };

      let khmer = { // Khmer romanization of 'ខ្មែរ'
        text: 'ខ្មែរ',
        start: 0,
        end: 5,
        length: 5
      }

      // Step 2: Allow shifting a defined 'constant' span without mutating the definition.
      let shiftIndex = function(span, delta) {
        // Avoid mutating the parameter!
        shiftedSpan = {
          text: span.text,
          start: span.start + delta,
          end: span.end + delta,
          length: span.length
        };

        return shiftedSpan;
      }

      // Step 3: Define return values for the cases we expect to need mocking.
      switch(text) {
        case 'ស្រុ':
          return [sro];
        case 'ក':
          return [k];
        case 'ស្រុក':
          return [srok];
        case 'ខ្មែរ':
          return [khmer];
        case 'ស្រុកខ្មែរ':
          return [srok, shiftIndex(khmer, 5)]; // array of the two.
        case 'កខ្មែរ':
          // I'd admittedly be at least somewhat surprised if a real wordbreaker got this 
          // and similar situations perfectly right... but at least it gives us what
          // we need for a test.
          return [k, shiftIndex(khmer, 1)];
        default:
          throw "Dummying error - no return value specified for \"" + text + "\"!";
      }
    }

    it('tokenizes Khmer using mocked wordbreaker, caret between words', function() {
      // The two words:
      // - ស្រុក - 'land'
      // - ខ្មែរ - 'Khmer'
      // Translation:  Cambodia (informal)

      let context = {
        left: "ស្រុក",
        right: "ខ្មែរ",
        startOfBuffer: true,
        endOfBuffer: true
      };

      let tokenization = models.tokenize(mockedKhmerBreaker, context);

      let expectedResult = {
        left: ['ស្រុក'],
        right: ['ខ្មែរ'],
        caretSplitsToken: false
      };

      assert.deepEqual(tokenization, expectedResult);
    });

    it('tokenizes Khmer using mocked wordbreaker, caret within word', function() {
      // The two words:
      // - ស្រុក - 'land'
      // - ខ្មែរ - 'Khmer'
      // Translation:  Cambodia (informal), lit:  "Khmer land" / "land of [the] Khmer"

      let context = {
        left: "ស្រុ",
        right: "កខ្មែរ",
        startOfBuffer: true,
        endOfBuffer: true
      };

      let tokenization = models.tokenize(mockedKhmerBreaker, context);

      let expectedResult = {
        left: ['ស្រុ'],
        right: ['ក', 'ខ្មែរ'],
        caretSplitsToken: true
      };

      assert.deepEqual(tokenization, expectedResult);
    });
  });
});