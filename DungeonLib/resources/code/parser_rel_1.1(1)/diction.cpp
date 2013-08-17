// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// code file for dictionary class

#include "all.hpp"
#include <iostream>
#include <algorithm>
#include "diction.hpp"

using namespace std;

// local class used to find a word in the dictionary. Assumes code is not AllLetters
struct match_words {
    size_t max_len; // numbers of letters the words will be trucated to before the comparison
    string s1, s2;  // strings used in compare defined here to avoid a lot allocation/deallocation

    match_words(int sl, Dictionary::SigCode code, const string& s) : s1(s)
    {
        max_len = sl;
        if (code == Dictionary::siNoAmbiguity)
        {
            max_len = max(s1.size(), max_len);
        }
        else
        {
            if (s1.size() > max_len)
                s1.erase(max_len, s1.size());
        }
    }

    bool operator() (const Dictionary::value_type& e)
    {
        s2 = e.first;
        if (s2.size() > max_len)
            s2.erase(max_len, s2.size());
        return s1 == s2;
    }
};

Dictionary::Dictionary (const WordRec vocab[], int sl, SigCode co) : sig_letters(sl), sig_code(co)
{
    for (const WordRec* p = vocab; p->code != wcNone; ++p)
        insert(p);
}

string Dictionary::lowercase(const std::string& s)
{
    string t(s);
    for (string::iterator i = t.begin(); i != t.end(); ++i)
        *i = tolower(*i);
    return t;
}

void Dictionary::insert(const WordRec* r)
{
    // convert word to lowercase to simplify searching
    string s(lowercase(r->word));

    // check if word already exists within dictionary
    WordMapType::iterator i = WordMap.find(s);
    if (i != WordMap.end())
    {
        // duplicate word exists.  if codes match, just add in new classes & info
        if (r->code == i->second.code)
        {
            i->second.classes |= r->classes;
            i->second.info |= r->info;
        }
        else
            throw duplicate_word_found();
    }
    else
        WordMap[s] = ElementType(r->code, r->classes, r->info);
}

Dictionary::const_iterator Dictionary::find(const string& word) const
{
    const_iterator i;
    string s(lowercase(word));

    switch (sig_code)
    {
    case siAllLetters:
        i = WordMap.find(s);
        break;

    case siNoAmbiguity:
    {
        i = find_if(WordMap.begin(), WordMap.end(), match_words(sig_letters, sig_code, s));

        // check for an exact match
        if (i != end() && s != i->first)
        {
            // check next map entry for a match, indicating ambiguity
            const_iterator j = i, k;
            if (i != end() && ++j != end())
            {
                k = j;
                ++k;
                j = find_if(j, k, match_words(sig_letters, sig_code, s));
                if (j != k)
                    i = end();
            }
        }
        break;
    }

    default:
        i = find_if(begin(), end(), match_words(sig_letters, sig_code, s));
    }

    return i;
}

namespace
{

struct match_code {
    const WordCode code;
    match_code(WordCode c) : code(c) {}
    bool operator()(const Dictionary::value_type& v)
    {
        return v.second.code == code;
    }
};

}

Dictionary::const_iterator Dictionary::find(WordCode code) const
{
    return find_if(begin(), end(), match_code(code));
}

void Dictionary::print_word(const value_type& e)
{
    cout << "\"" << e.first << "\", " << e.second.code << ", " << hex
        << (int) e.second.classes << dec << "\n";
}

void Dictionary::print_all_words(void) const
{
    for_each(begin(), end(), print_word);
}

