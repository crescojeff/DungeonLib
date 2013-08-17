// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// code file for Sentence class

#include "all.hpp"
#include <iostream>
#include "sentence.hpp"

using namespace std;

void Word::print(ostream& out) const
{
    out << '"' << word.c_str() << '"';
    out << ", " << code << ", " << WordClassNames[clss];

    if (code == wcRegEx)
        for (int i = 0; i < int(markers.size()); ++i)
            cout << ", " << i << ": \"" << string(markers[i].first, markers[i].second) << "\"";
}

void Sentences::AddWord(const Word& W, int code)
{
    // add word based on code:
    //  1: add new phrase with the given noun
    //  2: add verb to current predicate
    //  3: add adjective to current noun phrase
    //  4: add article to current noun phrase
    //  5: add preposition to current noun phrase
    //  6: add adjective to current subject
    //  7: add subject
    //  8: add adverb to current verb
    //  9: add adverb to current adjective in current noun phrase
    // 10: add adverb to current adjective in current subject
    // 11: add adverb to current verb (used for trailing adverbs so they have a lower precedence)
    // 25: add new predicate with the given verb
    // 50: add new sentence
    // 99: Ignore word

    switch (code)
    {
    case 1:     // add noun phrase
        add_phrase(W);
        break;

    case 2:     // add verb
        add_verb(W);
        break;

    case 3:     // add adjective to noun phrase
        add_p_adjective(W);
        break;

    case 4:     // add article to current noun phrase
        add_p_article(W);
        break;

    case 5:     // add preposition to current noun phrase
        add_p_preposition(W);
        break;

    case 6:     // add adjective to current subject
        add_s_adjective(W);
        break;

    case 7:     // add subject
        add_subject(W);
        break;

    case 8:     // add adverb to current verb
    case 11:
        add_v_adverb(W);
        break;

    case 9:     // add adverb to current adjective in current noun phrase
        add_p_adverb(W);
        break;

    case 10:    // add adverb to current adjective in current subject
        add_s_adverb(W);
        break;

    case 25:    // add new predicate with given verb
        add_predicate(W);
        break;

    case 50:    // add new sentence
        add_sentence();
        break;

    case 99:    // ignore word
    default:
        break;
    }
}

void Sentences::print_sentences(ostream& out) const
{
    const char ind[] = "    ";

    for (const_reverse_iterator s = rbegin(); s != rend(); ++s)
    {
        // print subjects
        out << "Subjects:\n";
        for (Subjects::const_reverse_iterator sub = s->subjects.rbegin(); sub != s->subjects.rend(); ++sub)
        {
            out << ind << sub->subject << endl;
            if (!sub->article.NoWord())
                out << ind << ind << sub->article << endl;

            for (Adjectives::const_reverse_iterator adj = sub->adjectives.rbegin(); adj != sub->adjectives.rend(); ++adj)
            {
                out << ind << ind << adj->adjective << endl;

                for (Adverbs::const_reverse_iterator adv = adj->adverbs.rbegin(); adv != adj->adverbs.rend(); ++adv)
                {
                    out << ind << ind << ind << *adv << endl;
                }
            }
        }
        out << endl;

        // print predicates
        out << "Predicates:\n";
        for (Predicates::const_reverse_iterator pre = s->predicates.rbegin(); pre != s->predicates.rend(); ++pre)
        {
            out << ind << pre->verb << endl;

            for (Adverbs::const_reverse_iterator adv = pre->adverbs.rbegin(); adv != pre->adverbs.rend(); ++adv)
            {
                out << ind << ind << *adv << endl;
            }

            // print phrases
            for (Phrases::const_reverse_iterator phr = pre->phrases.rbegin(); phr != pre->phrases.rend(); ++phr)
            {
                out << ind << ind << phr->noun << endl;
                if (!phr->preposition.NoWord())
                    out << ind << ind << ind << phr->preposition << endl;
                if (!phr->article.NoWord())
                    out << ind << ind << ind << phr->article << endl;

                for (Adjectives::const_reverse_iterator adj = phr->adjectives.rbegin(); adj != phr->adjectives.rend(); ++adj)
                {
                    out << ind << ind << ind << adj->adjective << endl;

                    for (Adverbs::const_reverse_iterator adv = adj->adverbs.rbegin(); adv != adj->adverbs.rend(); ++adv)
                    {
                        out << ind << ind << ind << ind << *adv << endl;
                    }
                }
            }
        }
        out << endl << endl;
    }
}

