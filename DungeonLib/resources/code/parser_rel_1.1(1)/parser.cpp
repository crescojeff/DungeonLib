// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// Parser code file

#include "all.hpp"
#include <iostream>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <stack>
#include <string>
#include "parser.hpp"
#include "charset.hpp"
#include "vocab.hpp"
#include "regex.hpp"

using namespace std;
using namespace pnfa;

// local exception classes
DEFINE_EXCEPTION(illegal_character, "illegal character");
DEFINE_EXCEPTION(unmatched_bracket, "unmatched bracket");
DEFINE_EXCEPTION(word_not_found, "word not found in dictionary");
DEFINE_EXCEPTION(string_incorrectly_terminated, "string incorrectly terminated");
DEFINE_EXCEPTION(add_command_without_word, "add command encounter without word");
DEFINE_EXCEPTION(unterminated_regex, "unterminated regular expression");

namespace
{
    const Trans E;

    // sets of opening and closing group characters within parse strings.  positions must match.
    const CharSet open_set("({[");
    const CharSet close_set(")}]");

    // set of punctuation characters
    const CharSet punct_set(Punctuation);

    // set of possible Nfa transition types.
    const CharSet trans_set(TransOrder);

    // function to advance a string pointer past white-space characters
    char skip_spaces(const char*& p)
    {
        while (p != NULL && isspace(*p))
            ++p;
        return *p;
    }

    // function to decrement a string pointer before white-space characters
    void trim_right(const char*& p, const char* const begin)
    {
        while (p > begin && isspace(*p))
            --p;
    }

    // function to convert a string to lower case
    void to_lowercase(string& s)
    {
        for (string::iterator i = s.begin(); i != s.end(); ++i)
            *i = tolower(*i);
    }

    // function to extract the command character if it exists
    char get_command(const char*& p)
    {
        skip_spaces(p);
        if (*p == ':')
        {
            skip_spaces(++p);
            return *p;
        }
        else
            return '\0';
    }

    // function to extract the function number if it extist
    int get_func(const char*& p)
    {
        int num = 0;
        skip_spaces(p);

        if (!isdigit(*p))
            return -1;

        while (isdigit(*p))
            num = num * 10 + (*p++ - '0');
        --p;
        return num;
    }

} // namespace

void Parser::strings_to_dfas(const char* const parse_strings[])
{
    dfas.clear();
    alphabet.clear();

    Nfa nfa;
    const char* const * p = parse_strings;

    while (*p != NULL)
    {
        nfa.clear();
        int initial, final;
        const char* pos = *p;

        if (build_nfa(nfa, pos, initial, final) != '\0')
            throw string_incorrectly_terminated();

        // mark final & initial nodes of nfa
        nfa.initial = initial;
        nfa.nodes[final].final = true;

        // convert nfa to dfa and add it the list
        dfas.push_back(Dfa(nfa));

        ++p;
    }
}

char Parser::build_nfa(Nfa& nfa, const char*& pos, int& initial, int& final)
{
    return build_subnfa0(nfa, pos, initial, final);
}

char Parser::build_subnfa0(Nfa& nfa, const char*& pos, int& initial, int& final)
{
    // insert initial and final nodes to simplify Nfa creation
    final = nfa.nodes.size();
    initial = final + 1;
    nfa << Node();
    nfa << Node();

    int first, last;
    char c;

    for (;;)
    {
        c = build_subnfa1(nfa, pos, first, last);

        nfa.nodes[initial] << Edge(E, first);
        nfa.nodes[last] << Edge(E, final);

        if (c == '|')
            ++pos;
        else if (c == '\0' || close_set.contains(c))
            break;
        else
            throw illegal_character();

    }

    return c;
}

