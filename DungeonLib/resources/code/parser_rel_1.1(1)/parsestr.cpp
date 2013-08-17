// (C) Copyright Richard Herrick 2002.
//
// Permission to copy, use, modify, sell and distribute this software
// is granted provided this copyright notice appears in all
// copies. This software is provided "as is" without express or
// implied warranty, and with no claim as to its suitability for any
// purpose.

#include "all.hpp"
#include <cstring>
#include "parsestr.hpp"
#include "vocab.hpp"

const char TransOrder[] = PUNCT_CHARS "mcprvdPonjxgaA";
const char CommandOrder[] = "NA";

#define ADVj            "pd:9"
#define ADVjs           "{" ADVj "{oc:9" ADVj "}}"  // adverbs for adjectives in noun phrase
#define ADJn            ADVjs "pj:3"
#define ADJns           "{" ADJn "{oc:3" ADJn "}}"  // adjectives for noun phrases
#define NOUN            ADJns "pn:1"                // noun for noun phrase
#define PREP            "op:5"                      // preposition for noun phrase
#define ART             "or:4"                      // article for noun phrase
#define PHONE           "/[0-9]{3}-[0-9]{4}/1/:1"
#define PHRASE          "(" PREP ART NOUN "|" PHONE ")"
#define PHRASEs         "{" PHRASE "{oc:1" PHRASE "}}"
#define ADVv            "pd:8"
#define ADVvs           "{" ADVv "{oc:8" ADVv "}}"  // adverbs for verbs
#define ADVe            "pd:11"
#define ADVes           "{" ADVv "{oc:11" ADVv "}}" // adverbs for verbs (trailing adverbs)
#define VERB            ADVvs "pv:2" ADVes
#define ADVs            "pd:10"
#define ADVss           "{" ADVs "{oc:10" ADVs "}}" // adverbs for adjectives in subjects
#define ADJs            ADVss "pj:6"
#define ADJss           "{" ADJs "{oc:6" ADJs "}}"  // adjectives for subjects
#define SUB             ADJss "(po:7 | pP:7)"
#define SUBs            "{" SUB "{oc:7" SUB "}}"
#define PRED            VERB PHRASEs ADVes
#define PREDs           PRED "{pm:C25 o(pc:2 pm:C25)" PRED "}"
#define END             "o(p.)"
#define SENT            SUBs PREDs
#define SENTs           SENT  "{" END "pm:C50 o(pc:2 pm:C50)" SENT "}"

// each parse string is considered an alternate path: s[0] | s[1] | s[2] ...
const char* const parse_strings[] = {

#if 1
    SENTs,
#else
    "/([0-9]{3})-([0-9]{4})/1/:2 <north, noun>:1",
#endif

    NULL};

