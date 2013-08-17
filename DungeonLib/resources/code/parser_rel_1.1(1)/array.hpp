// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// class wrapper for c array type

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "all.hpp"
#include <cstring>
#include <stdexcept>

template<class Element, int MaxSize>
class Array {

public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef Element* pointer;
    typedef const Element* const_pointer;
    typedef Element& reference;
    typedef const Element& const_reference;
    typedef Element value_type;
    typedef pointer iterator;
    typedef const_pointer const_iterator;

#if TYPE_OF_ITERATOR_DECLARATION_TEMPLATES_TO_USE == 0
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
#elif TYPE_OF_ITERATOR_DECLARATION_TEMPLATES_TO_USE == 1
    typedef std::reverse_iterator<const_iterator, value_type, const_reference, const_pointer, difference_type> const_reverse_iterator;
    typedef std::reverse_iterator<iterator, value_type, reference, pointer, difference_type> reverse_iterator;
#endif

    Array() : count(0) {}
    Array(const Array& arr) : count(arr.count) {::memcpy(array, arr.array, count * sizeof(Element));}

    Array& operator=(const Array& arr)
        {if (&arr != this) {count = arr.count; ::memcpy(array, arr.array, count * sizeof(Element));} return *this;}

    iterator begin() {return array;}
    const_iterator begin() const {return array;}
    iterator end() {return &array[count];}
    const_iterator end() const {return &array[count];}
    reverse_iterator rbegin() {return (reverse_iterator(end()));}
    const_reverse_iterator rbegin() const {return (const_reverse_iterator(end()));}
    reverse_iterator rend() {return (reverse_iterator(begin()));}
    const_reverse_iterator rend() const {return (const_reverse_iterator(begin()));}
    size_type size() const {return count;}
    size_type max_size() const {return MaxSize;}
    bool empty() const {return count == 0;}
    reference at(size_type idx) {if (idx >= size()) throw std::out_of_range(); return array[idx];}
    const_reference at(size_type idx) const {if (idx >= size()) throw std::out_of_range(); return array[idx];}
    reference operator[](size_type idx) {return array[idx];}
    const_reference operator[](size_type idx) const {return array[idx];}
    reference front() {return array[0];}
    const_reference front() const {return array[0];}
    reference back() {return array[count - 1];}
    const_reference back() const {return array[count - 1];}
    void push_back(const_reference e) {array[count++] = e;}
    void pop_back() {--count;}
    void clear() {count = 0;}
    pointer ptr() {return array;}
    const_pointer ptr() const {return array;}

private:
    Element array[MaxSize];
    int count;
};

template<class Element, int MaxSize>
inline bool operator==(const Array<Element, MaxSize>& a1, const Array<Element, MaxSize>& a2)
{
    return (a1.size() != a2.size()) ? false : ::memcmp(a1.ptr(), a2.ptr(), a1.size()) == 0;
}

template<class Element, int MaxSize>
inline bool operator!=(const Array<Element, MaxSize>& a1, const Array<Element, MaxSize>& a2)
{
    return (a1.size() != a2.size()) ? true : ::memcmp(a1.ptr(), a2.ptr(), a1.size()) != 0;
}

#endif // ARRAY_HPP