char Parser::build_subnfa1(Nfa& nfa, const char*& pos, int& initial, int& final)
{
    // insert initial and final nodes of Nfa
    final = nfa.nodes.size();
    initial = final + 1;
    nfa << Node();
    nfa << Node();

    char c;
    int old_last = initial;
    for (;;)
    {
        c = skip_spaces(pos);

        if (c == '\0' || c == '|' || close_set.contains(c))
            break;

        if (!open_set.contains(c) && c != '<' && c != '/')
            ++pos;

        int first, last;

        build_subnfa2(nfa, pos, first, last);

        int new_last = nfa.nodes.size();
        nfa << Node();

        nfa.nodes[old_last] << Edge(E, first);
        nfa.nodes[last] << Edge(E, new_last);
        last = new_last;

        switch (c)
        {
        case 'p':
        case '(':
        case '<':
        case '/':
            break;

        case 'o':
            nfa.nodes[old_last] << Edge(E, last);
            break;

        case '*':
        case '{':
            nfa.nodes[last] << Edge(E, first);
            nfa.nodes[old_last] << Edge(E, last);
            break;

        case '+':
        case '[':
            nfa.nodes[last] << Edge(E, first);
            break;

        default:
            throw illegal_character();
        }

        ++pos;
        old_last = last;
    }

    nfa.nodes[old_last] << Edge(E, final);
    return c;
}

void Parser::build_subnfa2(Nfa& nfa, const char*& pos, int& initial, int& final)
{
    const char c = skip_spaces(pos);

    if (open_set.contains(c))
    {
        const char t = build_subnfa0(nfa, ++pos, initial, final);

        if (open_set.pos(c) != close_set.pos(t))
            throw unmatched_bracket();
    }
    else
    {
        // insert initial and final nodes of Nfa
        final = nfa.nodes.size();
        initial = final + 1;
        nfa << Node();
        nfa << Node();

        Trans t;

        if (trans_set.contains(c) || punct_set.contains(c))
        {
            t = Trans(c);
        }
        else if (c == '/')
        {
            const char* const start = pos + 1;
            const char* p = start;
            while ((p = strchr(p, '/')) && p[1] == '/')
                p += 2;

            if (!p)
                throw unterminated_regex();

            const char* const end = p;

            // get code
            int code = 0;
            pos = p;
            skip_spaces(++p);
            if (isdigit(*p))
            {
                const char* q;
                code = strtoul(p, (char**) &q, 10);
                skip_spaces(q);
                if (*q != '/')
                    throw unterminated_regex();
                pos = q;
            }

            t = Trans(start, end, code);
        }
        else if (c == '<')
        {
            skip_spaces(++pos);
            const char* const brace = strchr(pos, '>');
            if (brace == NULL)
                throw unmatched_bracket();

            const char* const comma = strchr(pos, ',');
            const char* p;
            string clss = "";

            // extract word
            if (comma == NULL || brace < comma)
                p = brace - 1;
            else
            {
                p = comma - 1;

                // extract class
                const char* q = p + 2;
                const char* r = brace - 1;
                skip_spaces(q);
                trim_right(r, q);
                clss = string(q, r+1);
            }

            trim_right(p, pos);
            t.start = pos;
            t.end = p + 1;
            string wrd(pos, p+1);

            // convert clss to classes mask type
            WordClasses cls = cmNone;
            if (clss != "")
            {
                to_lowercase(clss);
                for (int i = 0; i < NumberOfClasses; ++i)
                {
                    if (clss == WordClassNames[i])
                    {
                        cls = 1 << i;
                        break;
                    }
                }
            }

            WordCode word;
            WordClasses classes;
            WordInfo info;
            pos = brace;

            if (D.find(wrd, word, classes, info))
            {
                t = Trans(word, cls == cmNone ? classes : cls);
            }
            else
                throw word_not_found();
        }
        else
            throw illegal_character();

        // get command character
        const char* p = pos + 1;
        char comm = get_command(p);
        if (comm != '\0')
        {
            // check if command is absent
            if (isdigit(comm))
            {
                --p;
                comm = 'N';
            }

            // add command to node
            t.command = comm;

            if (comm == 'A')
                if (!t.start || !t.end)
                    throw add_command_without_word();

            // get function number
            int func_num = get_func(++p);
            if (func_num < 0)
            {
                // no function code found
                func_num = 0;
                --p;
            }

            // add function number to node
            t.func_code = func_num;

            pos = p;
        }

        // add node to nfa & alphabet
        nfa.nodes[initial] << Edge(t, final);
        /*pair<TransList::const_iterator, bool> x = */ // test point
        alphabet.insert(t);
    }
}

