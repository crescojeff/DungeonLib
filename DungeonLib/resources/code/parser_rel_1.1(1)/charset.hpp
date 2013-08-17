// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// header to define a character set for comparisions

#ifndef CHARSET_HPP
#define CHARSET_HPP

#include "all.hpp"
#include <cstring>

class CharSet {
    const char* const chrs;

public:
    explicit CharSet(const char c[]) : chrs(c) {}
    int pos(char c) const {return strchr(chrs, c) - chrs;}
    bool contains(char c) const {return strchr(chrs, c) != NULL;}
    char operator[](int pos) const {return chrs[pos];}
};

#endif // CHARSET_HPP
