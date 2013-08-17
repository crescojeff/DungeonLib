// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// Vocabulary header file

#ifndef VOCAB_HPP
#define VOCAB_HPP

#include "all.hpp"

// This string defines the set of puncuation characters accepted by the
// lexical analyzer and parser. Under most circumstances punctuation is
// ignored. When being parsed, punctuation is represented as a negative code
// cooresponding to its position in the string starting with 1 (-1, -2, etc.).
// The class type is ctPunctuation.
// Puncuation is ignored unless explicitly referenced in a parse string.
#define PUNCT_CHARS "!#$%&:;,.?\""
extern const char Punctuation[];

// word class type (parts-of-speech)
enum WordClass {clNone, clAdverb, clAdjective, clArticle, clConjunction, clPreposition,
  clVerb, clNoun, clPronoun, clProperNoun, clPunctuation, clRegExCode,
  NumberOfClasses
};

// array of WordClass strings in the same order as WordClass
const char* const WordClassNames[] = {"none", "adverb", "adjective", "article", "conjunction",
  "preposition", "verb", "noun", "pronoun", "propernoun", "punctuation", "reg-ex-code"};

// bit mask type to hold all the classes a word belongs to
typedef unsigned long WordClasses;

// word class masks
const WordClasses cmNone = 0;
const WordClasses cmAdverb = 1 << clAdverb;
const WordClasses cmAdjective = 1 << clAdjective;
const WordClasses cmArticle = 1 << clArticle;
const WordClasses cmConjunction = 1 << clConjunction;
const WordClasses cmPreposition = 1 << clPreposition;
const WordClasses cmVerb = 1 << clVerb;
const WordClasses cmNoun = 1 << clNoun;
const WordClasses cmPronoun = 1 << clPronoun;
const WordClasses cmProperNoun = 1 << clProperNoun;
const WordClasses cmPunctuation = 1 << clPunctuation;
const WordClasses cmRegExCode = 1 << clRegExCode;

typedef int WordCode;

// type used to store addition information on words in the dictionary
typedef unsigned long WordInfo;

// constants of WordInfo type

// all words
const WordInfo wiNone = 0x00000000ul;

// pronouns
const WordInfo wiObjectPronoun  = 1ul <<  0;    // pronoun is an "object" pronoun (it, that, etc.)
const WordInfo wiMalePronoun    = 1ul <<  1;    // pronoun is a "male" pronoun (he, him, etc.)
const WordInfo wiFemalePronoun  = 1ul <<  2;    // pronoun is a "female" pronoun (she, her, etc.)
const WordInfo wiAllPronoun     = 1ul <<  3;    // pronoun is an "all" pronoun (they, them, etc.)
const WordInfo wiDontResolve    = 1ul <<  4;    // don't replace pronoun with an equated noun

// nouns and pronouns
const WordInfo wiObjectNoun     = 1ul <<  5;    // noun can be represented by an "object" pronoun
const WordInfo wiMaleNoun       = 1ul <<  6;    // noun can be represented by an "male" pronoun
const WordInfo wiFemaleNoun     = 1ul <<  7;    // noun can be represented by an "female" pronoun


// word translation code type
enum {
wcNone,

wcGibberish,  // used to indicate a word not in the vocabulary

wcRegEx,      // regular expression

// Articles
wcThe, wcA, wcAn,

// Adverbs
wcQuickly, wcQuietly, wcVery,

// Adjectives
wcRed, wcBlue, wcGreen, wcLarge, wcSmall,

// Conjunctions
wcAnd, wcOr, wcThen,

// Prepositions
wcTo, wcOf, wcIn, wcUnder, wcAt,

// Verbs
wcGo, wcLook, wcGet, wcDrop, wcTell, wcSay,
wcDial,

// Nouns
wcNorth, wcSouth, wcEast, wcWest,
wcNortheast,
wcTree, wcHouse, wcSword,
wcFred, wcBob, wcJane, wcRobot,
wcPhone,

// Pronouns
wcHe, wcHim, wcShe, wcHer, wcIt, wcWho, wcWhat,

NumberOfCodes
};

// define structure used in the vocabulary array to translate a word in
// the form of a text string into an internal word code and class. Each
// bit position in the class indicates the word type whose value is equal
// to the bit position. Setting a bit indicate the word belong to that class.
struct WordRec {
  const char* word;
  WordCode code;
  WordClasses classes;
  WordInfo info;
};

// The vocabulary array used to initialize the dictionary
extern const WordRec Vocabulary[];

// This function returns true if the given class is in the bit-set of classes
bool in_class(WordClasses classes, WordClass c);

// This function returns the first class type it finds in the bit-set of classes
WordClass WordClasses_to_WordClass (WordClasses c);

#endif // VOCAB_HPP
