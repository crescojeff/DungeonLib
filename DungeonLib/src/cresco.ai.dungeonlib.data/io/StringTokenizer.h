/*
 * StringTokenizer.h
 *
 *  Created on: May 29, 2013
 *      Author: CresCoJeff
 *
 *      Tokenizes String data, returning vectors of tokens.
 *      For the moment it tokenizes based on input file stream
 *      to support the need for reading from config and
 *      storyboard files at runtime
 *
 */

#ifndef STRINGTOKENIZER_H_
#define STRINGTOKENIZER_H_

#include "../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"
#include "Tokenizer.h"
#include "../mapping/hashmap.h"

class StringTokenizer {
private:
	Tokenizer mvTokenizer;


public:
	StringTokenizer(){

	}
	virtual ~StringTokenizer(){

	}

	//accessors

	//control functions
	std::vector<std::string> tokenizeStoryboardFIS(const char* fileName,std::string delimiter){
		std::vector<std::string> tokenVector;

		std::string token;
		std::string accStr = "";


		//Establishes in input stream from the named file
		std::ifstream file(fileName);

		//Get line from stream into string
		//Extracts characters from is and stores them into str until the delimitation character delim is found (or the newline character, '\n', for (2)).
		//The extraction also stops if the end of file is reached in is or if some other error occurs during the input operation.
		//If the delimiter is found, it is extracted and discarded, i.e. it is not stored and the next input operation will begin after it.
		//Each extracted character is appended to the string as if its member push_back was called.
		while(std::getline(file, token)) {

			std::cout << "our primal token is " << token << std::endl;


			accStr+=token+'\n';

			//explicit istringstream (const string& str,
            //ios_base::openmode which = ios_base::in)
			//initialization constructor
		    //Constructs an istringstream object with a copy of str as content.
		    //Internally, its istream base constructor is passed a pointer to a stringbuf object constructed with arguments based on str and which.
		    std::istringstream line(token);

		    //TODOx: to tokenize by character string as opposed to a single
		    //char or set of chars, we may want to use std::strstr
		    //which returns a pointer to the first occurrence of a
		    //given substring within a string (both given as const char*)
		    //After getting a pointer to the first
		    //occurrence of, say, std::strstr(token.c_str(),"<STORY>")
		    //we could update the token string to no longer include chars
		    //0 through [pointed to character index] and then repeat the
		    //substring search... or use the Tokenizer class by Song Ho
		    //which is designed to use C++ types




		    /*//TODOx: this is where our white space and line feeds are
		    //being consumed.  Question is why...
		    while(line >> token) {
		        std::cout << "Token :" << token << std::endl;
		        tokenVector.push_back(token);
		        //accStr.append(token);
		        accStr += token;
		    }
		    if(file.unget().get() == (*delimiter.c_str())) {
		        std::cout << "delimiter " << delimiter << " found" << std::endl;
		    }
		    */

		}

		std::cout << "The contents of accStr are " << accStr << std::endl;
		std::cout << "accStr is " << accStr.length() << " chars long " << std::endl;

		const char c = '\n';
		const char* c_ptr = &c;
		std::string tempS(c_ptr);

		/*
		std::vector<std::string> comments;
		comments.push_back("<COMMENT>");

		std::vector<std::string> endcomments;
		endcomments.push_back("</COMMENT>");
		*/

		//instantiate a tstring over the string <comment>
		//and the treasure integer 0 since we'll be using it to
		//indicate that the parser needs to allow for 0 extra chars
		//including whitespace between the second to last char of the
		//comment string ['T'] and the last char of the comment string
		//['>']
		std::vector<TreasureString<int> > tsCommentsVector;
		tsCommentsVector.push_back(TreasureString<int>("<COMMENT>",0));




		/*
		std::vector<std::string> delims;
		//delims.push_back("n");
		//delims.push_back(" ");
		//delims.push_back("\n");
		//delims.push_back(tempS);
		delims.push_back("\"");
		delims.push_back("<STORY>");
		delims.push_back("</STORY>");
		delims.push_back("<DUNGEON>");
		delims.push_back("</DUNGEON>");
		delims.push_back("<ROOM>");
		delims.push_back("</ROOM>");
		delims.push_back("<PARAGRAPH>");
		delims.push_back("</PARAGRAPH>");
		delims.push_back("<TEXT>");
		delims.push_back("</TEXT>");
		//mvTokenizer.set(accStr,"<STORY>");
		*/

		//instantiate a tstring over the string <TEXT>
		//and the treasure integer 20 since we'll be using it to
		//indicate that the parser needs to allow for 20 extra chars
		//including whitespace between the second to last char of the
		//delimiter string ['T'] and the last char of the delimiter string
		//['>'].  This extra char reading is to grab the id attribute.
		//Basically this parsing will look for X attribute chars
		//between the second to last comment/delim char and the last
		//comment/delim char where X is given by the longest attribute set
		//measured in chars in the .story file. The parser will be looking
		//for the last the comment/delim string char and will allow for
		//up to the specified attribute chars length before deciding no
		//legal comment/delimiter string was read.  If it encounters
		//one or more defined attribute strings, like id, it will store
		//them appropriately in Resources.h [id will be the var name used
		//to reference the resource]
		std::vector<TreasureString<int> > tsDelimsVector;
		tsDelimsVector.push_back(TreasureString<int>("<TEXT>",20));
		tsDelimsVector.push_back(TreasureString<int>("</TEXT>",0));
		tsDelimsVector.push_back(TreasureString<int>("<DUNGEON>",20));
		tsDelimsVector.push_back(TreasureString<int>("</DUNGEON>",0));
		tsDelimsVector.push_back(TreasureString<int>("<STORY>",20));
		tsDelimsVector.push_back(TreasureString<int>("</STORY>",0));
		tsDelimsVector.push_back(TreasureString<int>("<ROOM>",20));
		tsDelimsVector.push_back(TreasureString<int>("</ROOM>",0));
		tsDelimsVector.push_back(TreasureString<int>("\"",0));
		tsDelimsVector.push_back(TreasureString<int>("<PARAGRAPH>",20));
		tsDelimsVector.push_back(TreasureString<int>("</PARAGRAPH>",0));

		//std::string map of metadata tags to recognize
		//TODO: DANGER! DANGER will robinson, my hooks are flailing wildy!
		//seriously thoug, passing in this hashmap as a const ref
		//to Tokenizer::setStingTSDelimsTSCommentsTags(...) leads to a double
		//free because HashMap does NOT have a copy-constructor!  Rule of three!
		//either define a cc in HashMap or allocate the map to the heap
		//here so that the map object we construct is never deleted until
		//we explicitly call delete on its address...
		//TODO: also notable is that the delimiter string check in
		//tokenizer.tokenizeAll_TreasureStringVector() doesn't appear
		//to allow for metadata space, as <TEXT id='testtext'>
		//is not read as a delimiter...
		HashMap<std::string,char> tagsMap;
		tagsMap.put("id",OK_BYTE);

		//and a std::vector of metadata tags to iterate over
		std::vector<std::string> tagsVector;
		tagsVector.push_back("id");

		std::cout << "about to call setStringTSDelimsTSCommentsTags" << std::endl;

		mvTokenizer.setStringTSDelimsTSCommentsTags(accStr,tsDelimsVector,tsCommentsVector,tagsVector,tagsMap);

		/*
		while((token = mvTokenizer.next()) != "")
		{
			std::cout << "Tokenized String: " << token << std::endl; //"Tokenizer Token: " << token << std::endl;
		}
		*/

		std::cout << "about to call tokenizeAll_TreasureStringVector" << std::endl;

		token = mvTokenizer.tokenizeAll_TreasureStringVector();
		std::cout << "Tokenized String: " << token << std::endl;


		return tokenVector;
	}

};

#endif /* STRINGTOKENIZER_H_ */
