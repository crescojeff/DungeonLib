// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

#include "all.hpp"
#include <cctype>
#include <cstring>
#include <iostream>
#include <stack>
#include "regex.hpp"

using namespace std;

namespace REGEX {

namespace {

#define ADD_NODE() (nfa.addNode())
#define ADD_EDGE(from, to, trans) (nfa.addEdge((from), (to), (trans)))

const Trans E; // Null (epsilon) transition

void compile_character_class(const char*& ex, Nfa& nfa, int& last, int final, bool negate)
{
    struct {const char* name; ClassType cl;}
    static const classes[] = {
        {"alpha", ALPHA}, {"lower", LOWER}, {"upper", UPPER},
        {"alnum", ALNUM}, {"digit", DIGIT}, {"xdigit", XDIGIT},
        {"space", SPACE}, {"cntrl", CNTRL}, {"print", PRINT},
        {"graph", GRAPH}, {"punct", PUNCT}};

    ex += 2;

    // find class by name
    for (int i = 0; i < int(sizeof(classes) / sizeof(classes[0])); ++i)
    {
        const int len = strlen(classes[i].name);
        if (strncmp(classes[i].name, ex, len) == 0 &&
            ex[len] == ':' && ex[len + 1] == ']')
        {
            int next = nfa.nodes.size();
            ADD_NODE();

            if (!negate)
            {
                ADD_NODE();
                ADD_EDGE(last, next, E);
                ADD_EDGE(next + 1, final, E);
                last = next++;
            }

            ADD_EDGE(last, next, Trans(Class, classes[i].cl, negate, !negate));

            if (negate)
                last = next;

            ex += len + 2;
            return;
        }
    }

    throw bad_regex(); //unknown character class
}

void compile_bracket_expression(const char*& ex, Nfa& nfa, int& initial, int& final)
{
    const int new_final = nfa.nodes.size() + 1;
    const int new_initial = new_final - 1;
    int last = new_initial;

    ADD_NODE();
    ADD_NODE();
    ADD_EDGE(final, new_initial, E);

    // check for negation character
    const bool negate = *(++ex) == '^';

    if (negate)
        ++ex;

    const char* const first = ex;

    for (;;)
    {
        // check for character class
        if (ex[0] == '[' && ex[1] == ':')
        {
            compile_character_class(ex, nfa, last, new_final, negate);
            continue;
        }

        switch (*ex)
        {
        case '\0':
            throw bad_regex(); // missing ']'

        case ']':
            if (ex != first)
            {
                if (negate)
                {
                    ADD_EDGE(last, new_final, E);
                    nfa.nodes[last].edges[0].trans.consume = true; // consume char. at last match
                }
                initial = new_initial;
                final = new_final;
                ++ex;
                return;
            }

            // fall through

        default:
        {
            int next = nfa.nodes.size();
            ADD_NODE();

            if (!negate)
            {
                ADD_NODE();
                ADD_EDGE(last, next, E);
                ADD_EDGE(next + 1, new_final, E);
                last = next++;
            }

            // check for range expression
            if (ex[1] == '-' && ex[2] != ']')
            {
                ADD_EDGE(last, next, Trans(Range, ex[0], ex[2], negate, !negate));
                ex += 3;
            }
            else
                ADD_EDGE(last, next, Trans(Normal, *ex++, negate, !negate));

            if (negate)
                last = next;
        }
        } // switch (*ex)
    }
}

inline void compile_character(char c, Nfa& nfa, int& initial, int& final)
{
    const int new_final = nfa.nodes.size() + 1;
    const int new_initial = new_final - 1;
    ADD_NODE();
    ADD_NODE();
    ADD_EDGE(final, new_initial, E);
    ADD_EDGE(new_initial, new_final, Trans(Normal, c));
    initial = new_initial;
    final = new_final;
}

void compile1(const char*& ex, Nfa& nfa, Markers* markers, int depth)
{
    // create initial node
    nfa.nodes.push_back(Node());

    int initial = nfa.nodes.size() - 1;
    int final = initial;
    int group_initial = initial;

    while (*ex != '\0')
    {
        // check for base expressions
        switch (*ex)
        {
        case '*': // "bad" characters
        case '+':
        case '?':
        case ']':
        case '}':
            throw bad_regex(); // bad character in expression

        case '[':
            compile_bracket_expression(ex, nfa, initial, final);
            break;

        case '(':
        {
            int index = 0;
            if (markers)
            {
                index = markers->size();
                markers->push_back(StringMarker(NULL, NULL));
            }

            ++ex;
            initial = final + 1;
            compile1(ex, nfa, markers, depth + 1);
            ADD_NODE();
            final = nfa.nodes.size() - 1;
            ADD_EDGE(initial - 1, initial, E);
            ADD_EDGE(final - 1, final, E);
            if (markers)
            {
                nfa.nodes[initial].info.flag = SAVE_START_POSITION;
                nfa.nodes[initial].info.index = index;
                nfa.nodes[final].info.flag = SAVE_END_POSITION;
                nfa.nodes[final].info.index = index;
            }
            break;
        }

        case ')':
            ++ex;
            if (depth > 0)
                return;
            else
                throw bad_regex(); // ')' without a matching '('

        case '\\':
            // check for hex. constant
            if (ex[1] == 'x')
            {
                char b[3] = {0};

                if (!isxdigit((b[0] = ex[2])) || !isxdigit((b[1] = ex[3])))
                    throw bad_regex(); // bad character in hexidecimal constant

                const char c = char((unsigned char) strtoul(b, NULL, 16));
                compile_character(c, nfa, initial, final);
                ex += 4;
                break;
            }

            // match following character (escape sequence)
            ++ex;
            // fall through

        default: // match character
            compile_character(*ex++, nfa, initial, final);
            break;
        }

        // check for suffix expressions
        switch (*ex)
        {
        case '*': // match zero or more
            nfa.xFormZeroOrMore(initial, final);
            ++ex;
            break;

        case '+': // match one or more
            nfa.xFormOneOrMore(initial, final);
            ++ex;
            break;

        case '?': // match zero or one
            nfa.xFormZeroOrOne(initial, final);
            ++ex;
            break;

        case '{': // count, min, or min & max
        {
            enum {UNKNOWN, COUNT, MIN, MIN_AND_MAX} type = UNKNOWN;
            char* s;
            ++ex;
            const int min = strtoul(ex, &s, 10);
            if (s == ex)
                throw bad_regex(); // bad character in decimal constant

            int max = 0;
            ex = s + 1;

            // check for "count" suffix
            if (*s == '}')
                type = COUNT;
            else if (*s == ',')
            {
                // check for max. constant
                if (*ex != '}')
                {
                    max = strtoul(ex, &s, 10);
                    if (s == ex)
                        throw bad_regex(); // bad character in decimal constant
                    if (max < min)
                        throw bad_regex(); // bad range in {min,max} expression
                    type = MIN_AND_MAX;
                    ex = s + 1;
                }
                else
                {
                    type = MIN;
                    ++ex;
                }
            }
            else
                throw bad_regex(); // missing ',' after decimal constant

            switch (type)
            {
                case COUNT: nfa.xFormCount(initial, final, min); break;
                case MIN: nfa.xFormMin(initial, final, min); break;
                case MIN_AND_MAX: nfa.xFormMinAndMax(initial, final, min, max); break;
                default: throw bad_regex(); // internal error
            }
        }

        default:
            break;
        }

        // check for binary expressions
        switch (*ex)
        {
        case '|':
        {
            ++ex;
            const int new_initial = final + 1;
            compile1(ex, nfa, markers, depth);
            const int new_final = nfa.nodes.size() - 1;
            nfa.xFormOr(group_initial, final, new_initial, new_final);
            break;
        }

        case '/':
        {
            ++ex;
            const int new_initial = final + 1;
            compile1(ex, nfa, markers, depth);

            const int i = nfa.nodes.size();
            ADD_NODE(); // node to save string position
            ADD_NODE(); // node to restore string position
            ADD_NODE(); // new final node;

            // node indices
            const int save_node_index = i;
            const int restore_node_index = i + 1;
            const int new_final_node_index = i + 2;

            // add save and restore flags
            Node& save_node = nfa.nodes[save_node_index];
            save_node.info.flag = SAVE_STRING_POSITION;
            Node& restore_node = nfa.nodes[restore_node_index];
            restore_node.info.flag = RESTORE_STRING_POSITION;
            restore_node.info.index = save_node_index;

            // add llamda transitions
            ADD_EDGE(final, save_node_index, E);
            ADD_EDGE(save_node_index, new_initial, E);
            ADD_EDGE(i - 1, restore_node_index, E);
            ADD_EDGE(restore_node_index, new_final_node_index, E);

            final = new_final_node_index;
        }

        default:
            break;
        }
    }

    if (depth != 0)
        throw bad_regex(); // '(' without a matching ')'
}

// function to create an nfa from a regular expression string.
// extra nodes are used to avoid llamda cycles which could
// lead to an infinite loop.
void compile(const char*& ex, Nfa& nfa, Markers* markers, int depth = 0)
{
    compile1(ex, nfa, markers, depth);
    nfa.nodes.back().final = true;
}

bool trans_on_class(ClassType cl, int c)
{
    switch (cl)
    {
    case ALPHA: return isalpha(c) != 0;
    case LOWER: return islower(c) != 0;
    case UPPER: return isupper(c) != 0;
    case ALNUM: return isalnum(c) != 0;
    case DIGIT: return isdigit(c) != 0;
    case XDIGIT: return isxdigit(c) != 0;
    case SPACE: return isspace(c) != 0;
    case CNTRL: return iscntrl(c) != 0;
    case PRINT: return isprint(c) != 0;
    case GRAPH: return isgraph(c) != 0;
    case PUNCT: return ispunct(c) != 0;
    default:
        throw bad_regex(); // unknown class name
    }
}

bool process(const char*& str, Nfa& nfa, Markers* markers)
{
    InputType input(str, markers);
    const bool result = nfa.traverse(input);
    str = input.p;
    return result;
}

} // namespace

void InputType::callback(Nfa& nfa, NodeInfoType& info)
{
    switch (info.flag)
    {
    case NO_FLAG:
        break;

    case SAVE_START_POSITION:
        if (markers)
            (*markers)[info.index].first = p;
        break;

    case SAVE_END_POSITION:
        if (markers)
            (*markers)[info.index].second = p;
        break;

    case SAVE_STRING_POSITION:
        info.saved_pos = p;
        break;

    case RESTORE_STRING_POSITION:
        p = nfa.nodes[info.index].info.saved_pos;
        break;
    }
}

bool InputType::match(Trans& trans)
{
    bool can_trans = true;
    bool negate = trans.negate;
    TransType type = trans.type;

    switch (type)
    {
    case NORMAL:
        can_trans = *p == trans.trans;
        break;

    case LLAMDA:
        break;

    case RANGE:
    {
        const unsigned char c = *p;
        can_trans = c >= trans.info.min && c <= trans.info.max;
        break;
    }

    case CLASS:
        can_trans = trans_on_class(trans.info.cl, *p);
        break;

    case END_OF_STRING:
        can_trans = *p == '\0';
        type = LLAMDA;
        break;

    default:
        throw bad_regex(); // unknown transition type
    }

    if (negate)
        can_trans = !can_trans;

    // a null character can only transition on a Llamda
    if (*p == '\0' && type != LLAMDA)
        can_trans = false;

    if (can_trans && trans.consume)
        ++p;

    return can_trans;
}

bool regex(const char* ex, const char* str, int& matched, Markers* markers, Nfa* pnfa)
{
    Nfa infa;

    Nfa& nfa = (pnfa) ? *pnfa : infa;

    nfa.clear();

    // reverse a few entries to speed of compile process
    // for small expressions
    nfa.nodes.reserve(64);

    if (markers)
        markers->clear();
    compile(ex, nfa, markers);

    const char* start = str;
    const bool result = process(str, nfa, markers);
    if (result)
        matched = str - start;
    return result;
}

bool regex(Nfa& nfa, const char* str, int& matched, Markers* markers)
{
    const char* start = str;
    const bool result = process(str, nfa, markers);
    if (result)
        matched = str - start;
    return result;
}

} // namespace rex

