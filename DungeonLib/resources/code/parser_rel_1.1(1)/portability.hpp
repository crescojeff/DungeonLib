// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// defines portability macros

#ifndef PORTABILITY_HPP
#define PORTABILITY_HPP

// define macro for compiler type
#if defined(__GNUC__)
#define COMPILER_IS_GCC     1
#elif defined(_MSC_VER)
#define COMPILER_IS_VC      1
#endif // define macro for compiler type

// define macro to calculate version
#define VERSION(MAJOR, MINOR, PATCHLEVEL) ((MAJOR) * 10000 + (MINOR) * 100 + (PATCHLEVEL))

// define macro for compiler version
#if COMPILER_IS_GCC
#define COMPILER_VERSION VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#endif // define macro for compiler version

// define macros for what compiler can handle
#define CAN_HANDLE_INLINE_STATIC_CONSTANT_INITIALIZATION                    0
#define CAN_HANDLE_PARTIAL_TEMPLATE_SPECIALIZATION_FOR_CONSTANTS            0
#define CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS                             0
#define CAN_HANDLE_CALLING_PARENT_TEMPLATE_CLASS_MEMBERS                    0
#define TYPE_OF_ITERATOR_DECLARATION_TEMPLATES_TO_USE                       0

// define macros for specific compilers
#if COMPILER_IS_GCC
#if COMPILER_VERSION >= VERSION(3, 1, 0)
#undef CAN_HANDLE_INLINE_STATIC_CONSTANT_INITIALIZATION
#undef CAN_HANDLE_PARTIAL_TEMPLATE_SPECIALIZATION_FOR_CONSTANTS
#undef CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS
#undef CAN_HANDLE_CALLING_PARENT_TEMPLATE_CLASS_MEMBERS

#define CAN_HANDLE_INLINE_STATIC_CONSTANT_INITIALIZATION                    1
#define CAN_HANDLE_PARTIAL_TEMPLATE_SPECIALIZATION_FOR_CONSTANTS            1
#define CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS                             1
#define CAN_HANDLE_CALLING_PARENT_TEMPLATE_CLASS_MEMBERS                    1
#endif // COMPILER_IS_GCC

#endif // define macros for specific compilers

#ifdef COMPILER_IS_VC

#undef TYPE_OF_ITERATOR_DECLARATION_TEMPLATES_TO_USE
#define TYPE_OF_ITERATOR_DECLARATION_TEMPLATES_TO_USE                       1


#pragma warning(disable: 4786 4503)
#include "xutility"

namespace std
{
template<class _Ty>
inline const _Ty& max(const _Ty& _X, const _Ty& _Y)
{
    return (_X < _Y ? _Y : _X);
}

template<class _Ty>
inline const _Ty& min(const _Ty& _X, const _Ty& _Y)
{
    return (_Y < _X ? _Y : _X);
}
}
#endif

// macro used to define static constants within classes
#if CAN_HANDLE_INLINE_STATIC_CONSTANT_INITIALIZATION
#define DECLARE_STATIC_CONST(TYPE, NAME, VALUE) static const TYPE NAME = (VALUE)
#define DEFINE_STATIC_CONST(TYPE, NAME, VALUE) const TYPE NAME
#else
#define DECLARE_STATIC_CONST(TYPE, NAME, VALUE) enum { NAME = TYPE(VALUE) }
#define DEFINE_STATIC_CONST(TYPE, NAME, VALUE)
#endif

// macro used to define template template parameter
#if CAN_HANDLE_TEMPLATE_TEMPLATE_PARAMETERS
#define TEMPLATE_PARAM(T) template<class> class T
#else
#define TEMPLATE_PARAM(T) class T
#endif

#endif // PORTABILITY_H

