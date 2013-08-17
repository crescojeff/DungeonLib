// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// miscellaneous declarations

#ifndef ALL_HPP
#define ALL_HPP

#include <exception>
#include "portability.hpp"

// macro for defining exceptions; str is assumed to be static const
#define DEFINE_EXCEPTION(name, str) \
    class name : public std::exception { \
    public: \
        virtual const char* what() const throw() {return str;} \
    }

#endif // ALL_HPP
