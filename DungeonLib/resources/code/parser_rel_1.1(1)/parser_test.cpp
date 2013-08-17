// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

#include "all.hpp"
#include <iostream>
#include <ctime>
#include <utility>
#include "parser.hpp"

using namespace std;

#define FAILED make_pair(false, __LINE__)

namespace {

string getstr(void)
{
    string line = "";
    int c = cin.get();

    while (c != '\n')
    {
        line += char(c);
        c = cin.get();
    }

    return line;
}

}

pair<bool, int> test_parser()
{
    Sentences S;
    Dictionary D(Vocabulary, 0, Dictionary::siNoAmbiguity);
    LexicalAnalyzer L(D);
    Parser P(L, D, parse_strings);

    for (;;)
    {
        //P.SetMalePronoun(Word(D, wcBob));
        //P.SetObjectPronoun(Word(D, wcTree));

        if (P.parse(S))
            cout << S;
        else
        {
            switch (P.GetParseResult())
            {
            case Parser::parseBadGrammer:
                if (P.GetFailedWordCode() == wcGibberish)
                    cout << "the word \"" << P.GetFailedWord() << "\" is unknown\n";
                else
                    cout << "sentence is not grammatically correct.\n";
                break;

            case Parser::parseUnresolvedPronoun:
                cout << "parser could not resolve the pronoun \"" <<
                    P.GetUnresolvedPronoun().word << "\"\n";
                break;
            default:
                cout << "parse failed.\n";
                break;
            }
        }

        if (L.LineIsEmpty())
            return make_pair(true, 0);
    }
}
