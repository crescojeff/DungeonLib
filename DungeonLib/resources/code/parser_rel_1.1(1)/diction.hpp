// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// header file for dictionary class

#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include "all.hpp"
#include <string>
#include <map>
#include "vocab.hpp"

// exception classes
DEFINE_EXCEPTION(duplicate_word_found, "duplicate word found in dictionary");

class Dictionary {
public:
    // Codes to modify how the dictionary uses its given number of significant letters (sl)
    // to compares words
    enum SigCode
    {
        siNone,         // sl letters are significant
        siAllLetters,   // all letters are significant (sl is ignored)
        siNoAmbiguity   // the dictionary will accept as few letters (>= sl) that avoid ambiguity
    };

    // dictionary element type
    struct ElementType {
        WordCode code;
        WordClasses classes;
        WordInfo info;

        ElementType(WordCode co = wcNone, WordClasses cl = cmNone, WordInfo in = wiNone) :
            code(co), classes(cl), info(in) {}
    };

protected:
    typedef std::map<std::string, ElementType> WordMapType;

public:
    typedef WordMapType::value_type value_type;
    typedef WordMapType::const_iterator const_iterator;

protected:
    WordMapType WordMap;

    // The maximum number of letters in a word that the dictionary will check
    // when deciding if a word is in its vocabulary.
    const int sig_letters;
    const SigCode sig_code;

    static std::string lowercase(const std::string& s); // converts a string to lowercase
    void insert(const WordRec *r);

public:
    Dictionary(const WordRec vocab[], int sl, SigCode co = siNone);
    ~Dictionary(void) {}

    const_iterator begin(void) const {return WordMap.begin();}
    const_iterator end(void) const {return WordMap.end();}
    const_iterator find(const std::string& word) const;
    bool find(const std::string& word, WordCode& code, WordClasses& classes, WordInfo& info) const;
    const_iterator find(WordCode code) const;

    //Testing functions
    static void print_word(const value_type& e);
    void print_all_words(void) const;
};

inline bool Dictionary::find(const std::string& word, WordCode& code, WordClasses& classes,
                             WordInfo& info) const
{
    const_iterator i = find(word);
    if (i != end())
    {
        code = i->second.code;
        classes = i->second.classes;
        info = i->second.info;
        return true;
    }
    else
        return false;
}

#endif // DICTIONARY_HPP
