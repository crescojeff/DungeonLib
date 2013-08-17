// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// parser nfa code file

#include "all.hpp"
#include "pnfa.hpp"

using namespace std;

namespace pnfa {

namespace {

const Trans E;  // null transition

} // unnamed namespace

ostream& operator<<(ostream& out, const Trans& trans)
{
    if (trans != E)
    {
        out << trans.trans;
        if (trans.command == 'N')
            out << ", cmd: " << trans.command;
        if (trans.func_code != 0)
            out << ", func: " << trans.func_code;
        if (trans.trans == 'm')
        {
            if (trans.command != 'C')
            {
                out << ", code: " << trans.info.m_trans.code;
                out << ", classes: " << hex << trans.info.m_trans.classes << dec;
            }
        }
    }
    else
        out << "NULL";

    return out;
}


} // namespace pnfa
