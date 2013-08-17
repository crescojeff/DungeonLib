// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// Header file for the Sentence class

#ifndef SENTENCE_HPP
#define SENTENCE_HPP

#include "all.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include "vocab.hpp"
#include "diction.hpp"
#include "regex.hpp"

struct Word {
    std::string word;
    WordCode code;
    WordClass clss;
    const Dictionary::ElementType* entry;   // pointer to word's dictionary entry
    REGEX::Markers markers; // regular expression substring markers
    int regex_code;

    Word(std::string pWord = "", WordCode pCode = wcNone, WordClass pClass = clNone,
        const Dictionary::ElementType* pEntry = NULL) :
        word(pWord), code(pCode), clss(pClass), entry(pEntry) {}

    Word(std::string pWord, const REGEX::Markers& pMarkers, int pCode) :
        word(pWord), code(wcRegEx), clss(clRegExCode), entry(NULL), markers(pMarkers), regex_code(pCode) {}

    Word(const Dictionary& D, WordCode pCode, WordClass pClass = clNone)
    {
        Dictionary::const_iterator i = D.find(pCode);

        word = i->first;
        code = pCode;
        clss = pClass != clNone ? pClass : WordClasses_to_WordClass(i->second.classes);
        entry = &(i->second);
    }

    bool NoWord(void) const {return code == wcNone;}
    void print(std::ostream& out) const;
};

inline std::ostream& operator<<(std::ostream& out, const Word& W) {W.print(out); return out;}

typedef std::vector<Word> Words;

typedef Word Adverb;
typedef std::vector<Adverb> Adverbs;

struct Adjective {
    Word adjective;
    Adverbs adverbs;
    Adjective(Word pAdj = Word()) : adjective(pAdj) {}
    Adjective(const Adjective& a) : adjective(a.adjective), adverbs(a.adverbs) {}
    void clear(void)
    {
        adjective = Word();
        adverbs.clear();
    }

    Adjective& operator=(const Adjective& a)
    {
        if (this != &a)
        {
            adjective = a.adjective;
            adverbs = a.adverbs;
        }

        return *this;
    }
};
typedef std::vector<Adjective> Adjectives;

struct Phrase {
    Word preposition;
    Word article;
    Word noun;
    Adjectives adjectives;
    Phrase(Word pNoun = Word()) : noun(pNoun) {}
    Phrase(const Phrase& p) : preposition(p.preposition), article(p.article), noun(p.noun),
        adjectives(p.adjectives) {}
    void clear(void)
    {
        adjectives.clear();
        preposition = noun = article = Word();
    }

    Phrase& operator=(const Phrase& p)
    {
        if (this != &p)
        {
            preposition = p.preposition;
            article = p.article;
            noun = p.noun;
            adjectives = p.adjectives;
        }

        return *this;
    }
};
typedef std::vector<Phrase> Phrases;

struct Subject {
    Word article;
    Word subject;
    Adjectives adjectives;
    Subject(Word pSubject = Word()) : subject(pSubject) {}
    Subject(const Subject& s) : article(s.article), subject(s.subject), adjectives(s.adjectives) {}
    void clear(void)
    {
        adjectives.clear();
        subject = article = Word();
    }

    Subject& operator=(const Subject& s)
    {
        if (this != &s)
        {
            article = s.article;
            subject = s.subject;
            adjectives = s.adjectives;
        }

        return *this;
    }
};

typedef std::vector<Subject> Subjects;

struct Predicate {
    Word verb;
    Adverbs adverbs;
    Phrases phrases;
    Predicate(Word pVerb = Word()) : verb(pVerb) {}
    Predicate(const Predicate& p) : verb(p.verb), adverbs(p.adverbs), phrases(p.phrases) {}
    void clear(void)
    {
        verb = Word();
        adverbs.clear();
        phrases.clear();
    }

    Predicate& operator=(const Predicate& p)
    {
        if (this != &p)
        {
            verb = p.verb;
            adverbs = p.adverbs;
            phrases = p.phrases;
        }

        return *this;
    }
};
typedef std::vector<Predicate> Predicates;

struct Sentence {
    Subjects subjects;
    Predicates predicates;
    Sentence(void) {}
    Sentence(const Sentence& s) : subjects(s.subjects), predicates(s.predicates) {}
    void clear(void) {subjects.clear(); predicates.clear();}
    Sentence& operator=(const Sentence& s)
    {
        if (this != &s)
        {
            subjects = s.subjects;
            predicates = s.predicates;
        }

        return *this;
    }
};


// vector to contain the parsered senteces.  it and all other vectors contained within it are
// built in reverse (later objects are stored first) for effiency reasons.
struct Sentences : public std::vector<Sentence> {
    int parse_string_num; // the number of the parse-string (zero-base) that matched the input

