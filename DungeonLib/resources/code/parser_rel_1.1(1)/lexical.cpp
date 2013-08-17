// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// lexical analyzer code file

#include "all.hpp"
#include <string>
#include "lexical.hpp"
#include "vocab.hpp"
#include "charset.hpp"

using namespace std;

namespace
{
    // set of punctuation characters
    const CharSet punct_set(Punctuation);
}

bool LexicalAnalyzer::GetNextLine(void)
{
    line = "";
    int c = cin.get();

    while (c != '\n')
    {
        line += char(c);
        c = cin.get();
    }

    Reset();

    return line == "";
}

bool LexicalAnalyzer::GetNextWord(std::string& str, bool& is_punc)
{
    char c;

    str = "";
    is_punc = false;

    skip_whitespace();

    if (pline == line.end())
        return true;

    for(;;)
    {
        if (pline == line.end())
            break;

        c = *pline++;

        // check if c is a punctuation character
        if (punct_set.contains(c))
        {
            if (str == "")
            {
                str = c;
                is_punc = true;
                break;
            }
            else // see if punctuation is embedded in word or at the end
            {
                const string::const_iterator saved_pline = --pline;
                string s;

                while (pline != line.end() && punct_set.contains(*pline))
                    s += *pline++;

                if (pline == line.end() || isspace(*pline))
                {
                    pline = saved_pline;
                    break;
                }
                else
                {
                    str += s;
                    continue;
                }
            }
        }

        // check if c is white space
        else if (isspace(c))
            break;

        // add character to string
        else
            str += c;
    }

    return false;
}

bool LexicalAnalyzer::GetNextWord(string& word, WordCode& code, WordClasses& classes,
                                  const Dictionary::ElementType*& entry)
{
    bool eol;
    bool punc;

    entry = NULL;
    eol = GetNextWord(word, punc);

    if (eol)
        return true;

    else if (punc)
    {
        code = -punct_set.pos(word[0]) - 1;
        classes = cmPunctuation;
    }
    else if (word != "")
    {
        Dictionary::const_iterator i = dictionary.find(word);
        if (i != dictionary.end())
        {
            code = i->second.code;
            classes = i->second.classes;
            entry = &(i->second);
        }
        else
        {
            code = wcGibberish;
            classes = cmNone;
        }
    }

    return false;
}

