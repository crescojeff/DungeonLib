// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// test regular expression class

#include "all.hpp"
#include <functional>
#include <string>
#include <utility>
#include "regex.hpp"

using namespace std;
using namespace REGEX;

#define FAILED make_pair(false, __LINE__)

pair<bool, int> test_regex()
{
    int m;

    if (!regex("hello", "hello", m) || m != 5)
        return FAILED;
    if (regex("hello", "goodbye", m))
        return FAILED;
    if (!regex("hel*lo", "helo", m) || m != 4)
        return FAILED;
    if (!regex("hel*lo", "hello", m) || m != 5)
        return FAILED;
    if (!regex("hel*llo", "hello", m) || m != 5)
        return FAILED;
    if (!regex("hel+lo", "hello", m) || m != 5)
        return FAILED;
    if (regex("hel+llo", "hello", m))
        return FAILED;
    if (!regex("h?ello", "ello", m) || m != 4)
        return FAILED;
    if (!regex("h?ello", "hello", m) || m != 5)
        return FAILED;
    if (regex("h?ello", "xello", m))
        return FAILED;
    if (!regex("\\h\\e\\l\\l\\o", "hello", m) || m != 5)
        return FAILED;
    if (regex("\\h\\e\\l\\l\\o", "hell", m))
        return FAILED;
    if (!regex("\\h\\e\\l\\l\\o\\*\\+\\?", "hello*+?", m) || m != 8)
        return FAILED;
    if (!regex("[h]", "h", m) || m != 1)
        return FAILED;
    if (!regex("[a-z]", "h", m) || m != 1)
        return FAILED;
    if (!regex("[a-z]*", "hello", m) || m != 5)
        return FAILED;
    if (!regex("[A-Z]*", "HELLO", m) || m != 5)
        return FAILED;
    if (!regex("[a-z]*", "HELLO", m) || m != 0)
        return FAILED;
    if (!regex("[a-z]*", "goodbye", m) || m != 7)
        return FAILED;
    if (!regex("[a-z]*", "hello1", m) || m != 5)
        return FAILED;
    if (!regex("[a-z]+", "hello1", m) || m != 5)
        return FAILED;
    if (!regex("[hello]*", "hello", m) || m != 5)
        return FAILED;
    if (!regex("[hello]*", "goodbye", m) || m != 0)
        return FAILED;
    if (!regex("[hello]+", "hello", m) || m != 5)
        return FAILED;
    if (regex("[hello]+", "goodbye", m))
        return FAILED;
    if (!regex("[a-z0-9]*", "hello1234567890", m) || m != 15)
        return FAILED;
    if (!regex("[^a-z]*", "hello", m) || m != 0)
        return FAILED;
    if (regex("[^a-z]+", "hello", m))
        return FAILED;
    if (!regex("[^0-9]*", "hello", m) || m != 5)
        return FAILED;
    if (!regex("[^0-9]+", "hello", m) || m != 5)
        return FAILED;
    if (!regex("[-0-9]*", "-123", m) || m != 4)
        return FAILED;
    if (!regex("[-0-9]+", "-123", m) || m != 4)
        return FAILED;
    if (!regex("[][0-9-]*", "[-123]", m) || m != 6)
        return FAILED;
    if (!regex("[^][0-9-]*", "hello", m) || m != 5)
        return FAILED;
    if (!regex("[^][0-9-]+", "hello", m) || m != 5)
        return FAILED;
    if (!regex("[[:alpha:]]*", "helloHELLO", m) || m != 10)
        return FAILED;
    if (!regex("[[:alpha:]]*", "hello1", m) || m != 5)
        return FAILED;
    if (!regex("[[:lower:]]*", "hello", m) || m != 5)
        return FAILED;
    if (!regex("[[:lower:]]*", "hellO", m) || m != 4)
        return FAILED;
    if (!regex("[[:upper:]]*", "HELLO", m) || m != 5)
        return FAILED;
    if (!regex("[[:lower:]]*", "HELLo", m) || m != 0)
        return FAILED;
    if (!regex("[[:alnum:]]*", "HELLOhello123", m) || m != 13)
        return FAILED;
    if (!regex("[[:alnum:]]*", "hello!", m) || m != 5)
        return FAILED;
    regex("[[:digit:]]*", "0123456789", m);
    if (!regex("[[:digit:]]*", "hello", m) || m != 0)
        return FAILED;
    if (!regex("[[:xdigit:]]*", "0123456789abcdefABCDEF", m) || m != 22)
        return FAILED;
    if (!regex("[[:xdigit:]]*", "123abcdefghi", m) || m != 9)
        return FAILED;
    if (!regex("[[:cntrl:]]*", "\n\t\v", m) || m != 3)
        return FAILED;
    if (!regex("[[:cntrl:]]*", "hello\n", m) || m != 0)
        return FAILED;
    if (!regex("[[:graph:]]*", "123abc", m) || m != 6)
        return FAILED;
    if (!regex("[[:graph:]]*", " ", m) || m != 0)
        return FAILED;
    if (!regex("[[:punct:]]*", "!@#$%^&*", m) || m != 8)
        return FAILED;
    if (!regex("[[:punct:]]*", "123abc", m) || m != 0)
        return FAILED;
    if (!regex("[^[:punct:][:cntrl:]]*", "123abc", m) || m != 6)
        return FAILED;
    if (!regex("[[:punct:][:cntrl:]]+", "\n\t\v!@#$%^&*", m) || m != 11)
        return FAILED;
    if (!regex("\\x35", "\x35", m) || m != 1)
        return FAILED;
    if (regex("\\x35", "\x36", m))
        return FAILED;
    if (!regex("h{5}", "hhhhh", m) || m != 5)
        return FAILED;
    if (regex("h{5}", "hhhh", m))
        return FAILED;
    if (!regex("h{5}", "hhhhhh", m) || m != 5)
        return FAILED;
    if (!regex("h{5}h", "hhhhhh", m) || m != 6)
        return FAILED;
    if (!regex("h{0}abc", "abc", m) || m != 3)
        return FAILED;
    if (!regex("h{5,}", "hhhhh", m) || m != 5)
        return FAILED;
    if (!regex("h{5,}h", "hhhhhh", m) || m != 6)
        return FAILED;
    if (regex("h{5,}", "hhhh", m))
        return FAILED;
    if (!regex("h{5,}", "hhhhhh", m) || m != 6)
        return FAILED;
    if (!regex("h{5,7}", "hhhhh", m) || m != 5)
        return FAILED;
    if (!regex("h{5,7}", "hhhhhh", m) || m != 6)
        return FAILED;
    if (!regex("h{5,7}", "hhhhhhh", m) || m != 7)
        return FAILED;
    if (regex("h{5,7}", "hhhh", m))
        return FAILED;
    if (!regex("h{5,7}", "hhhhhhhh", m) || m != 7)
        return FAILED;
    if (!regex("h{5,7}h", "hhhhhhhh", m) || m != 8)
        return FAILED;
    if (!regex("((abc)(123))", "abc123", m) || m != 6)
        return FAILED;
    if (!regex("((abc)*(123)+)", "abcabcabc123123", m) || m != 15)
        return FAILED;
    if (!regex("((a(b*c+)c+)*(123)+)", "abccabccabcc123123", m) || m != 18)
        return FAILED;
    if (!regex("hello|goodbye|solong", "hello", m) || m != 5)
        return FAILED;
    if (!regex("(hello)|(goodbye)|solong", "goodbye", m) || m != 7)
        return FAILED;
    if (!regex("hello|(goodbye)|(solong)", "solong", m) || m != 6)
        return FAILED;
    if (regex("(hello)|goodbye|(solong)", "good", m))
        return FAILED;
    if (!regex("hello|goodbye|solong|[0-9]+", "1234567890", m) || m != 10)
        return FAILED;
    if (!regex("[0-9]+|hello|goodbye|solong", "1234567890", m) || m != 10)
        return FAILED;
    if (!regex("hello|[0-9]+|goodbye|solong", "1234567890", m) || m != 10)
        return FAILED;
    if (!regex("hello/ goodbye", "hello goodbye", m) || m != 5)
        return FAILED;
    if (regex("hello/ goodbye", "hello solong", m))
        return FAILED;
    if (!regex("hello/ goodbye/ I'm back!", "hello goodbye I'm back!", m) || m != 5)
        return FAILED;

    Markers markers;
    Nfa nfa;

    if (!regex("((([0-9]+))-([a-z]+)-(([0-9]+)))", "1234567890-abcdefghi-0987654321", m,
            &markers, &nfa) || m != 31 || markers.size() != 6)
        return FAILED;

    if (string(markers[0].first, markers[0].second) !=
            "1234567890-abcdefghi-0987654321")
        return FAILED;
    if (string(markers[1].first, markers[1].second) !=
            "1234567890")
        return FAILED;
    if (string(markers[2].first, markers[2].second) !=
            "1234567890")
        return FAILED;
    if (string(markers[3].first, markers[3].second) !=
            "abcdefghi")
        return FAILED;
    if (string(markers[4].first, markers[4].second) !=
            "0987654321")
        return FAILED;
    if (string(markers[5].first, markers[5].second) !=
            "0987654321")
        return FAILED;

    if (!regex(nfa, "1234567890-abcdefghi-0987654321", m, &markers) ||
            m != 31 || markers.size() != 6)
        return FAILED;

    if (string(markers[0].first, markers[0].second) !=
            "1234567890-abcdefghi-0987654321")
        return FAILED;
    if (string(markers[1].first, markers[1].second) !=
            "1234567890")
        return FAILED;
    if (string(markers[2].first, markers[2].second) !=
            "1234567890")
        return FAILED;
    if (string(markers[3].first, markers[3].second) !=
            "abcdefghi")
        return FAILED;
    if (string(markers[4].first, markers[4].second) !=
            "0987654321")
        return FAILED;
    if (string(markers[5].first, markers[5].second) !=
            "0987654321")
        return FAILED;

    return make_pair(true, 0);
}
