import LexicalModelCompiler from '../dist/lexical-model-compiler/lexical-model-compiler';
import {assert} from 'chai';
import 'mocha';

import path = require('path');
import { compileModelSourceCode } from './helpers';


describe('LexicalModelCompiler', function () {
  describe('specifying custom methods: applyCasing and searchTermToKey', function () {
    const MODEL_ID = 'example.qaa.trivial';
    const PATH = path.join(__dirname, 'fixtures', MODEL_ID)

    describe('should compile applyCasing and searchTermToKey into the generated code', function () {
      let casingWithPrependedSymbols: CasingFunction = function(casingName: CasingEnum, text: string, defaultApplyCasing: CasingFunction) {
        switch(casingName) {
          // Use of symbols, and of the `casingName` name, exist to serve as regex targets.
          case 'lower':
            return '-' + defaultApplyCasing(casingName, text);
          case 'upper':
            return '+' + defaultApplyCasing(casingName, text);
          case 'initial':
            return '^' + defaultApplyCasing(casingName, text);
          default:
            return defaultApplyCasing(casingName, text);
        }
      };

      it('variant 1:  applyCasing prepends symbols, searchTermToKey removes them', function() {
        let compiler = new LexicalModelCompiler;
        let code = compiler.generateLexicalModelCode(MODEL_ID, {
          format: 'trie-1.0',
          sources: ['wordlist.tsv'],
          languageUsesCasing: true, // applyCasing won't appear without this!
          applyCasing: casingWithPrependedSymbols,
          // Parameter name `rawSearchTerm` selected for uniqueness, regex matching test target.
          searchTermToKey: function(rawSearchTerm: string, applyCasing: CasingFunction) {
            // Strips any applyCasing symbols ('-', '+', '^') out of the compiled Trie.
            // We should be able to test that they do _not_ occur within internal nodes of the Trie.
            return applyCasing('lower', rawSearchTerm)
              .replace(/^-/, '')
              .replace(/^\+/, '')
              .replace(/^\^/, '');
          }
        }, PATH) as string;
  
        // Check that the methods actually made into the code; use our custom parameter names:
        assert.match(code, /casingName/);
        assert.match(code, /rawSearchTerm/);
  
        // Check that the prepended symbols from applyCasing also appear in the code:
        assert.match(code, /'-'/);
        assert.match(code, /'\+'/);
        assert.match(code, /'\^'/);
  
        let modelInitIndex = code.indexOf('LMLayerWorker.loadModel');
        let modelInitCode = code.substring(modelInitIndex);
        // Chop off the IIFE terminator.  Not strictly necessary, but whatever.
        modelInitCode = modelInitCode.substring(0, modelInitCode.lastIndexOf('\n})();'))
  
        // Check that the prepended symbols from applyCasing do not appear in the Trie:
        assert.notMatch(modelInitCode, /['"]-['"]/);
        assert.notMatch(modelInitCode, /['"]\+['"]/);
        assert.notMatch(modelInitCode, /['"]\^['"]/);
  
        // Make sure it compiles!
        let compilation = compileModelSourceCode(code);
        assert.isFalse(compilation.hasSyntaxError);
        assert.isNotNull(compilation.exportedModel);
      });

      it('variant 2:  applyCasing prepends symbols, searchTermToKey keeps them', function() {
        let compiler = new LexicalModelCompiler;
        let code = compiler.generateLexicalModelCode(MODEL_ID, {
          format: 'trie-1.0',
          sources: ['wordlist.tsv'],
          languageUsesCasing: true, // applyCasing won't appear without this!
          applyCasing: casingWithPrependedSymbols,
          // Parameter name `rawSearchTerm` selected for uniqueness, regex matching test target.
          searchTermToKey: function(rawSearchTerm: string, applyCasing: CasingFunction) {
            // Strips any applyCasing symbols ('-', '+', '^') out of the compiled Trie.
            // We should be able to test that they do _not_ occur within internal nodes of the Trie.
            return applyCasing('lower', rawSearchTerm);
          }
        }, PATH) as string;
  
        // Check that the methods actually made into the code; use our custom parameter names:
        assert.match(code, /casingName/);
        assert.match(code, /rawSearchTerm/);
  
        // Check that the prepended symbols from applyCasing also appear in the code:
        assert.match(code, /'-'/);
        assert.match(code, /'\+'/);
        assert.match(code, /'\^'/);
  
        let modelInitIndex = code.indexOf('LMLayerWorker.loadModel');
        let modelInitCode = code.substring(modelInitIndex);
        // Chop off the IIFE terminator.  Not strictly necessary, but whatever.
        modelInitCode = modelInitCode.substring(0, modelInitCode.lastIndexOf('\n})();'))
  
        // Check that the prepended lowercase "-" DOES appear within the Trie, as keying
        // does not remove it in this variant:
        assert.match(modelInitCode, /['"]-['"]/);
  
        // Make sure it compiles!
        let compilation = compileModelSourceCode(code);
        assert.isFalse(compilation.hasSyntaxError);
        assert.isNotNull(compilation.exportedModel);
      });
    });
  });
});
