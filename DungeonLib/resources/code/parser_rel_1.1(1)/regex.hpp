// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// function to determine if a string matches a regular expression

/* expressions may contain:
$ (dollar sign)     match end of string
. (period):         match any single character
* (asterisk):       match zero or more of the preceding expression
+ (plus):           match one or more of the preceding expression
? (question mark):  match zero or one of the preceding expression
\c (backslash):     match the character 'c' exactly (escape sequence)
\xdd:               match the character with the two digit hexidecimal value of dd
{count}             match the specified number of the preceding expression
{min,}              match at least the specified number of the preceding expression
{min,max}           match between min and max of the preceding expression
r1|r2               match either r1 or r2.  '|' has the lowest precedence, except for /
r1/r2 (slash)       match r1 only if followed by r2.  r2 is not consumed.
                    '/' has the lowest precedence, and binds right to left. for
                    example: given r1/r2/r3, r1 will only match if r2 follows r1,
                    and r2 will only match if r3 follows r2.  neither r2 or r3 are consumed.
() (parentheses)    used to group expression together.
[] (brackets):      match any character in brackets (or any not in brackets,
                    if the first character is '^').  ranges can be specified,
                    such as: 0-9, a-z, or A-Za-z.  A closing bracket (']')
                    may be in the set if it is the first character after
                    the opening bracket ('[') or the '^' character.  A minus
                    sign ('-') may be in the set of it is the first character
                    after the opening bracket ('[') or the '^' character or
                    the last character before the closing bracket.  A carat
                    ('^') may be in the set if it is not the first character.

bracketed expression may also contain the following character classes:
[:alpha:]   -- any letter, as determined by isalpha().
[:lower:]   -- any lowercase letter, as determined by islower()
[:upper:]   -- any uppercase letter, as determined by isupper()
[:alnum:]   -- any letter or digit, as determined by isalnum()
[:digit:]   -- any digit, as determined by isdigit()
[:xdigit:]  -- any hexidecimal digit, as determined by isxdigit()
[:space:]   -- any whitespace (except \n or \r)
[:cntrl:]   -- any control character, as determined by iscntrl()
[:print:]   -- any printable character, as determined by isprint()
[:graph:]   -- any printable character, as determined by isgraph()
[:punct:]   -- any punctuation, as determined by ispunct(). note that this
               can accept different characters those defined in PUNCT_CHARS.

note that because of character classes, to accept both '[' and ':' characters
within a bracketed expression, do not place them adjacent to each other with
the '[' first.  place the ':' first or separate them with other characters.

any character not listed above must match exactly.

suffix expressions (?, *, +, {}) cannot immediately follow another suffix
expression, but they can immediately follow a closing parenthesis.

*/

#ifndef REGEX_HPP
#define REGEX_HPP

#include "all.hpp"
#include <vector>
#include <iostream>
#include "nfa.hpp"
#include "array.hpp"

namespace REGEX {

const int MAX_EDGES = 2; // no node will ever need more than this number of edges

template<class Element>
class EdgesArray : public Array<Element, MAX_EDGES> {

public:
    EdgesArray() {}
};

// exception class
DEFINE_EXCEPTION(bad_regex, "bad regular expression");

enum TransType {NORMAL, LLAMDA, RANGE, CLASS, END_OF_STRING};

enum ClassType {ALPHA, LOWER, UPPER, ALNUM, DIGIT, XDIGIT, SPACE, CNTRL, PRINT, GRAPH, PUNCT};

enum NodeFlag {
    NO_FLAG,
    SAVE_START_POSITION,        // count var. has index of in marker vector
    SAVE_END_POSITION,          // count var. has index of in marker vector
    SAVE_STRING_POSITION,
    RESTORE_STRING_POSITION     // count var. has index of node w/ saved pointer
};

struct TransInfo {
    TransInfo() {}
    TransInfo(char minimum, char maximum) : min(minimum), max(maximum) {}
    TransInfo(ClassType class_type) : cl(class_type) {}
    unsigned char min, max;
    ClassType cl;
};

// transaction stub classes for overload resolution
struct CNormal      {CNormal      () {} } const Normal;
struct CRange       {CRange       () {} } const Range;
struct CClass       {CClass       () {} } const Class;
struct CEndOfString {CEndOfString () {} } const EndOfString;

struct Trans {
    Trans() : type(LLAMDA), negate(false), consume(false) {}
    Trans(CNormal, char trans_char, bool neg = false, bool con = true) : trans(trans_char), type(NORMAL), negate(neg), consume(con) {}
    Trans(CRange, char first, char last, bool neg = false, bool con = true) : type(RANGE), info(int((unsigned char) first), int((unsigned char) last)), negate(neg), consume(con) {}
    Trans(CClass, ClassType class_type, bool neg = false, bool con = true) : type(CLASS), info(class_type), negate(neg), consume(con) {}
    Trans(CEndOfString) : type(END_OF_STRING), negate(false), consume(false) {}
    char trans;
    TransType type;
    TransInfo info;
    bool negate, consume;
};

inline std::ostream& operator<<(std::ostream& out, const Trans& trans)
{
    switch (trans.type)
    {
    case NORMAL:
        out << "'" << trans.trans << "'";
        break;

    case LLAMDA:
        out << "(NULL)";
        break;

    default:
        out << "Unknown Type: " << trans.type;
        break;
    }

    return out;
}

typedef std::pair<const char*, const char*> StringMarker;
typedef std::vector<StringMarker> Markers;

struct InputType;

#if CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS
typedef NFA::Edge<Trans> Edge;
typedef EdgesArray<Edge> Edges;
typedef NFA::Node<Trans, InputType, EdgesArray> Node;
typedef std::vector<Node> Nodes;
typedef NFA::Nfa<Trans, InputType, EdgesArray, std::vector> Nfa;
#else
typedef NFA::Edge<Trans> Edge;
typedef EdgesArray<Edge> Edges;
typedef NFA::Node<Trans, InputType, Edges> Node;
typedef std::vector<Node> Nodes;
typedef NFA::Nfa<Trans, InputType, Edges, Nodes> Nfa;
#endif

struct InputType {
    typedef const char* SavedPosType;

    struct NodeInfoType {
        NodeInfoType() : flag(NO_FLAG) {}

        NodeInfoType(NodeFlag aFlag, int aMin = 0, int aMax = 0) : flag(aFlag), min(aMin), max(aMax) {}

        NodeFlag flag;
        int index, min, max;
        const char* saved_pos;
    };

    InputType(const char* aInput, Markers* aMarkers) : p(aInput), markers(aMarkers) {}

    void savePos(SavedPosType& pos) {pos = p;}
    void restorePos(SavedPosType& pos) {p = pos;}
    bool match(Trans& trans);
    void callback(Nfa& nfa, NodeInfoType& info);

    SavedPosType p;
    Markers* markers;
};

// function to return true if a given string matches a given regular expression.
// if pnfa is not null, the function will return the nfa created for the
// expression so the expression can be retested without having to recreate the
// nfa.  if successful, match contains the number of characters in the matched
// substring
bool regex(const char* ex, const char* str, int& matched, Markers* markers = NULL, Nfa* pnfa = NULL);

// function to return to if a given string matches a given nfa for a regular
// expression.
bool regex(Nfa& nfa, const char* str, int& matched, Markers* markers = NULL);

} // namespace REGEX

#endif // REGEX_HPP
