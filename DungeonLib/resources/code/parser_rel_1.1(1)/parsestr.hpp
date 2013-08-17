// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// header file to define the parse strings used to build the parser's NFA

#ifndef PARSESTR_HPP
#define PARSESTR_HPP

#include "all.hpp"

// The following parse strings define the grammer of the language.
// The strings can be non-deterministic. All codes are case-sensitive.
// The strings are encoded as pairs, a code & part-of-speech (pos) type.
// Spaces can be used for clarity and will be ignored.
// Codes:
//   p - following pos must be present: pX
//   o - following pos is optional: oX
//   * - match zero or more of the following pos: *X
//   + - match one or more of the following pos: +X
//   | - separator for alternate choices: +X | *Y | pZ
//  () - groups multiple pos together: (pXoY), *(pX | pY)
//  {} - same as *(): {pX | oY}
//  [] - same as +(): [pX | oY]
//  <> - match exact word: <tell, class>  class is optional
//  // - match regular expression: /[0-9]+/number/. use two slashes to represent
//       a slash within the expression. number is an integer number used to
//       identify the expression used to match the string. it and its final slash
//       are optional and default to 0.
//
// Parts-of-Speech:
//   a - any
//   A - any, including gibberish
//   g - gibberish
//   r - article
//   d - adverb
//   j - adjective
//   c - conjunction
//   p - preposition
//   v - verb
//   n - noun (any)
//   o - pronoun
//   P - proper noun
//   m - match word exact (not used directly, see <> above)
//   x - regular expression. used to match numbers, codes, etc.
//
//   Punctuation occurring after a code is treated as an exact match of that punctuation,
//   for example: p! p.
//
// Parts-of-Speech are followed by a colon, an optional command, and an optional code number.
// The code number indicates what to do with the word then it is correctly parsered.
// The default function number is 0.
// For example: pn:0, <Tell>:1, o<North, Noun>:A56, /[0-9]+/5/, o/[//a-z]*/
// Note that function will be called in the reversed order of parsed words.
// Commands:
//   A - Add        - Word is added to parsed words.  can only be used with m (<word>) transitons
//   C - Command    - Executes command. Both parser code and pos are ignored (except for precedence).
//   N - None       - no command. Same as omitting the command.
//


// This string defines the order of importance for transition types in cases of ambiguity
extern const char TransOrder[];

// This string defines the order of importance for commands in cases of ambiguity
extern const char CommandOrder[];

// each parse string is considered an alternate path: s[0] | s[1] | s[2] ...
extern const char* const parse_strings[];

#endif // PARSESTR_HPP
