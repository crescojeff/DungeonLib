// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// defines the nfa class used by the parser

#ifndef PNFA_HPP
#define PNFA_HPP

#include "all.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "vocab.hpp"
#include "parsestr.hpp"
#include "nfa.hpp"
#include "dfa.hpp"

namespace pnfa {

// Define type for "extact-match" transition
struct mTransRec {
    WordCode code;
    WordClasses classes;
};

// Define type for regular expression transition
struct xTransRec {
    const char *start, *end;
    int code;
};

// Define type for transition extended information
union TransInfo {
    mTransRec m_trans;
    xTransRec x_trans;
};

// Define type of transition element
struct Trans {
    char trans;
    char command;
    const char *start, *end; // word to add if command is 'A'
    int func_code;
    TransInfo info;

    explicit Trans(char pTrans = '\0') :
        trans(pTrans), command('N'), start(NULL), end(NULL), func_code(0) {}

    Trans(WordCode pCode, WordClasses pClasses) :
        trans('m'), command('N'), start(NULL), end(NULL), func_code(0)
        {info.m_trans.code = pCode; info.m_trans.classes = pClasses;}

    Trans(const char* pStart, const char* pEnd, int pCode) :
        trans('x'), command('N'), start(NULL), end(NULL), func_code(0)
        {info.x_trans.start = pStart; info.x_trans.end = pEnd; info.x_trans.code = pCode;}
};

inline bool operator<(const Trans& t1, const Trans& t2)
{
    if (t1.trans != t2.trans)
    {
        return strchr(TransOrder, t1.trans) < strchr(TransOrder, t2.trans);
    }
    else if (t1.trans == 'm')
    {
        if (t1.info.m_trans.code != t2.info.m_trans.code)
            return t1.info.m_trans.code < t2.info.m_trans.code;
        else if (t1.info.m_trans.classes != t2.info.m_trans.classes)
            return t1.info.m_trans.classes < t2.info.m_trans.classes;
    }
    else if (t1.trans == 'x')
    {
        if (t1.info.x_trans.start != t2.info.x_trans.start)
            return (unsigned long) t1.info.x_trans.start < (unsigned long) t2.info.x_trans.start;
        else if (t1.info.x_trans.end != t2.info.x_trans.end)
            return (unsigned long) t1.info.x_trans.end < (unsigned long) t2.info.x_trans.end;
        if (t1.info.x_trans.code != t2.info.x_trans.code)
            return t1.info.x_trans.code < t2.info.x_trans.code;
    }

    if (t1.command != t2.command)
        return strchr(CommandOrder, t1.command) < strchr(CommandOrder, t2.command);
    else if (t1.command == 'A')
    {
        if (t1.start != t2.start)
            return t1.start < t2.start;
    }

    if (t1.func_code != t2.func_code)
        return t1.func_code < t2.func_code;

    return false;
}

inline bool operator==(const Trans& t1, const Trans& t2)
{
    return !(t1 < t2) && !(t2 < t1);
}

inline bool operator!=(const Trans& t1, const Trans& t2) {return !operator==(t1, t2);}

std::ostream& operator<<(std::ostream& out, const Trans& trans);

struct InputType;

#if CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS
typedef NFA::Edge<Trans> Edge;
typedef std::vector<Edge> Edges;
typedef NFA::Node<Trans, InputType> Node;
typedef std::vector<Node> Nodes;
typedef NFA::Nfa<Trans, InputType> Nfa;
typedef DFA::Dfa<Trans, InputType> Dfa;
#else
typedef NFA::Edge<Trans> Edge;
typedef std::vector<Edge> Edges;
typedef NFA::Node<Trans, InputType, Edges> Node;
typedef std::vector<Node> Nodes;
typedef NFA::Nfa<Trans, InputType, Edges, Nodes> Nfa;
typedef DFA::Dfa<Trans, InputType, Edges, Nodes> Dfa;
#endif

struct InputType {
    typedef std::string::const_iterator SavedPosType;

    struct NodeInfoType {
        NodeInfoType() {}
    };

    InputType() {}

    void savePos(SavedPosType& pos) {pos = p;}
    void restorePos(SavedPosType& pos) {p = pos;}
    bool match(Trans& trans);
    void callback(Nfa& nfa, NodeInfoType& info);

    SavedPosType p;
};

// set to hold an NFA's alphabet (a list of all transition types used in the NFA)
typedef std::set<Trans> TransList;

// array of DFAs
typedef std::vector<Dfa> DfaList;

} // namespace pnfa

#endif // PNFA_HPP