namespace
{
char code_to_punc(int code)
{
    return Punctuation[-(code + 1)];
}

bool match(const Trans& trans, WordCode code, WordClasses classes, WordClass& cl, LexicalAnalyzer& L,
           string::const_iterator old_state, REGEX::Markers& markers, string& ex_str, int& ex_code)
{
    cl = clNone;

    if (trans.command == 'C')
    {
        return true;
    }
    if (punct_set.contains(trans.trans) && trans.trans == code_to_punc(code))
    {
        cl = clPunctuation;
        return true;
    }
    else switch (trans.trans)
    {
    case 'r':
        if (in_class(classes, cl = clArticle)) return true;
        break;
    case 'j':
        if (in_class(classes, cl = clAdjective)) return true;
        break;
    case 'd':
        if (in_class(classes, cl = clAdverb)) return true;
        break;
    case 'c':
        if (in_class(classes, cl = clConjunction)) return true;
        break;
    case 'p':
        if (in_class(classes, cl = clPreposition)) return true;
        break;
    case 'v':
        if (in_class(classes, cl = clVerb)) return true;
        break;
    case 'P':
        if (in_class(classes, cl = clProperNoun)) return true;
        break;
    case 'o':
        if (in_class(classes, cl = clPronoun)) return true;
        break;
    case 'n':
        if (in_class(classes, cl = clPronoun) ||
            in_class(classes, cl = clProperNoun) ||
            in_class(classes, cl = clNoun)) return true;
        break;
    case 'g':
        if (code == wcGibberish) return true;
        break;
    case 'a':
        if (code == wcGibberish) return false;
        // fall through
    case 'A':
    {
        cl = WordClasses_to_WordClass(classes);
        return true;
    }
    case 'm':
        if (trans.info.m_trans.code == code || trans.command == 'A')
        {
            cl = WordClasses_to_WordClass(trans.info.m_trans.classes);
            return true;
        }
        return false;

    case 'x':
    {
        string::const_iterator saved_state = L.SaveState();
        L.RestoreState(old_state);
        const string ex(trans.info.x_trans.start, trans.info.x_trans.end - trans.info.x_trans.start);
        ex_str = L.CopyLine();
        int count;
        if (REGEX::regex(ex.c_str(), ex_str.c_str(), count, &markers))
        {
            L.RestoreState(old_state + count);
            cl = clRegExCode;
            ex_code = trans.info.x_trans.code;
            return true;
        }
        else
            L.RestoreState(saved_state);
        break;
    }

    }


    return false;
}

bool move(const Dfa& dfa, int in, const Trans& trans, WordCode code, WordClasses classes, int& n_out,
           WordClass &cl, LexicalAnalyzer& L, string::const_iterator old_state, REGEX::Markers& markers,
           string& ex_str, int& ex_code)
{
    for (Edges::const_iterator i = dfa.nodes[in].edges.begin(); i != dfa.nodes[in].edges.end(); ++i)
    {
        if (i->trans == trans && match(trans, code, classes, cl, L, old_state, markers, ex_str, ex_code))
        {
            n_out = i->node;
            return true;
        }
    }
    return false;
}

} // namespace

bool Parser::build_path(const Dfa& dfa, int node, Sentences& S)
{
    int p;
    string word;
    WordCode code;
    WordClass clss;
    WordClasses classes;
    bool result = false;
    bool end_of_words = false;
    bool moved = false;
    string::const_iterator old_state = L.SaveState();
    const Dictionary::ElementType* entry;
    REGEX::Markers markers;

    if (L.GetNextWord(word, code, classes, entry))
    {
        // no more words in input
        end_of_words = true;
        word = "";
        code = wcNone;
        classes = cmNone;
        entry = NULL;
    }

    bool inpunc = in_class(classes, clPunctuation);

    // Check each transition in the alphabet for a legal move.  If there is
    // one, recursive check the next one.  If that was successful, add
    // the word to the stack
    for (TransList::iterator i = alphabet.begin(); i != alphabet.end(); ++i)
    {
        string ex_str;
        int ex_code;
        if (move(dfa, node, *i, code, classes, p, clss, L, old_state, markers, ex_str, ex_code))
        {
            moved = true;

            // if move is to add new word, reparse to current input
            // with the new node, then add new word to stack
            if (i->command == 'A')
            {
                L.RestoreState(old_state);
                word = string(i->start, i->end - i->start);
                code = i->info.m_trans.code;
                Dictionary::const_iterator i = D.find(code);

                entry = &(i->second);
            }

            // if move is to just execute a command, reparse
            // current input with the new node, then execute command
            else if (i->command == 'C')
            {
                L.RestoreState(old_state);
                word = "";
                code = wcNone;
                clss = clNone;
                entry = NULL;
            }

            if (build_path(dfa, p, S))
            {
                if (clss == clRegExCode)
                    S.AddWord(Word(ex_str, markers, ex_code), i->func_code);
                else
                    S.AddWord(Word(word, code, clss, entry), i->func_code);
                result = true;
                break;
            }
            else if (i->command == 'A' || i->command == 'C')
            {
                // reread current word
                if (L.GetNextWord(word, code, classes, entry))
                {
                    // no more words in input
                    end_of_words = true;
                    word = "";
                    code = wcNone;
                    classes = cmNone;
                    entry = NULL;
                }
            }
        }
    }

    // If the current "word" is a punctuation character and there was not
    // legal move on it, then skip it.
    if (!result && inpunc && build_path(dfa, node, S))
    {
        result = true;
    }

    // if there are no more words to parse and parser is in a final node of the Dfa, parse passed
    else if (!result && end_of_words && dfa.nodes[node].final)
    {
        result = true;
    }

    // if there was no possible move for this word, saved it as the failed word for the parse
    if (!moved)
    {
        failed_code = code;
        failed_word = word;
    }

    L.RestoreState(old_state);
    return result;
}

