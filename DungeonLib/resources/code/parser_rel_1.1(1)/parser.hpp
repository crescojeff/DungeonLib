// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

// Parser header file

#ifndef PARSER_HPP
#define PARSER_HPP

#include "all.hpp"
#include <set>
#include <vector>
#include <iostream>
#include "lexical.hpp"
#include "pnfa.hpp"
#include "diction.hpp"
#include "sentence.hpp"

// exception class
DEFINE_EXCEPTION(BadParseString, "bad parse string");

class Parser {
public:
    // parse results
    enum ParseResult {
        parseOk, parseBadGrammer, parseUnresolvedPronoun
    };

protected:
    LexicalAnalyzer& L;
    Dictionary& D;
    pnfa::DfaList dfas;
    pnfa::TransList alphabet;

    // pronoun equates that can be set in program that take precedence over any other form of
    // resolution.  will be reset are a successful parse.
    Word object_pronoun, male_pronoun, female_pronoun;

    // parse result variables
    ParseResult parse_result;
    Word unresolved_pronoun;
    WordCode failed_code;
    std::string failed_word;

    void strings_to_dfas(const char* const parse_strings[]);
    bool build_path(const pnfa::Dfa& dfa, int node, Sentences& S);

    // The following "build" functions each build 'simple' NFAs from the given point in the
    // parse string.  The NFA is simple because the first node is always the initial node, and the
    // last node is always the only final node (but final flag is NOT set).  The functions return
    // the actual character that terminated the NFA build.
    char build_nfa(pnfa::Nfa& nfa, const char*& pos, int& initial, int& final);
    char build_subnfa0(pnfa::Nfa& nfa, const char*& pos, int& initial, int& final);
    char build_subnfa1(pnfa::Nfa& nfa, const char*& pos, int& initial, int& final);
    void build_subnfa2(pnfa::Nfa& nfa, const char*& pos, int& initial, int& final);

    bool ResolvePronouns(Sentences& S);
    bool ResolvePronoun(Word& w);
    void UpdatePronouns(const Word& w, Word& object, Word& male, Word& female, bool from_subjects);

public:
    Parser(LexicalAnalyzer& pL, Dictionary& pD, const char* const parse_strings[]) :
        L(pL), D(pD), object_pronoun(Word()), male_pronoun(Word()), female_pronoun(Word())
    {
        strings_to_dfas(parse_strings);
    }

    bool parse(Sentences& S);

    void SetObjectPronoun(const Word& w) {object_pronoun = w;}
    void SetMalePronoun(const Word& w) {male_pronoun = w;}
    void SetFemalePronoun(const Word& w) {female_pronoun = w;}

    ParseResult GetParseResult(void) const {return parse_result;}
    const Word& GetUnresolvedPronoun(void) const {return unresolved_pronoun;}
    WordCode GetFailedWordCode(void) const {return failed_code;}
    const std::string& GetFailedWord(void) const {return failed_word;}
};

#endif // PARSER_HPP
