///////////////////////////////////////////////////////////////////////////////
// Tokenizer.h
// ===========
// General purpose string tokenizer (C++ string version)
//
// The default delimiters are space(" "), tab(\t, \v), newline(\n),
// carriage return(\r), and form feed(\f).
// If you want to use different delimiters, then use setDelimiter() to override
// the delimiters. Note that the delimiter string can hold multiple characters.
//
//  AUTHORs: Song Ho Ahn (song.ahn@gmail.com) and Jeff Creswell creswel2@gmail.com
// CREATED: 2005-05-25
// UPDATED: 2011-03-08
// UPDATED: 2013-07-13
///////////////////////////////////////////////////////////////////////////////

/**
 * Basically the idea behind the Resource.h file will be this:
 * we take a .story file and tokenize it using this class.  While we
 * are extracting tokens, we will store a UUID code for each under a
 * variable name specified in the id attribute of <TEXT> elements.
 * For example <TEXT id='myText'> would be written to Resources.h as
 * const static std::string myText = ... in class Text.  The elipsis is replaced with
 * a code generated from a combination of the id specified and the byte offset
 * in the story file where this string can be found.  When a string is referenced
 * is referenced in the source of the app, it will be via
 * std::string myRoomIntro = findResourceById(Resources.Text.myText);
 * the findResourceById function will take the UUID integer for the
 * sought resource and use it to identify the location and name of the
 * file where the string resides, and then go directly to the byte offset where
 * the string is defined in said file.  This it will read in performing just a bit
 * of disk I/O and then it will retain the string reource until a room
 * cluster has been left.  At this point the temporary string holding the
 * now logically distant string will be overwritten with a more logically
 * close and relevant string e.g. from an adjacent room.
 * The loading of potential strings for nearby rooms
 * should be occurring all the time on background pthreads so that the user
 * barely ever if ever notices load time.
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>
#include "ResourceWriter.h"
#include "TreasureString.h"
#include "../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"
#include "../mapping/hashmap.h"
//#include "../../Resources.h"

#define NO_DELIM_FOUND -1
#define NO_COMMENT_FOUND -2

// default delimiter string (space, tab, newline, carriage return, form feed)
const std::string DEFAULT_DELIMITER = " \t\v\n\r\f";
const std::string DEFAULT_COMMENT = "//";

class Tokenizer
{
public:

	/**
	 * content state := we are looking at content that should be recorded and dispalyed
	 * delimiter state := we are looking at delimiter metadata; do not record it for display and
	 *                    issue directives associated with the delimiter found if necessary
	 *comment state := no characters will be written for display or processing until we exit
	 *                 this state via a comment string identical to the last one found that put us
	 *                 in the comment state with a '/' between the '<' and first char of the
	 *                 comment string.
	 */
	enum ParserState{PARSE_CONTENT_STATE,PARSE_DELIMITER_STATE,PARSE_COMMENT_STATE,PARSE_ENDCOMMENT_STATE,PARSE_METADATA_STATE,PARSE_RESOURCE_CONTENT_STATE};

	const char PARSE_CONTENT_STATE = 0x01; //00000001 content bit
	const char PARSE_DELIMITER_STATE = 0x02; //00000010 delimiter bit
	const char PARSE_COMMENT_STATE = 0x04; //00000100 comment bit
	const char PARSE_ENDCOMMENT_STATE = 0x08; //00001000 endcomment bit
	const char PARSE_METADATA_STATE = 0x10; //00010000 metadata bit

	//for resource content state reading
	//we will look for PARSE_METADATA_STATE | PARSE_CONTENT_STATE

    // ctor/dtor
    Tokenizer();
    Tokenizer(const std::string& str, const std::string& delimiter=DEFAULT_DELIMITER);
    ~Tokenizer();

    // set string and delimiter
    void setStringDelimComment(const std::string& str, const std::string& delimiter=DEFAULT_DELIMITER, const std::string& comment=DEFAULT_COMMENT);
    void setStringDelimsComments(const std::string& str, const std::vector<std::string>&,const std::vector<std::string>&);
    void setStringTSDelimsTSCommentsTags(const std::string& str, const std::vector<TreasureString<int> >&,const std::vector<TreasureString<int> >&,const std::vector<std::string>&, const HashMap<std::string,char>&);
    void setString(const std::string& str);             // set source string only
    void setDelimiter(const std::string& delimiter);    // set delimiter string only
    void setComment(const std::string& comment); // set the comment string
    std::string next();                                 // return the next token, return "" if it ends
    std::string tokenizeAll_StringVector(); //tokenizes based on a vector of string comments and delimiters, and returns the cat'd token set as a std::string
    std::string tokenizeAll_TreasureStringVector(); ////tokenizes based on a vector of treasurestring comments and delimiters, and returns the cat'd token set as a std::string

    //TreasureString tokenizeAllTreasure();

    std::vector<std::string> split();                   // return array of tokens from current cursor

    /**
     * Checks two std::string references to see if the
     * strings they point to are equivalent in char content,
     * with respect to both value and sequence
     */
    bool strEqual(std::string&,std::string&);
    bool strEqual(std::string&,const char*);
    bool strEqual(const char*,std::string&);
    bool strEqual(const char*,const char*);

protected:


private:
    void skipDelimiter(const std::string&);                               // ignore leading delimiters
    void skipDelimiter_CStr(char*,int,const std::string&); //skips any leading complete string delimiters
    bool isDelimiter(char c,const std::string&);                           // check if the current char is delimiter
    bool isDelimiter_CStr(char*,int, const std::string&); //check if the current char through span-1 forms a delimiter string

    std::string buffer;                                 // input string
    std::string token;                                  // output string
    std::string delimiter;                              // delimiter string
    std::string comment;
    TreasureString<int> tsDelimiter;                              // delimiter string
    TreasureString<int> tsComment;
    std::string::const_iterator currPos;                // string iterator pointing the current position
    std::vector<std::string> delimiters;
    std::vector<std::string> comments;
    std::vector<TreasureString<int> > tsvDelimiters;
    std::vector<TreasureString<int> > tsvComments;
    std::vector<std::string> mvTagsVector;
    HashMap<std::string,char> mvTagsMap;
    int iCurrPos; //tracks the iterator's character index in the string with an integer value
    int ParserFSM;

    ResourceWriter rw;

};

#endif // TOKENIZER_H