bool Parser::parse (Sentences &S)
{
    bool result = true;
    parse_result = parseOk;
    failed_code = wcNone;
    failed_word = "";

    unresolved_pronoun = Word();
    S.clear();
    L.GetNextLine();

    for (size_t i = 0; i < dfas.size(); ++i)
    {
        if (build_path(dfas[i], dfas[i].initial, S))
        {
            S.parse_string_num = i;
            break;
        }

        parse_result = parseBadGrammer;
        result = false;
    }

    if (result)
    {
        Word unresolved;

        if (!ResolvePronouns(S))
        {
            parse_result = parseUnresolvedPronoun;
            result = false;
        }
    }

    return result;
}

bool Parser::ResolvePronoun(Word& w)
{
    const WordInfo info = w.entry->info;

    if (info & wiDontResolve || info == wiNone)
    {
        return true;
    }

    if (info & wiObjectPronoun && !object_pronoun.NoWord())
    {
        w = object_pronoun;
        return true;
    }

    if (info & wiMalePronoun && !male_pronoun.NoWord())
    {
        w = male_pronoun;
        return true;
    }

    if (info & wiFemalePronoun && !female_pronoun.NoWord())
    {
        w = female_pronoun;
        return true;
    }

    unresolved_pronoun = w;

    return false;
}

bool Parser::ResolvePronouns(Sentences& S)
{
    Word new_object(object_pronoun), new_male(male_pronoun), new_female(female_pronoun);

    const Sentences::reverse_iterator s_rend = S.rend();
    for (Sentences::reverse_iterator s = S.rbegin(); s != s_rend; ++s)
    {
        const Predicates::reverse_iterator p_rend = s->predicates.rend();
        for (Predicates::reverse_iterator p = s->predicates.rbegin(); p != p_rend; ++p)
        {
            const Phrases::reverse_iterator r_rend = p->phrases.rend();
            for (Phrases::reverse_iterator r = p->phrases.rbegin(); r != r_rend; ++r)
            {
                Word& w = r->noun;

                if (w.clss == clPronoun && !ResolvePronoun(w))
                    return false;

                if (w.clss != clPronoun)
                    UpdatePronouns(w, new_object, new_male, new_female, false);
            }
        }

        const Subjects::reverse_iterator j_rend = s->subjects.rend();
        for (Subjects::reverse_iterator j = s->subjects.rbegin(); j != j_rend; ++j)
        {
            Word& w = j->subject;

            if (w.clss == clPronoun && !ResolvePronoun(w))
                return false;

            if (w.clss != clPronoun)
                UpdatePronouns(w, new_object, new_male, new_female, true);
        }

        object_pronoun = new_object;
        male_pronoun = new_male;
        female_pronoun = new_female;
    }

    return true;
}

void Parser::UpdatePronouns(const Word& w, Word& object, Word& male, Word& female, bool from_subjects)
{
    if (w.entry)
    {
        const WordInfo info = w.entry->info;

        if (info & wiObjectNoun && (!from_subjects || object.NoWord()))
            object = w;

        if (info & wiMaleNoun && (!from_subjects || male.NoWord()))
            male = w;

        if (info & wiFemaleNoun && (!from_subjects || female.NoWord()))
            female = w;
    }
}
