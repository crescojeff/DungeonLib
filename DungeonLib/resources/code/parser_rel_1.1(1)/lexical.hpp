// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// lexical analyzer header file

#ifndef LEXICAL_HPP
#define LEXICAL_HPP

#include "all.hpp"
#include <iostream>
#include <string>
#include <list>
#include "vocab.hpp"
#include "diction.hpp"
#include "charset.hpp"

class LexicalAnalyzer {
    Dictionary& dictionary;

    // current line of text and position marker
    std::string line;
    std::string::const_iterator pline;

    // function to get next word from the input.  returns true if end-of-line
    bool GetNextWord(std::string& str, bool& is_punc);

    void skip_whitespace(void)
    {
        while (pline != line.end() && isspace(*pline))
            ++pline;
    }

public:
    LexicalAnalyzer (Dictionary& D) : dictionary(D) {}
    ~LexicalAnalyzer (void) {}

    // function to reset position mark to the start of the line
    void Reset(void) {pline = line.begin();}

    // function to save the current state of the lexer.
    std::string::const_iterator SaveState(void) const {return pline;}

    // function to restore the state of the lexer.
    void RestoreState(std::string::const_iterator pstring) {pline = pstring;}

    // function to retrieve the next line of text from input.  returns true if line is empty.
    bool GetNextLine(void);

    // function to get next word from the current line.  returns true if end-of-line
    bool GetNextWord(std::string& word, WordCode& code, WordClasses& classes,
        const Dictionary::ElementType*& entry);

    // function to return if the current line is empty
    bool LineIsEmpty(void) const {return line == "";}

    // function to copy the current line from the current position to the end
    std::string CopyLine(bool skipws = true)
    {
        if (skipws)
            skip_whitespace();
        const std::string::const_iterator p = line.end();
        return std::string(pline, p);
    }
};

#endif // LEXICAL_HPP
