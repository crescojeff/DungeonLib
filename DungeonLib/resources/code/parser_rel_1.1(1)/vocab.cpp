// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// code file for vocabulary data

#include "all.hpp"
#include "vocab.hpp"

const char Punctuation[] = PUNCT_CHARS;

// This function returns true if the given class is in the bit-set of classes
bool in_class(WordClasses classes, WordClass c)
{
    return bool((classes & (1 << c)) != 0);
}

// This function returns the first class type it finds in the bit-set of classes
WordClass WordClasses_to_WordClass (WordClasses c)
{
    int i = 0;

    while (c && !(c & 1))
    {
        c >>= 1;
        i++;
    }
    return WordClass(i);
}

// Define the known vocabulary. Synonyms should have the same code.
// A word can exist in more than one class group.
const WordRec Vocabulary[] = {
// articles
{"the", wcThe, cmArticle, wiNone},
{"a", wcA, cmArticle, wiNone},
{"an", wcAn, cmArticle, wiNone},

// adverbs
{"quickly", wcQuickly, cmAdverb, wiNone},
{"quietly", wcQuietly, cmAdverb, wiNone},
{"very", wcVery, cmAdverb, wiNone},

// adjectives
{"red", wcRed, cmAdjective, wiNone},
{"blue", wcBlue, cmAdjective, wiNone},
{"green", wcGreen, cmAdjective, wiNone},
{"large", wcLarge, cmAdjective, wiNone},
{"small", wcSmall, cmAdjective | cmAdverb, wiNone},

// conjunctions
{"and", wcAnd, cmConjunction, wiNone},
{"or", wcOr, cmConjunction, wiNone},
{"then", wcThen, cmConjunction, wiNone},

// prepositions
{"to", wcTo, cmPreposition, wiNone},
{"of", wcOf, cmPreposition, wiNone},
{"in", wcIn, cmPreposition, wiNone},
{"under", wcUnder, cmPreposition, wiNone},
{"at", wcAt, cmPreposition, wiNone},

// verbs
{"go", wcGo, cmVerb, wiNone},
{"walk", wcGo, cmVerb, wiNone},
{"look", wcLook, cmVerb, wiNone},
{"examine", wcLook, cmVerb, wiNone},
{"get", wcGet, cmVerb, wiNone},
{"take", wcGet, cmVerb, wiNone},
{"drop", wcDrop, cmVerb, wiNone},
{"tell", wcTell, cmVerb, wiNone},
{"say", wcSay, cmVerb, wiNone},
{"dial", wcDial, cmVerb, wiNone},

// nouns
{"north", wcNorth, cmNoun | cmAdjective, wiObjectNoun},
{"south", wcSouth, cmNoun | cmAdjective, wiObjectNoun},
{"east", wcEast, cmNoun | cmAdjective, wiObjectNoun},
{"west", wcWest, cmNoun | cmAdjective, wiObjectNoun},
{"northeast", wcNortheast, cmNoun | cmAdjective, wiObjectNoun},
{"tree", wcTree, cmNoun, wiObjectNoun},
{"house", wcHouse, cmNoun, wiObjectNoun},
{"sword", wcSword, cmNoun, wiObjectNoun},
{"phone", wcPhone, cmNoun, wiObjectNoun},
{"telephone", wcPhone, cmNoun, wiObjectNoun},

// proper nouns
{"fred", wcFred, cmProperNoun, wiMaleNoun},
{"bob", wcBob, cmProperNoun, wiMaleNoun},
{"jane", wcJane, cmProperNoun, wiFemaleNoun},
{"robot", wcRobot, cmProperNoun, wiMaleNoun | wiFemaleNoun | wiObjectNoun},

// pronouns
{"he", wcHe, cmPronoun, wiMalePronoun},
{"him", wcHim, cmPronoun, wiMalePronoun},
{"she", wcShe, cmPronoun, wiFemalePronoun},
{"her", wcHer, cmPronoun, wiFemalePronoun},
{"it", wcIt, cmPronoun, wiObjectPronoun},
{"who", wcWho, cmPronoun, wiMalePronoun | wiFemalePronoun},
{"what", wcWhat, cmPronoun, wiDontResolve},

{"", wcNone, 0, wiNone}  // end of list
};

