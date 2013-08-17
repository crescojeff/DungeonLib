// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// main test program

#include "all.hpp"
#include <iostream>
#include <exception>
#include <utility>

using namespace std;

#define TEST_REGEX              1
#define TEST_PARSER             1

typedef pair<bool, int> Result;
typedef Result (*TestFunc) ();

extern Result test_regex();
extern Result test_parser();

void run_test(TestFunc func, const char* name)
{
    cout << "Testing " << name << "..." << endl;
    const Result result = func();
    cout << name << " tests have ";
    if (result.first)
        cout << "passed." << endl;
    else
        cout << "failed at line #" << result.second << "." << endl;
    cout << endl;
}

int main()
{
    try
    {
#if TEST_REGEX
        run_test(test_regex, "regex");
#endif // TEST_REGEX

#if TEST_PARSER
        run_test(test_parser, "parser");
#endif // TEST_REGEX
    }
    catch (exception& e)
    {
        cout << "Exception caught in main: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown exception caught in main." << endl;
    }

    return 0;
}