    Sentences(void) : parse_string_num(-1) {}

#if CAN_HANDLE_CALLING_PARENT_TEMPLATE_CLASS_MEMBERS
    void clear(void) {parse_string_num = -1; std::vector<Sentence>::clear();}
#else
    void clear(void) {parse_string_num = -1; static_cast<std::vector<Sentence>*>(this)->clear();}
#endif

    void AddWord(const Word& W, int code);

    // functions that first the "current" object of various types; usefull in building the
    // sentences
    Sentence& curr_sentence(void) {return back();}
    const Sentence& curr_sentence(void) const {return back();}
    Predicate& curr_predicate(void) {return curr_sentence().predicates.back();}
    const Predicate& curr_predicate(void) const {return curr_sentence().predicates.back();}
    Phrase& curr_phrase(void) {return curr_predicate().phrases.back();}
    const Phrase& curr_phrase(void) const {return curr_predicate().phrases.back();}
    Adjective& curr_p_adjective(void) {return curr_phrase().adjectives.back();}
    const Adjective& curr_p_adjective(void) const {return curr_phrase().adjectives.back();}
    Adverb& curr_p_adverb(void) {return curr_p_adjective().adverbs.back();}
    const Adverb& curr_p_adverb(void) const {return curr_p_adjective().adverbs.back();}
    Adverb& curr_v_adverb(void) {return curr_predicate().adverbs.back();}
    const Adverb& curr_v_adverb(void) const {return curr_predicate().adverbs.back();}
    Subject& curr_subject(void) {return curr_sentence().subjects.back();}
    const Subject& curr_subject(void) const {return curr_sentence().subjects.back();}
    Adjective& curr_s_adjective(void) {return curr_subject().adjectives.back();}
    const Adjective& curr_s_adjective(void) const {return curr_subject().adjectives.back();}
    Adverb& curr_s_adverb(void) {return curr_s_adjective().adverbs.back();}
    const Adverb& curr_s_adverb(void) const {return curr_s_adjective().adverbs.back();}

    // functions to return true if the object list is empty
    bool no_sentences(void) const {return empty();}
    bool no_subjects(void) const {return no_sentences() || curr_sentence().subjects.empty();}
    bool no_s_adjectives(void) const {return no_subjects() || curr_subject().adjectives.empty();}
    bool no_predicates(void) const {return no_sentences() || curr_sentence().predicates.empty();}
    bool no_phrases(void) const {return no_predicates() || curr_predicate().phrases.empty();}
    bool no_p_adjectives(void) const {return no_phrases() || curr_phrase().adjectives.empty();}

    // functions to add the given object to the sentences
    void add_sentence(void) {push_back(Sentence());}

    void add_predicate(const Word& W = Word())
    {
        if (no_sentences()) add_sentence();
        curr_sentence().predicates.push_back(Predicate(W));
    }

    void add_phrase(const Word& W = Word())
    {
        if (no_predicates()) add_predicate();
        curr_predicate().phrases.push_back(W);
    }

    void add_p_adjective(const Word& W = Word())
    {
        if (no_phrases()) add_phrase();
        curr_phrase().adjectives.push_back(W);
    }

    void add_p_adverb(const Word& W)
    {
        if (no_p_adjectives()) add_p_adjective();
        curr_p_adjective().adverbs.push_back(W);
    }

    void add_p_preposition(const Word& W)
    {
        if (no_phrases()) add_phrase();
        curr_phrase().preposition = W;
    }

    void add_p_article(const Word& W)
    {
        if (no_phrases()) add_phrase();
        curr_phrase().article = W;
    }

    void add_subject(const Word& W = Word())
    {
        if (no_sentences()) add_sentence();
        curr_sentence().subjects.push_back(W);
    }

    void add_s_adjective(const Word& W = Word())
    {
        if (no_subjects()) add_subject();
        curr_subject().adjectives.push_back(W);
    }

    void add_s_adverb(const Word& W)
    {
        if (no_s_adjectives()) add_s_adjective();
        curr_s_adjective().adverbs.push_back(W);
    }

    void add_s_article(const Word& W)
    {
        if (no_subjects()) add_subject();
        curr_subject().article = W;
    }

    void add_verb(const Word& W = Word())
    {
        if (no_predicates())
            add_predicate(W);
        else
            curr_predicate().verb = W;
    }

    void add_v_adverb(const Word& W)
    {
        if (no_predicates()) add_verb();
        curr_predicate().adverbs.push_back(W);
    }

    // testing functions
    void print_sentences(std::ostream& out) const;

private:
    // internal variables used in building sentences
    std::queue<Adverb> saved_adverbs;  // adverbs encountered after the verb in the sentence
};

inline std::ostream& operator<<(std::ostream& out, const Sentences& S) {S.print_sentences(out); return out;}

#endif // SENTENCE_HPP
