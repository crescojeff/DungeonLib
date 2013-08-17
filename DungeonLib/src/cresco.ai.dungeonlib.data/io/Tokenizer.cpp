///////////////////////////////////////////////////////////////////////////////
// Tokenizer.cpp
// =============
// General purpose string tokenizer (C++ string version)
//
// The default delimiters are space(" "), tab(\t, \v), newline(\n),
// carriage return(\r), and form feed(\f).
// If you want to use different delimiters, then use setDelimiter() to override
// the delimiters. Note that the delimiter string can hold multiple characters.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2005-05-25
// UPDATED: 2011-03-08
///////////////////////////////////////////////////////////////////////////////

#include "Tokenizer.h"



///////////////////////////////////////////////////////////////////////////////
// constructor
///////////////////////////////////////////////////////////////////////////////
Tokenizer::Tokenizer() : buffer(""), token(""), delimiter(DEFAULT_DELIMITER)
{
    currPos = buffer.begin();
    iCurrPos = 0;
    std::stringstream resSS;
    resSS << "#ifndef RESOURCES_H_" << std::endl << "#define RESOURCES_H_" << std::endl << "static class Resources{" << std::endl << "public:" << std::endl;
    rw.setResContent(resSS.str());
    rw.writeContentToResources(rw.WRITE_MODE_OVER);

    //rw.writeContentToResources(rw.WRITE_MODE_PREPEND);
}

Tokenizer::Tokenizer(const std::string& str, const std::string& delimiter) : buffer(str), token(""), delimiter(delimiter)
{
    currPos = buffer.begin();
    iCurrPos = 0;
}



///////////////////////////////////////////////////////////////////////////////
// destructor
///////////////////////////////////////////////////////////////////////////////
Tokenizer::~Tokenizer()
{
}



///////////////////////////////////////////////////////////////////////////////
// reset string buffer, delimiter and the currsor position
///////////////////////////////////////////////////////////////////////////////
void Tokenizer::setStringDelimComment(const std::string& str, const std::string& delimiter,const std::string& comment)
{
    this->buffer = str;
    this->delimiters.push_back(delimiter);
    this->comments.push_back(comment);
    this->delimiter = this->delimiters[0];
    this->comment = this->comments[0];
    this->currPos = buffer.begin();
}
void Tokenizer::setStringDelimsComments(const std::string& str, const std::vector<std::string>& delimiters,const std::vector<std::string>& comments)
{
    this->buffer = str;
    for(int i=0;i<delimiters.size();i++){
    	this->delimiters.push_back(delimiters[i]);
    }
    for(int i=0;i<comments.size();i++){
		this->comments.push_back(comments[i]);
	}
    this->delimiter = this->delimiters[0]; //begin at the beginning...
    this->comment = this->comments[0];
    this->currPos = buffer.begin();
}

void Tokenizer::setStringTSDelimsTSCommentsTags(const std::string& str, const std::vector<TreasureString<int> >& tsvDelims,const std::vector<TreasureString<int> >& tsvComms,const std::vector<std::string>& vTags,const HashMap<std::string,char>& mTags){
	//Checking strEqual function
	//std::string s1 = "id";
	//std::string s2 = "di";
	std::stringstream tempSS;
	tempSS << strEqual("idd","ide") << std::endl;
	myStaticWriteStringLog(tempSS.str());
	std::cout << strEqual("idd","ide") << std::endl;

	static std::string* s_ptr = new std::string("yo");
	std::cout << "our static string pointer points to string " << *s_ptr << std::endl;


	this->buffer = str;
	for(int i=0;i<tsvDelims.size();i++){
		this->tsvDelimiters.push_back(tsvDelims[i]);
	}
	for(int i=0;i<tsvComms.size();i++){
		this->tsvComments.push_back(tsvComms[i]);
	}
	this->tsDelimiter = this->tsvDelimiters[0]; //begin at the beginning...
	this->tsComment = this->tsvComments[0];
	this->mvTagsVector = vTags;
	this->mvTagsMap = mTags;
	this->currPos = buffer.begin();
}

void Tokenizer::setString(const std::string& str)
{
    this->buffer = str;
    this->currPos = buffer.begin();
}

void Tokenizer::setDelimiter(const std::string& delimiter)
{
	this->delimiters.push_back(delimiter);
    this->delimiter = this->delimiters[0];
    this->currPos = buffer.begin();

}



///////////////////////////////////////////////////////////////////////////////
/**return all tokens built together into a single string
 *
 *Iff cannot find a token, then return "".
 */
///////////////////////////////////////////////////////////////////////////////
std::string Tokenizer::tokenizeAll_StringVector()
{

	token.clear();

	//TODOx: Okay, delimiting by an entire string works nicely.
	//Now comes the REAL challenge -- how to handle multiple
	//string delimiters, each one of arbitrary length?
	//UPDATE: current issue with returned token being
	//APH>... is due to the fact that our two string delimiter
	//both start with the same character and for some reason span is staying
	//with the first delimiter length of 7, so <STORY> gets skipped
	//and also <PARAGR.  Also/otherwise it seems our isDelimiter_CStr() method
	//may not be working properly...

	//If only one string delimiter is specified via the
	//single string set() arg set...
	///for(int i = 0;i<delimiters.size();i++){

		if(buffer.size() <= 0) return "";           // skip if buffer is empty

		//token.clear();                              // reset token string

		//this->skipDelimiter();                      // skip leading delimiters


		std::stringstream ssLog;

		/*
		int span = delimiters[i].length();

		std::string subStr = buffer.substr(iCurrPos,span);
		const char* cstr1 = (subStr.c_str());
		char cstr2[sizeof(cstr1)];

		std::strncpy(cstr2,cstr1,sizeof(cstr1));

		this->skipDelimiter_CStr(cstr2,span,delimiters[i]);
		*/


		/*
		//Skip leading delimiters
		for(int i=0;i<delimiters.size();i++){
			//[X]TODOx: our APH> result is caused by this here--
			//we only look at the first char and then iff
			//it is a match to delimiters[0][0], we declare it
			//a delimiter immediately for span characters.  This
			//cause <PARAGR to be read as delimiter to skip just
			//because it starts with a left-angle bracket like <STORY>
		//this->skipDelimiter(delimiters[i]);
			int span = delimiters[i].length();

			std::string subStr = buffer.substr(iCurrPos,span);
			const char* cstr1 = (subStr.c_str());
			char cstr2[sizeof(cstr1)];

			std::strncpy(cstr2,cstr1,sizeof(cstr1));

			//Check to see if the current char could be starting a
			//deliverable
			//std::cout << " possibly skipping leading delimiter -- the current char is " << *currPos << " and the target starting delim char is " << delimiters[i][0] << std::endl;
			ssLog << " possibly skipping leading delimiter -- the current char is " << *currPos << " and the target starting delim char is " << delimiters[i][0] << std::endl;
			if(isDelimiter(*currPos,delimiters[i])){

				this->skipDelimiter_CStr(cstr2,span,delimiters[i]);

			}

		}
		*/

		/*
		std::string subStr2 = buffer.substr(iCurrPos,span);

	   //// //std::cout << "our buffer substring from position " << iCurrPos << " is " << subStr2 << std::endl;

		const char* cstr3 = (subStr2.c_str());
		std::strncpy(cstr2,cstr3,sizeof(cstr3));
		*/

		// append each char to token string until it meets delimiter
		//TODOx: look for the first character of the delimiter string
		//iff one is found, look ahead delimiter.length() span to see
		//if a complete delimiter string is present

		int foundDelimIndex = NO_DELIM_FOUND;
		int foundCommentIndex = NO_COMMENT_FOUND;
		this->ParserFSM = PARSE_CONTENT_STATE;

		////Commenting this while loop and using the loop in StringTokenizer instead
		while(currPos != buffer.end() )//&& //!isDelimiter_CStr(cstr2,delimiter.length()))//!isDelimiter(*currPos))
		{


			//TODOx: so here is the cause of our current problem, where we
			//can skip at least one leading delimiter but later ones are
			//missed-- we need each char of the source buffer to be
			//analyzed wrt each individual delimiter; the way we have it here
			//current pos is updated within the for loop, meaning the
			//second delim will be looking at a different character.  Most likely
			//what we're currently seeing is < read at second <STORY> tag,
			//but current delim is </STORY> so the <STORY> tag returns false
			//for being a delimiter string.  What we should do instead perhpas is
			//factor out position modification to after the for loop, based on
			//analyses prepared within the for loop.
			//Essentially, foreach(char in buffer){is char the start of current delim? if yes, is current char + current span exactly equal to the current delim? ...
			//Pass these results to vars persistent outside the loop and update the read
			//position in buffer based on these vars only once the for loop has finished.
			for(int i=0;i<delimiters.size();i++){

			int span = delimiters[i].length();



			//std::cout << " our current delimiter number is " << i << " which is " << delimiters[i] << std::endl;
			//ssLog << " our current delimiter number is " << i << " which is " << delimiters[i] << std::endl;

			//std::cout << " span is therefore " << span << std::endl;
			//ssLog << " span is therefore " << span << std::endl;

			////std::cout << "our current position is " << iCurrPos << std::endl;

			//Be careful not to check beyond the buffer string length for
			//delimiter string characters
			if(iCurrPos+span>buffer.length()){

				//std::cout << "Looking ahead " << span << " chars would overflow the string buffer-- returning no delimiter found" << std::endl;
				//ssLog << "Looking ahead " << span << " chars would overflow the string buffer-- returning no delimiter found" << std::endl;

				//foundDelimIndex = NO_DELIM_FOUND;

				/*
				token += *currPos;
				////std::cout << "at pos " << iCurrPos << " inside isDelimiter_CStr check returns false condition. token is now " << token << std::endl;
				++currPos;
				++iCurrPos;
				*/
				continue;
			}

			std::string subStr = buffer.substr(iCurrPos,span);
			const char* cstr1 = (subStr.c_str());
			char cstr2[span+1];//sizeof(cstr1)];

			std::strncpy(cstr2,cstr1,span);//sizeof(cstr1));
			cstr2[span] = '\0'; //manually adding null terminator

			if(!isDelimiter(*currPos,delimiters[i])){
				//no delim found
				if(ParserFSM != PARSE_COMMENT_STATE){
					foundDelimIndex = NO_DELIM_FOUND;
					this->ParserFSM = PARSE_CONTENT_STATE;
				}
				/*
				//TODOx: append current char to token and increase pos by 1
				token += *currPos;
				////std::cout << "at pos " << iCurrPos << " inside isDelimiter_CStr check returns false condition. token is now " << token << std::endl;
				++currPos;
				++iCurrPos;
				*/

			}
			else{

				//std::cout << "Potential delimiter detected based on starting char.  Analyzing further..." << std::endl;
				//ssLog << "Potential delimiter detected based on starting char.  Analyzing further..." << std::endl;

				//TODOx: look ahead span characters and see if the character
				//string is a delimiter string.  If it is, move currPos and iCurrPos
				//up by span and continue.  If it is not, append current char to
				//token and continue


				//TODOx: failure seems to occur always at char index 8
				//0 through 7 are fine, but reading from 8 on gives
				//gibberish hex...
				//UPDATE: trouble appears to come from the strncpy function--
				//the vetted const char* cstr3 comes back correct for all substrings
				//but the char* cstr4 which is copied via strncpy from cstr3
				//has gibberish after index 7

				//TODO:
				//[X]1. Figure out why white space and new lines are being consumed
				//2. Implement a feature that allows for simultaneous use of sub-delimiters
				//   and delimiters, such as "n", "nn", and "nnnmnnn" -- for this it might be
				//   best to remove the break statements in the for each delimiter loop
				//   and maintain a dynamic or statically sized array of integers
				//   which correspond to the possible delimiters at a given position.
				//   Then give a rule that determines which trumps, most likely the longest
				//   one.
				//3. Implement the delimiter check as a char,std::string K,V unordered_map
				//   for faster access and also easier debugging

				//Need to refresh cstr2 within the while loop
				std::string subStr2 = buffer.substr(iCurrPos,span);

				//std::cout << "Our character string [a substring of buffer] for comparison to the delimiter is " << subStr2 << " at position " << iCurrPos << " and current delimiter is " << delimiters[i] << std::endl;
				//ssLog << "Our character string for comparison to the delimiter is " << subStr2 << " at position " << iCurrPos << " and current delimiter is " << delimiters[i] << std::endl;

				if(span == 1){
					//Delimiter string is only one char long, so we found it
					if(ParserFSM != PARSE_COMMENT_STATE){
						foundDelimIndex = i;
						this->ParserFSM = PARSE_DELIMITER_STATE;
					}
					break;
				}//End if delimiter was only one char long
				else{

					////std::cout << "our buffer substring from position " << iCurrPos << " is " << subStr2 << std::endl;
					const char* cstr3 = (subStr2.c_str());

					/*
					//WTF... why does this almost work?  Why is a spanMod necessary at all?
					int spanMod = 0;
					if(span > 8){
						spanMod = span-8;
					}
					*/

					char cstr4[span+1];//[sizeof(cstr3)+(spanMod)];

					std::strncpy(cstr4,cstr3,span);//sizeof(cstr3)+spanMod);
					cstr4[span] = '\0';

					//Sanity checking the contents of cstr2 before we pass it into
					//isDelimiter_CStr()
					//for(int x=0;x<span;x++){
						//std::cout << "cstr4 char at index " << x << " is " << cstr4[x] << "cstr3 char at index " << x << " is " << cstr3[x]<< std::endl;
						//ssLog << "cstr4 char at index " << x << " is " << cstr4[x] << "cstr3 char at index " << x << " is " << cstr3[x]<< std::endl;
					//}


					//std::cout << "Our final args for isDelimiter_CStr are (" << subStr2 << "," << span << "," << delimiters[i] << ")" << std::endl;
					//ssLog << "Our final args for isDelimiter_CStr are (" << subStr2 << "," << span << "," << delimiters[i] << ")" << std::endl;

					if(!isDelimiter_CStr(cstr4,span,delimiters[i])){

						//might have been a delimiter, but wasn't the current delimiter string

						//foundDelimIndex = NO_DELIM_FOUND;

						/*
						token += *currPos;
						////std::cout << "at pos " << iCurrPos << " inside isDelimiter_CStr check returns false condition. token is now " << token << std::endl;
						++currPos;
						++iCurrPos;
						*/
					}
					else{

						//delimiter found was the current delimiter!

						//If we are in comment state, ignore the found delimiter
						if(ParserFSM != PARSE_COMMENT_STATE){
							foundDelimIndex = i;

							this->ParserFSM = PARSE_DELIMITER_STATE;
						}
						break;

						/*
						//TODOx: update the currPos to be currPos+(span-1)
						currPos+=span;
						iCurrPos+=span;
						*/

					}
				}//End if our delimiter was longer than one char

			}//End if we are looking at a valid char to potentially start a delimiter string

			/*
			//Need to refresh cstr2 within the while loop
			std::string subStr2 = buffer.substr(iCurrPos,span);
			//////std::cout << "our buffer substring from position " << iCurrPos << " is " << subStr2 << std::endl;
			const char* cstr3 = (subStr2.c_str());
			std::strncpy(cstr2,cstr3,sizeof(cstr3));


			//////std::cout << "at pos " << iCurrPos << " about to enter isDelimiter_CStr check " << std::endl;
			//if(!isDelimiter_CStr(cstr,delimiter.length())){
				token += *currPos;
				//////std::cout << "at pos " << iCurrPos << " inside isDelimiter_CStr check returns false condition. token is now " << token << std::endl;
				++currPos;
				++iCurrPos;
			//}

			//++currPos;
			//++iCurrPos;
				*/
			}//End for delimiters.size()


			//TODOx: if a comment char string is found,
			//everything must be ignored until the end comment
			//string that matches the beginning comment string is
			//found

			//Check for comment char string
			for(int i=0;i<comments.size();i++){

				int span = comments[i].length();



				std::cout << " our current comment number is " << i << " which is " << comments[i] << std::endl;
				ssLog << " our current comment number is " << i << " which is " << comments[i] << std::endl;

				//std::cout << " span is therefore " << span << std::endl;
				ssLog << " span is therefore " << span << std::endl;


				//Be careful not to check beyond the buffer string length for
				//comment string characters
				if(iCurrPos+span>buffer.length()){

					//std::cout << "Looking ahead " << span << " chars would overflow the string buffer-- returning no delimiter found" << std::endl;
					ssLog << "Looking ahead " << span << " chars would overflow the string buffer-- returning no comment found" << std::endl;


					continue;
				}

				std::string subStr = buffer.substr(iCurrPos,span);
				const char* cstr1 = (subStr.c_str());
				char cstr2[span+1];//sizeof(cstr1)];

				std::strncpy(cstr2,cstr1,span);//sizeof(cstr1));
				cstr2[span] = '\0'; //manually adding null terminator

				if(!isDelimiter(*currPos,comments[i])){
					//no delim found
					foundCommentIndex = NO_COMMENT_FOUND;

					if(ParserFSM == PARSE_ENDCOMMENT_STATE){
						ParserFSM = PARSE_CONTENT_STATE;
					}

					/*
					if(ParserFSM == PARSE_CONTENT_STATE){
						this->ParserFSM = PARSE_CONTENT_STATE;
					}
					else if(ParserFSM == PARSE_DELIMITER_STATE){
						this->ParserFSM = PARSE_DELIMITER_STATE;
					}
					else if (ParserFSM == PARSE_COMMENT_STATE){
						this->ParserFSM = PARSE_COMMENT_STATE;
					}
					*/


				}
				else{

					//std::cout << "Potential delimiter detected based on starting char.  Analyzing further..." << std::endl;
					ssLog << "Potential comment detected based on starting char.  Analyzing further..." << std::endl;





					//Need to refresh cstr2 within the while loop
					std::string subStr2 = buffer.substr(iCurrPos,span);

					//grab an additional substr, sampling one char beyond the
					//current comment string length to check for an endcomment string
					std::string subStr_EndCheck = buffer.substr(iCurrPos,span+1);

					std::cout << "Our character string [a substring of buffer] for comparison to the comment string is " << subStr2 << " at position " << iCurrPos << " and current comment string is " << comments[i] << std::endl;
					ssLog << "Our character string for comparison to the comment is " << subStr2 << " at position " << iCurrPos << " and current comment is " << comments[i] << std::endl;

					if(span == 1){
						//Comment string is only one char long, so we found it
						foundCommentIndex = i;
						this->ParserFSM = PARSE_COMMENT_STATE;
						break;
					}//End if comment was only one char long
					else{

						////std::cout << "our buffer substring from position " << iCurrPos << " is " << subStr2 << std::endl;
						//grab cstr versions of substr2 and substr_endcheck
						const char* cstr3 = (subStr2.c_str());
						const char* cstr5 = (subStr_EndCheck.c_str());


						//create an empty char array of size comment string length +1 (for the null terminator)
						//to be populated with cstr3 [the cstr version of substr2] plus a null terminator
						//at the end.  Point of this is to trim screwy std::string
						//flotsam that throws off data comparison
						char cstr4[span+1];//[sizeof(cstr3)+(spanMod)];

						//create an empty char array of size comment string length +2 (for the '/' and the null terminator)
						//this is to be used to look for the endcomment stirng
						//populated with the current sampling
						char cstr6[span+2];

						//create an empty char array of size comment string length +2 (for the '/' and the null terminator)
						//this is to be populated with the endcomment stirng
						//for the purpose of comparing current sample against
						//endcomment string
						char cstrEndComment[span+2];

						std::strncpy(cstr4,cstr3,span);//sizeof(cstr3)+spanMod);
						cstr4[span] = '\0';

						std::strncpy(cstr6,cstr5,span+1);//sizeof(cstr3)+spanMod);
						cstr6[span+1] = '\0';

						int innerTrack = 0;
						for(int x=0;x<span+2;x++){
							if(x==1){
								cstrEndComment[x] = '/';
							}
							else{
								cstrEndComment[x] = comments[i][innerTrack]; //cstr4[innerTrack];

								innerTrack++;
							}

						}

						//Sanity checking the contents of cstr2 before we pass it into
						//isDelimiter_CStr()
						for(int x=0;x<span;x++){
							std::cout << "cstr4 char at index " << x << " is " << cstr4[x] << std::endl; //<< "cstr3 char at index " << x << " is " << cstr3[x]<< std::endl;
							ssLog << "cstr4 char at index " << x << " is " << cstr4[x] << std::endl; // "cstr4 char at index " << x << " is " << cstr4[x]<< std::endl;
						}
						for(int x=0;x<span+1;x++){
							std::cout << "cstrendcomment char at index " << x << " is " << cstrEndComment[x] << std::endl; //<< "cstr4 char at index " << x << " is " << cstr4[x] << "cstr3 char at index " << x << " is " << cstr3[x]<< std::endl;
							ssLog << "cstrendcomment char at index " << x << " is " << cstrEndComment[x] << std::endl; //<< "cstrendcomment char at index " << x << " is " << cstr3[x]<< std::endl;
						}


						std::cout << "Our final args for isDelimiter_CStr checking for a comment string are (" << subStr2 << "," << span << "," << comments[i] << ")" << std::endl;
						ssLog << "Our final args for isDelimiter_CStr checking for a comment string are (" << subStr2 << "," << span << "," << comments[i] << ")" << std::endl;

						std::cout << "Our final args for isDelimiter_CStr checking for an endcomment string are (" << subStr_EndCheck << "," << span+1 << "," << subStr_EndCheck << ")" << std::endl;
						ssLog  << "Our final args for isDelimiter_CStr checking for an endcomment string are (" << subStr_EndCheck << "," << span+1 << "," << subStr_EndCheck << ")" << std::endl;

						if(!isDelimiter_CStr(cstr4,span,comments[i]) && !isDelimiter_CStr(cstrEndComment,span+1,subStr_EndCheck)){

							//might have been a comment string, but wasn't the current comment string
							//or its paired endcomment string


						}

						else if(isDelimiter_CStr(cstrEndComment,span+1,subStr_EndCheck)){
							//[X]TODOx: what we really want to be comparing here
							//is either:
							//[X]1. cstrEndComment and subStr_EndCheck which is a substring of buffer that grabs one char beyond span
							//      in order to match the end comment string if it is present
							//2. ctsrEndComment and a vector of endcomment strings at the same index as the comment
							//string that most recently put us in the comment state

							//If we hit this condition, we've found the end comment for
							//our current comment string
							//TODOx: so check to make sure we are in comment state,
							//and iff we are go ahead and change out of comment state
							//and move the current parser position up by the end comment string length...

							//TODO: seems we are never hitting this condition as true,
							//so we never leave comment state...

							std::cout << "found endcomment string " << cstrEndComment << "we will enter endcomment state iff we are currently in comment state... our current state is " << ParserFSM << std::endl;
							ssLog << "found endcomment string " << cstrEndComment << "we will enter endcomment state iff we are currently in comment state... our current state is " << ParserFSM << std::endl;


							if(ParserFSM == PARSE_COMMENT_STATE){
								ParserFSM = PARSE_ENDCOMMENT_STATE;
								foundCommentIndex = i;

								std::cout << "found endcomment string " << cstrEndComment << std::endl;
								ssLog << "found endcomment string " << cstrEndComment << std::endl;

								/*
								iCurrPos+=span+1;
								currPos+=span+1;
								*/
							}
							else{
								std::cout << "whoops, it appears we tried to switch out of the comment state without first being in the comment state -- illegal state exception" << std::endl;
							}

						}
						else{

							//comment string found was the current comment string!
							foundCommentIndex = i;
							ParserFSM = PARSE_COMMENT_STATE;
							break;



						}
					}//End if our comment string was longer than one char

				}//End if we are looking at a valid char to potentially start a comment string


			}//End for comments.size()

			//TODOx: implement the functionality from above that was
			//commented moving the current stream position
			//based on the actual found delimiter string

			//std::cout << "Our current char being analyzed is " << *currPos << std::endl;
			//ssLog << "Our current char being analyzed is " << *currPos << std::endl;
			//std::cout << "After the for each delimiter and comment loops..." << std::endl;
			//ssLog << "After the for each delimiter and comment loops..." << std::endl;

			/**
			  *Post-processing... working with the data we gathered from
			  *the for loops above
			  *
			  *TODOx: it appears we are not changing states properly...
			  *      output suggests that we never leave comment state
			  *      after entering it the first time
			  */


			if(foundDelimIndex != NO_DELIM_FOUND){
				//std::cout << "delimiter was found!  foundDelimIndex is " << foundDelimIndex << std::endl;
				//ssLog << "delimiter was found!  foundDelimIndex is " << foundDelimIndex << std::endl;

				this->ParserFSM = PARSE_DELIMITER_STATE;

				int span = delimiters[foundDelimIndex].length();
				if(buffer[iCurrPos+span]=='\n'){
					//If we are skipping over a delimiter and
					//it has a line feed right after it, consume
					//the line feed as well
					currPos+=span+1;
					iCurrPos+=span+1;
				}
				else{
					currPos+=span;
					iCurrPos+=span;
				}
			}
			else if(foundCommentIndex != NO_COMMENT_FOUND){

				std::cout << "comment was found...  foundCommentIndex is " << foundCommentIndex << "our current char is specifically: " << *currPos << std::endl;
				ssLog << "comment was found...  foundCommentIndex is " << foundCommentIndex << "our current char is specifically: " << *currPos << std::endl;

				int span = comments[foundCommentIndex].length();
				switch(ParserFSM){
				case PARSE_CONTENT_STATE:{
					this->ParserFSM = PARSE_COMMENT_STATE;
					++currPos;
					++iCurrPos;
					break;
				}
				case PARSE_DELIMITER_STATE:{
					this->ParserFSM = PARSE_COMMENT_STATE;
					++currPos;
					++iCurrPos;
					break;
				}
				case PARSE_ENDCOMMENT_STATE:{
					this->ParserFSM = PARSE_CONTENT_STATE;
					currPos+=span+1;
					iCurrPos+=span+1;
					break;
				}
				case PARSE_COMMENT_STATE:{
					this->ParserFSM = PARSE_COMMENT_STATE;
					currPos++;
					iCurrPos++;
					break;
				}
				default:{
					std::cout << "illegal state transition-- found a comment in state " << ParserFSM << std::endl;
					ssLog << "illegal state transition-- found a comment in state " << ParserFSM << std::endl;
					break;
				}
				}


			}
			else{
				if(ParserFSM == PARSE_CONTENT_STATE){
					std::cout << "no delimiter or comment was found...  foundDelimIndex is " << foundDelimIndex << "foundCommentIndex is " << foundCommentIndex << " Since our state is content, we will record a char; specifically: " << *currPos << std::endl;
					ssLog << "no delimiter or comment was found...  foundDelimIndex is " << foundDelimIndex << "foundCommentIndex is " << foundCommentIndex << " Since our state is content, we will record a char; specifically: " << *currPos << std::endl;
					token += *currPos;
					//TODO: right about here is where we should start building our
					//resource file-- basically have a separate sResString which takes
					//the same char recorded to token above, and then when we leave PARSE_CONTENT_STATE
					//for any reason write out the contents of sResString to Resources.h preferably with a
					//story file specified name/id and reset sResString to the empty string. Repeat until
					//all token chars are parsed.
					//Alternatively, we could alter this next() method so that it only
					//returns one token [defined as content between BOF, delimiters, comments, and EOF]
					//at a time and write it out in StringTokenizer.h in its while(mvTokenizer.next() != "") loop

				}
				/*//This branch shouldn't be necessary...
				else if(ParserFSM == PARSE_ENDCOMMENT_STATE){
					this->ParserFSM = PARSE_CONTENT_STATE;
					currPos+=span+1;
					iCurrPos+=span+1;
				}
				*/
				else{
					std::cout << "no delimiter or comment was found...  foundDelimIndex is " << foundDelimIndex << "foundCommentIndex is " << foundCommentIndex << " Since our state is not content but rather " << ParserFSM << ", we will not record the current char; specifically: " << *currPos << std::endl;
					ssLog << "no delimiter or comment was found...  foundDelimIndex is " << foundDelimIndex << "foundCommentIndex is " << foundCommentIndex << " Since our state is not content but rather " << ParserFSM << ", we will not record the current char; specifically: " << *currPos << std::endl;
				}
				++currPos;
				++iCurrPos;

			}

			foundDelimIndex = NO_DELIM_FOUND; //reset to 'no delimiter found' value
			foundCommentIndex = NO_COMMENT_FOUND; //reset to 'no comment found' value

		//Commenting this while loop and using the loop in StringTokenizer instead
		}//End while currPos != buffer.end()

		//write the #endif of the include guard to Resources.h
		rw.setResContent("#endif //def RESOURCES_H_");
		rw.writeContentToResources(rw.WRITE_MODE_APPEND);


		myStaticWriteStringLog(ssLog.str());

		/*//This approach messes up the position tracking module
		  //try to find another way
		//Now we set buffer to the current tokenized string so far
		buffer = token;
		iCurrPos = 0;
		currPos = buffer.begin();
		*/

	//}//End for each delimiter in delimiters

    return token;
}

///////////////////////////////////////////////////////////////////////////////
/**return all tokens built together into a single string
 *
 *and write the metadata and data to Resources.h in the process of
 *tokenizing.
 *
 *Iff cannot find a token, then return "".
 */
///////////////////////////////////////////////////////////////////////////////
std::string Tokenizer::tokenizeAll_TreasureStringVector()
{

	std::cout << "we are now in tokenizeAll_TreasureStringVector()" << std::endl;

	token.clear();

	std::stringstream resSS;
	resSS << "static class string{" << std::endl << "public:" << std::endl;
	rw.setResContent(resSS.str());
	rw.writeContentToResources(rw.WRITE_MODE_APPEND);
	resSS.str("");

	//TODOx: Okay, delimiting by an entire string works nicely.
	//Now comes the REAL challenge -- how to handle multiple
	//string delimiters, each one of arbitrary length?
	//UPDATE: current issue with returned token being
	//APH>... is due to the fact that our two string delimiter
	//both start with the same character and for some reason span is staying
	//with the first delimiter length of 7, so <STORY> gets skipped
	//and also <PARAGR.  Also/otherwise it seems our isDelimiter_CStr() method
	//may not be working properly...

	//If only one string delimiter is specified via the
	//single string set() arg set...
	///for(int i = 0;i<delimiters.size();i++){

		if(buffer.size() <= 0) return "";           // skip if buffer is empty

		//token.clear();                              // reset token string

		//this->skipDelimiter();                      // skip leading delimiters


		std::stringstream ssLog;

		/*
		int span = delimiters[i].length();

		std::string subStr = buffer.substr(iCurrPos,span);
		const char* cstr1 = (subStr.c_str());
		char cstr2[sizeof(cstr1)];

		std::strncpy(cstr2,cstr1,sizeof(cstr1));

		this->skipDelimiter_CStr(cstr2,span,delimiters[i]);
		*/


		/*
		//Skip leading delimiters
		for(int i=0;i<delimiters.size();i++){
			//[X]TODOx: our APH> result is caused by this here--
			//we only look at the first char and then iff
			//it is a match to delimiters[0][0], we declare it
			//a delimiter immediately for span characters.  This
			//cause <PARAGR to be read as delimiter to skip just
			//because it starts with a left-angle bracket like <STORY>
		//this->skipDelimiter(delimiters[i]);
			int span = delimiters[i].length();

			std::string subStr = buffer.substr(iCurrPos,span);
			const char* cstr1 = (subStr.c_str());
			char cstr2[sizeof(cstr1)];

			std::strncpy(cstr2,cstr1,sizeof(cstr1));

			//Check to see if the current char could be starting a
			//deliverable
			//std::cout << " possibly skipping leading delimiter -- the current char is " << *currPos << " and the target starting delim char is " << delimiters[i][0] << std::endl;
			ssLog << " possibly skipping leading delimiter -- the current char is " << *currPos << " and the target starting delim char is " << delimiters[i][0] << std::endl;
			if(isDelimiter(*currPos,delimiters[i])){

				this->skipDelimiter_CStr(cstr2,span,delimiters[i]);

			}

		}
		*/

		/*
		std::string subStr2 = buffer.substr(iCurrPos,span);

	   //// //std::cout << "our buffer substring from position " << iCurrPos << " is " << subStr2 << std::endl;

		const char* cstr3 = (subStr2.c_str());
		std::strncpy(cstr2,cstr3,sizeof(cstr3));
		*/

		// append each char to token string until it meets delimiter
		//TODOx: look for the first character of the delimiter string
		//iff one is found, look ahead delimiter.length() span to see
		//if a complete delimiter string is present

		int foundDelimIndex = NO_DELIM_FOUND;
		int foundCommentIndex = NO_COMMENT_FOUND;
		this->ParserFSM = PARSE_CONTENT_STATE;

		std::cout << "about to enter while currPos != buffer.end()" << std::endl;

		////Commenting this while loop and using the loop in StringTokenizer instead
		while(currPos != buffer.end() )//&& //!isDelimiter_CStr(cstr2,delimiter.length()))//!isDelimiter(*currPos))
		{


			//TODOx: so here is the cause of our current problem, where we
			//can skip at least one leading delimiter but later ones are
			//missed-- we need each char of the source buffer to be
			//analyzed wrt each individual delimiter; the way we have it here
			//current pos is updated within the for loop, meaning the
			//second delim will be looking at a different character.  Most likely
			//what we're currently seeing is < read at second <STORY> tag,
			//but current delim is </STORY> so the <STORY> tag returns false
			//for being a delimiter string.  What we should do instead perhpas is
			//factor out position modification to after the for loop, based on
			//analyses prepared within the for loop.
			//Essentially, foreach(char in buffer){is char the start of current delim? if yes, is current char + current span exactly equal to the current delim? ...
			//Pass these results to vars persistent outside the loop and update the read
			//position in buffer based on these vars only once the for loop has finished.
			for(int i=0;i<tsvDelimiters.size();i++){

				std::cout << "for loop " << i << " of " << tsvDelimiters.size() << "..." << std::endl;

			int totalSpan = tsvDelimiters[i].getContentString().length() + tsvDelimiters[i].getTreasure();
			int stringSpan = tsvDelimiters[i].getContentString().length();


			//std::cout << " our current delimiter number is " << i << " which is " << delimiters[i] << std::endl;
			//ssLog << " our current delimiter number is " << i << " which is " << delimiters[i] << std::endl;

			//std::cout << " span is therefore " << span << std::endl;
			//ssLog << " span is therefore " << span << std::endl;

			////std::cout << "our current position is " << iCurrPos << std::endl;

			//Be careful not to check beyond the buffer string length for
			//delimiter string characters
			if(iCurrPos+totalSpan>buffer.length()){

				//std::cout << "Looking ahead " << span << " chars would overflow the string buffer-- returning no delimiter found" << std::endl;
				//ssLog << "Looking ahead " << span << " chars would overflow the string buffer-- returning no delimiter found" << std::endl;

				//foundDelimIndex = NO_DELIM_FOUND;

				/*
				token += *currPos;
				////std::cout << "at pos " << iCurrPos << " inside isDelimiter_CStr check returns false condition. token is now " << token << std::endl;
				++currPos;
				++iCurrPos;
				*/
				continue;
			}

			std::string subStr = buffer.substr(iCurrPos,stringSpan);
			const char* cstr1 = (subStr.c_str());
			char cstr2[stringSpan+1];//sizeof(cstr1)];

			std::strncpy(cstr2,cstr1,stringSpan);//sizeof(cstr1));

			//Replace whatever is just after the second to last char of the content string
			//with a right angle bracket for comparison below against
			//the full content string
			cstr2[stringSpan-1] = '>';
			cstr2[stringSpan] = '\0'; //manually adding null terminator

			//TODOx: fix this and beyond for treasure strings, writing out
			//metadata when a chunk of it is available
			//chunk syntax given as
			//<0 or more defined tag item>='<value to be written to Resources.h>'
			if(!isDelimiter(*currPos,tsvDelimiters[i].getContentString())){
				//no delim found
				if(ParserFSM != PARSE_COMMENT_STATE){
					foundDelimIndex = NO_DELIM_FOUND;
					this->ParserFSM = PARSE_CONTENT_STATE;
				}
				/*
				//TODOx: append current char to token and increase pos by 1
				token += *currPos;
				////std::cout << "at pos " << iCurrPos << " inside isDelimiter_CStr check returns false condition. token is now " << token << std::endl;
				++currPos;
				++iCurrPos;
				*/

			}
			else{

				//std::cout << "Potential delimiter detected based on starting char.  Analyzing further..." << std::endl;
				//ssLog << "Potential delimiter detected based on starting char.  Analyzing further..." << std::endl;

				//TODOx: look ahead span characters and see if the character
				//string is a delimiter string.  If it is, move currPos and iCurrPos
				//up by span and continue.  If it is not, append current char to
				//token and continue


				//TODOx: failure seems to occur always at char index 8
				//0 through 7 are fine, but reading from 8 on gives
				//gibberish hex...
				//UPDATE: trouble appears to come from the strncpy function--
				//the vetted const char* cstr3 comes back correct for all substrings
				//but the char* cstr4 which is copied via strncpy from cstr3
				//has gibberish after index 7

				//TODO:
				//[X]1. Figure out why white space and new lines are being consumed
				//2. Implement a feature that allows for simultaneous use of sub-delimiters
				//   and delimiters, such as "n", "nn", and "nnnmnnn" -- for this it might be
				//   best to remove the break statements in the for each delimiter loop
				//   and maintain a dynamic or statically sized array of integers
				//   which correspond to the possible delimiters at a given position.
				//   Then give a rule that determines which trumps, most likely the longest
				//   one.
				//3. Implement the delimiter check as a char,std::string K,V unordered_map
				//   for faster access and also easier debugging

				//Need to refresh cstr2 within the while loop
				std::string subStr2 = buffer.substr(iCurrPos,stringSpan);

				//std::cout << "Our character string [a substring of buffer] for comparison to the delimiter is " << subStr2 << " at position " << iCurrPos << " and current delimiter is " << delimiters[i] << std::endl;
				//ssLog << "Our character string for comparison to the delimiter is " << subStr2 << " at position " << iCurrPos << " and current delimiter is " << delimiters[i] << std::endl;

				if(stringSpan == 1){
					//Delimiter string is only one char long, so we found it
					if(ParserFSM != PARSE_COMMENT_STATE){
						foundDelimIndex = i;
						this->ParserFSM = PARSE_DELIMITER_STATE;
					}
					break;
				}//End if delimiter was only one char long
				else{

					////std::cout << "our buffer substring from position " << iCurrPos << " is " << subStr2 << std::endl;
					const char* cstr3 = (subStr2.c_str());

					/*
					//WTF... why does this almost work?  Why is a spanMod necessary at all?
					int spanMod = 0;
					if(span > 8){
						spanMod = span-8;
					}
					*/



					char cstr4[stringSpan+1];//[sizeof(cstr3)+(spanMod)];

					std::strncpy(cstr4,cstr3,stringSpan);//sizeof(cstr3)+spanMod);
					cstr4[stringSpan-1] = '>';
					cstr4[stringSpan] = '\0';

					//Sanity checking the contents of cstr2 before we pass it into
					//isDelimiter_CStr()
					//for(int x=0;x<span;x++){
						//std::cout << "cstr4 char at index " << x << " is " << cstr4[x] << "cstr3 char at index " << x << " is " << cstr3[x]<< std::endl;
						//ssLog << "cstr4 char at index " << x << " is " << cstr4[x] << "cstr3 char at index " << x << " is " << cstr3[x]<< std::endl;
					//}


					//std::cout << "Our final args for isDelimiter_CStr are (" << subStr2 << "," << span << "," << delimiters[i] << ")" << std::endl;
					//ssLog << "Our final args for isDelimiter_CStr are (" << subStr2 << "," << span << "," << delimiters[i] << ")" << std::endl;

					if(!isDelimiter_CStr(cstr4,stringSpan,tsvDelimiters[i].getContentString())){

						//might have been a delimiter, but wasn't the current delimiter string

						//foundDelimIndex = NO_DELIM_FOUND;

						/*
						token += *currPos;
						////std::cout << "at pos " << iCurrPos << " inside isDelimiter_CStr check returns false condition. token is now " << token << std::endl;
						++currPos;
						++iCurrPos;
						*/
					}
					else{

						//delimiter found was the current delimiter!

						//TODO: this condition here, and only this condition here,
						//are where we should to look for metadata up to
						//treasurestring<int>.getTreasure() chars of it.

						//Read and write to Resources.h the metadata when a chunk of it is available
						//chunk syntax given as
						//<0 or more defined tag item>='<value to be written to Resources.h>'

						//If we are in comment state, ignore the found delimiter
						if(ParserFSM != PARSE_COMMENT_STATE){
							foundDelimIndex = i;

							std::cout << "we are about to begin looking for metadata tags in treasure space of " << tsvDelimiters[i].getTreasure() << std::endl;


							for(int tcount = 0; tcount < tsvDelimiters[i].getTreasure(); tcount++){
								//iterating over potential metadata here
								//TODOx: search against the tagMap for legal metadata tags
								//before the '>' char.  If the '>' char is found, quit the
								//loop
								char endChar;
								char currentChar = buffer[iCurrPos+tcount];//.substr(iCurrPos,iCurrPos+tcount);//tsvDelimiters[i].getContentString()[tcount];

								std::cout << "we are inside the tsvDelimiters loop, on iteration " << tcount << " of " << tsvDelimiters[i].getTreasure() << std::endl;

								std::cout << "currentChar is " << currentChar << std::endl;

								if(currentChar == '>'){
									std::cout << "found '>' which ends the delimiter string" << std::endl;
									ssLog << "found '>' which ends the delimiter string" << std::endl;
									break;
								}

								std::cout << "past the currentChar check" << std::endl;

								resSS.str("");

								std::cout << "past the resSS reset" << std::endl;
								bool bIsTagFound = false;
								bool bIsLegalTag = false;

								std::cout << "about to assign tagspan length" << std::endl;

								//grab the length of our current tag
								//TODOx: our silent crash is related to accessing members of mvTagsVector at i
								//because i goes beyond the max tags in tagsVector...
								for(int tagsCounter=0;tagsCounter<mvTagsVector.size();tagsCounter++){

								//The tagSpan is the length of the tag itself, such as id at length 2
								int tagSpan = mvTagsVector[tagsCounter].length();

								//tagSpanExt is the char length of the syntax expected after a given tag
								//such as =' after id for assignment
								//hard-coding this for now, but syntax nodes like this should be part of
								//a treasurestring used for the tags instead of a basic string...
								int tagSpanExt = tagSpan + 2;

								std::cout << "about to look into tagsvector" << std::endl;
								ssLog << "about to look into tagsvector" << std::endl;
								std::cout << "about to check the first char of the current tag, " << mvTagsVector[tagsCounter][0] << ", with the current sampled char " << currentChar << std::endl;
								ssLog << "about to check the first char of the current tag, " << mvTagsVector[tagsCounter][0] << ", with the current sampled char " << currentChar << std::endl;
								//determine if current char == first char of tag, indicating a possible tag
								if(mvTagsVector[tagsCounter][0] == currentChar){
									std::cout << "we have found the first char, " << currentChar << ", of tag " << mvTagsVector[tagsCounter] << std::endl;
									ssLog << "we have found the first char, " << currentChar << ", of tag " << mvTagsVector[tagsCounter] << std::endl;
									//iff we might be looking at a tag, make sure we are looking
									//at a complete tag
									std::cout << "tsvDelimiters[i].getContentString().length() is " << tsvDelimiters[i].getContentString().length() << " and tcount+tagSpan is " << (tcount+tagSpan) << std::endl;
									ssLog << "tsvDelimiters[i].getContentString().length() is " << tsvDelimiters[i].getContentString().length() << " and tcount+tagSpan is " << (tcount+tagSpan) << std::endl;
									std::string s1 = "";
									std::string s2 = "";

									/*//TODOx: the below log shows how we aren't sampling ahead in the buffer quite rightly...
									 * about to look into tagsvector
										about to check the first char of the current tag, i, with the current sampled char i
										we have found the first char, i, of tag id
										tsvDelimiters[i].getContentString().length() is 6 and tcount+tagSpan is 8
										bIsTagFound is false
									 */

									//checking for potential buffer overflow, of course
									//if(tsvDelimiters[i].getContentString().length() >= tcount+tagSpan){ //this was a legacy check, I think
									if(buffer.length() >= iCurrPos+tcount+tagSpan){
										s1 = mvTagsVector[tagsCounter];
										std::cout << "we will sample the buffer using iCurrPos: " << iCurrPos << " tcount: " << tcount << " and tagspan: " << tagSpan << std::endl;
										ssLog << "we will sample the buffer using iCurrPos: " << iCurrPos << " tcount: " << tcount << " and tagspan: " << tagSpan << std::endl;
										//TODOx: the buffer is not sampled correctly here -- we're getting way too much text in the log for s2...
										s2 = buffer.substr(iCurrPos+tcount,tagSpan);//tsvDelimiters[i].getContentString().substr(tcount,tagSpan);

										/*
										std::cout << "tagsVector[" << tagsCounter << "] is " << s1 << " and tsvDelimiters[" << i << "].getContentString().substr(" << tcount << "," << tcount+tagSpan << ") is " << s2 << std::endl;
										ssLog << "tagsVector[" << tagsCounter << "] is " << s1 << " and tsvDelimiters[" << i << "].getContentString().substr(" << tcount << "," << tagSpan << " is " << s2 << std::endl;
										*/

										std::cout << "tagsVector[" << tagsCounter << "] is " << s1 << " and buffer.substr(" << iCurrPos+tcount << "," << iCurrPos+tcount+tagSpan << ") is " << s2 << std::endl;
										ssLog << "tagsVector[" << tagsCounter << "] is " << s1 << " and buffer.substr(" << iCurrPos+tcount << "," << iCurrPos+tcount+tagSpan << ") is " << s2 << std::endl;

										bIsTagFound = strEqual(s1,s2);//((mvTagsVector[i]),(tsvDelimiters[i].getContentString().substr(tcount,tagSpan)));

										std::cout << "bIsTagFound set with the results of strEqual(" << s1 << "," << s2 << ") is " << bIsTagFound << std::endl;
										ssLog << "bIsTagFound set with the results of strEqual(" << s1 << "," << s2 << ") is " << bIsTagFound << std::endl;
									}
									else{
										std::cout << "bIsTagFound is false" << std::endl;
										ssLog << "bIsTagFound is false" << std::endl;
										//not enough room for the look-ahead sample
										//to be our target tag
										bIsTagFound = false;
									}



									if(bIsTagFound){
										std::cout << "found a tag; now to verify legality..." << std::endl;
										ssLog << "found a tag; now to verify legality..." << std::endl;
										//if legal, will hold =' to be followed by <value> and then close '
										s2 = buffer.substr(iCurrPos+tcount+tagSpan,2);
										std::cout << "setting s2, which is to be compared with char set /='/ returns " << s2 << std::endl;
										ssLog << "setting s2, which is to be compared with char set /='/ returns " << s2 << std::endl;
										if(strEqual(s2,"='")){
											bIsLegalTag = true;

										}

										if(bIsLegalTag){
											std::cout << "found a legal tag" << std::endl;
											ssLog << "found a legal tag" << std::endl;
											//begin writing to resources.h
											int valStringCharCounter = 0;
											char singleQuoteCount = 0;
											resSS << "static std::string* ";
											while(currentChar != '\''){
												//Now we are recording the actual metadata
												//value, so we need to skip the assignment syntax
												//node, e.g. chars =' otherwise we get static std:string* ='=
												//So we use tagSpanExt instead of tagSpan
												currentChar = buffer[iCurrPos+tcount+tagSpanExt+valStringCharCounter];
												valStringCharCounter++;
												if(currentChar != '\''){
													resSS << currentChar;
												}

											}

											resSS << "= new std::string(\"\\";

											//Resources::string::testtext;


											//[LATER'd]TODOx: derive an integer code from the unique id and
											//the byte offset in the file where the string to reference is located...

											//TODOx: instead, see the format in ResourceWriter.h
											//which calls for ading the string data directly here
											//since it is being added to a static string pointer
											//we can recycle the content and keep the WORD sized pointer
											//pretty spacially-safely throughout the application run.

											//TODO: next step is to add the token we're about to read
											//after we've read it to resSS and then append resSS to
											//Resources.h and reset resSS via resSS.str = "";

										}//End if tag's value set syntax is legal and, if so, value has been written to resSS
									}//End if tag found



									//resSS << mvTagsVector[i] << std::endl;
									//TODOx: finish putting the tag chunk into the
									//res stringstream, see syntax above...


									rw.setResContent(resSS.str());
									rw.writeContentToResources(rw.WRITE_MODE_APPEND);
									resSS.str("");

									std::cout << "end possible tag space" << std::endl;

								}//end if possible tag
								else{
									std::cout << "no possible tag found over char " << currentChar << " considering tag " << mvTagsVector[tagsCounter] << std::endl;
								}

								std::cout << "just processed tag " << tagsCounter << " and we found that possibleTag was: " << bIsTagFound << " and legalTag was: " << bIsLegalTag << std::endl;

								}//End for tags in tagsvector

								std::cout << "at char number " << tcount << " in treasure space of size " << tsvDelimiters[i].getTreasure() << std::endl;

							}//end for treasure space in current delimiter

							int tempTreasureVal = ((int)tsvDelimiters[i].getTreasure());
							std::cout << "end of for delimiter " << tsvDelimiters[i].getContentString() << " which has treasure attribute of " << tempTreasureVal << std::endl;

							this->ParserFSM = PARSE_DELIMITER_STATE;
						}//End if not comment state

						//break out of for each delimiter in delims vector loop
						//since we just found a delimiter successfully
						break; //why was this here?  because we found the right delimiter at this point, so we stop looking for it in the delims vector

						/*
						//TODOx: update the currPos to be currPos+(span-1)
						currPos+=span;
						iCurrPos+=span;
						*/

					}//End if current delimiter sample is the target delimiter
				}//End if our delimiter was longer than one char

			}//End if we are looking at a valid char to potentially start a delimiter string

			/*
			//Need to refresh cstr2 within the while loop
			std::string subStr2 = buffer.substr(iCurrPos,span);
			//////std::cout << "our buffer substring from position " << iCurrPos << " is " << subStr2 << std::endl;
			const char* cstr3 = (subStr2.c_str());
			std::strncpy(cstr2,cstr3,sizeof(cstr3));


			//////std::cout << "at pos " << iCurrPos << " about to enter isDelimiter_CStr check " << std::endl;
			//if(!isDelimiter_CStr(cstr,delimiter.length())){
				token += *currPos;
				//////std::cout << "at pos " << iCurrPos << " inside isDelimiter_CStr check returns false condition. token is now " << token << std::endl;
				++currPos;
				++iCurrPos;
			//}

			//++currPos;
			//++iCurrPos;
				*/

		}//End for delimiters.size()


			//TODOx: if a comment char string is found,
			//everything must be ignored until the end comment
			//string that matches the beginning comment string is
			//found

			//Check for comment char string
			for(int i=0;i<tsvComments.size();i++){

				int span = tsvComments[i].getContentString().length();



				std::cout << " our current comment number is " << i << " which is " << tsvComments[i].getContentString() << std::endl;
				ssLog << " our current comment number is " << i << " which is " << tsvComments[i].getContentString() << std::endl;

				//std::cout << " span is therefore " << span << std::endl;
				ssLog << " span is therefore " << span << std::endl;


				//Be careful not to check beyond the buffer string length for
				//comment string characters
				if(iCurrPos+span>buffer.length()){

					//std::cout << "Looking ahead " << span << " chars would overflow the string buffer-- returning no delimiter found" << std::endl;
					ssLog << "Looking ahead " << span << " chars would overflow the string buffer-- returning no comment found" << std::endl;


					continue;
				}

				std::string subStr = buffer.substr(iCurrPos,span);
				const char* cstr1 = (subStr.c_str());
				char cstr2[span+1];//sizeof(cstr1)];

				std::strncpy(cstr2,cstr1,span);//sizeof(cstr1));
				cstr2[span] = '\0'; //manually adding null terminator

				if(!isDelimiter(*currPos,tsvComments[i].getContentString())){
					//no delim found
					foundCommentIndex = NO_COMMENT_FOUND;

					if(ParserFSM == PARSE_ENDCOMMENT_STATE){
						ParserFSM = PARSE_CONTENT_STATE;
					}

					/*
					if(ParserFSM == PARSE_CONTENT_STATE){
						this->ParserFSM = PARSE_CONTENT_STATE;
					}
					else if(ParserFSM == PARSE_DELIMITER_STATE){
						this->ParserFSM = PARSE_DELIMITER_STATE;
					}
					else if (ParserFSM == PARSE_COMMENT_STATE){
						this->ParserFSM = PARSE_COMMENT_STATE;
					}
					*/


				}
				else{

					//std::cout << "Potential delimiter detected based on starting char.  Analyzing further..." << std::endl;
					ssLog << "Potential comment detected based on starting char.  Analyzing further..." << std::endl;





					//Need to refresh cstr2 within the while loop
					std::string subStr2 = buffer.substr(iCurrPos,span);

					//grab an additional substr, sampling one char beyond the
					//current comment string length to check for an endcomment string
					std::string subStr_EndCheck = buffer.substr(iCurrPos,span+1);

					std::cout << "Our character string [a substring of buffer] for comparison to the comment string is " << subStr2 << " at position " << iCurrPos << " and current comment string is " << tsvComments[i].getContentString() << std::endl;
					ssLog << "Our character string for comparison to the comment is " << subStr2 << " at position " << iCurrPos << " and current comment is " << tsvComments[i].getContentString() << std::endl;

					if(span == 1){
						//Comment string is only one char long, so we found it
						foundCommentIndex = i;
						this->ParserFSM = PARSE_COMMENT_STATE;
						break;
					}//End if comment was only one char long
					else{

						////std::cout << "our buffer substring from position " << iCurrPos << " is " << subStr2 << std::endl;
						//grab cstr versions of substr2 and substr_endcheck
						const char* cstr3 = (subStr2.c_str());
						const char* cstr5 = (subStr_EndCheck.c_str());


						//create an empty char array of size comment string length +1 (for the null terminator)
						//to be populated with cstr3 [the cstr version of substr2] plus a null terminator
						//at the end.  Point of this is to trim screwy std::string
						//flotsam that throws off data comparison
						char cstr4[span+1];//[sizeof(cstr3)+(spanMod)];

						//create an empty char array of size comment string length +2 (for the '/' and the null terminator)
						//this is to be used to look for the endcomment stirng
						//populated with the current sampling
						char cstr6[span+2];

						//create an empty char array of size comment string length +2 (for the '/' and the null terminator)
						//this is to be populated with the endcomment stirng
						//for the purpose of comparing current sample against
						//endcomment string
						char cstrEndComment[span+2];

						std::strncpy(cstr4,cstr3,span);//sizeof(cstr3)+spanMod);
						cstr4[span] = '\0';

						std::strncpy(cstr6,cstr5,span+1);//sizeof(cstr3)+spanMod);
						cstr6[span+1] = '\0';

						int innerTrack = 0;
						for(int x=0;x<span+2;x++){
							if(x==1){
								cstrEndComment[x] = '/';
							}
							else{
								cstrEndComment[x] = tsvComments[i].getContentString()[innerTrack]; //cstr4[innerTrack];

								innerTrack++;
							}

						}

						//Sanity checking the contents of cstr2 before we pass it into
						//isDelimiter_CStr()
						for(int x=0;x<span;x++){
							std::cout << "cstr4 char at index " << x << " is " << cstr4[x] << std::endl; //<< "cstr3 char at index " << x << " is " << cstr3[x]<< std::endl;
							ssLog << "cstr4 char at index " << x << " is " << cstr4[x] << std::endl; // "cstr4 char at index " << x << " is " << cstr4[x]<< std::endl;
						}
						for(int x=0;x<span+1;x++){
							std::cout << "cstrendcomment char at index " << x << " is " << cstrEndComment[x] << std::endl; //<< "cstr4 char at index " << x << " is " << cstr4[x] << "cstr3 char at index " << x << " is " << cstr3[x]<< std::endl;
							ssLog << "cstrendcomment char at index " << x << " is " << cstrEndComment[x] << std::endl; //<< "cstrendcomment char at index " << x << " is " << cstr3[x]<< std::endl;
						}


						std::cout << "Our final args for isDelimiter_CStr checking for a comment string are (" << subStr2 << "," << span << "," << tsvComments[i].getContentString() << ")" << std::endl;
						ssLog << "Our final args for isDelimiter_CStr checking for a comment string are (" << subStr2 << "," << span << "," << tsvComments[i].getContentString() << ")" << std::endl;

						std::cout << "Our final args for isDelimiter_CStr checking for an endcomment string are (" << subStr_EndCheck << "," << span+1 << "," << subStr_EndCheck << ")" << std::endl;
						ssLog  << "Our final args for isDelimiter_CStr checking for an endcomment string are (" << subStr_EndCheck << "," << span+1 << "," << subStr_EndCheck << ")" << std::endl;

						if(!isDelimiter_CStr(cstr4,span,tsvComments[i].getContentString()) && !isDelimiter_CStr(cstrEndComment,span+1,subStr_EndCheck)){

							//might have been a comment string, but wasn't the current comment string
							//or its paired endcomment string


						}

						else if(isDelimiter_CStr(cstrEndComment,span+1,subStr_EndCheck)){
							//[X]TODOx: what we really want to be comparing here
							//is either:
							//[X]1. cstrEndComment and subStr_EndCheck which is a substring of buffer that grabs one char beyond span
							//      in order to match the end comment string if it is present
							//2. ctsrEndComment and a vector of endcomment strings at the same index as the comment
							//string that most recently put us in the comment state

							//If we hit this condition, we've found the end comment for
							//our current comment string
							//TODOx: so check to make sure we are in comment state,
							//and iff we are go ahead and change out of comment state
							//and move the current parser position up by the end comment string length...

							//TODOx: seems we are never hitting this condition as true,
							//so we never leave comment state...

							std::cout << "found endcomment string " << cstrEndComment << "we will enter endcomment state iff we are currently in comment state... our current state is " << ParserFSM << std::endl;
							ssLog << "found endcomment string " << cstrEndComment << "we will enter endcomment state iff we are currently in comment state... our current state is " << ParserFSM << std::endl;


							if(ParserFSM == PARSE_COMMENT_STATE){
								ParserFSM = PARSE_ENDCOMMENT_STATE;
								foundCommentIndex = i;

								std::cout << "found endcomment string " << cstrEndComment << std::endl;
								ssLog << "found endcomment string " << cstrEndComment << std::endl;

								/*
								iCurrPos+=span+1;
								currPos+=span+1;
								*/
							}
							else{
								std::cout << "whoops, it appears we tried to switch out of the comment state without first being in the comment state -- illegal state exception" << std::endl;
							}

						}
						else{

							//comment string found was the current comment string!
							foundCommentIndex = i;
							ParserFSM = PARSE_COMMENT_STATE;
							break;



						}
					}//End if our comment string was longer than one char

				}//End if we are looking at a valid char to potentially start a comment string


			}//End for comments.size()

			//TODOx: implement the functionality from above that was
			//commented moving the current stream position
			//based on the actual found delimiter string

			//std::cout << "Our current char being analyzed is " << *currPos << std::endl;
			//ssLog << "Our current char being analyzed is " << *currPos << std::endl;
			//std::cout << "After the for each delimiter and comment loops..." << std::endl;
			//ssLog << "After the for each delimiter and comment loops..." << std::endl;

			/**
			  *Post-processing... working with the data we gathered from
			  *the for loops above
			  *
			  *TODOx: it appears we are not changing states properly...
			  *      output suggests that we never leave comment state
			  *      after entering it the first time
			  */


			if(foundDelimIndex != NO_DELIM_FOUND){
				//std::cout << "delimiter was found!  foundDelimIndex is " << foundDelimIndex << std::endl;
				//ssLog << "delimiter was found!  foundDelimIndex is " << foundDelimIndex << std::endl;

				this->ParserFSM = PARSE_DELIMITER_STATE;

				//no longer content state, so write out and reset resSS
				rw.setResContent(resSS.str());
				rw.writeContentToResources(rw.WRITE_MODE_APPEND);
				resSS.str("");

				int span = tsvDelimiters[foundDelimIndex].getContentString().length();
				if(buffer[iCurrPos+span]=='\n'){
					//If we are skipping over a delimiter and
					//it has a line feed right after it, consume
					//the line feed as well
					currPos+=span+1;
					iCurrPos+=span+1;
				}
				else{
					currPos+=span;
					iCurrPos+=span;
				}
			}
			else if(foundCommentIndex != NO_COMMENT_FOUND){

				std::cout << "comment was found...  foundCommentIndex is " << foundCommentIndex << "our current char is specifically: " << *currPos << std::endl;
				ssLog << "comment was found...  foundCommentIndex is " << foundCommentIndex << "our current char is specifically: " << *currPos << std::endl;

				int span = tsvComments[foundCommentIndex].getContentString().length();
				switch(ParserFSM){
				case PARSE_CONTENT_STATE:{
					this->ParserFSM = PARSE_COMMENT_STATE;
					//no longer content state, so write out and reset resSS
					rw.setResContent(resSS.str());
					rw.writeContentToResources(rw.WRITE_MODE_APPEND);
					resSS.str("");
					++currPos;
					++iCurrPos;
					break;
				}
				case PARSE_DELIMITER_STATE:{
					this->ParserFSM = PARSE_COMMENT_STATE;
					//no longer content state, so write out and reset resSS
					rw.setResContent(resSS.str());
					rw.writeContentToResources(rw.WRITE_MODE_APPEND);
					resSS.str("");
					++currPos;
					++iCurrPos;
					break;
				}
				case PARSE_ENDCOMMENT_STATE:{
					this->ParserFSM = PARSE_CONTENT_STATE;
					currPos+=span+1;
					iCurrPos+=span+1;
					break;
				}
				case PARSE_COMMENT_STATE:{
					this->ParserFSM = PARSE_COMMENT_STATE;
					//no longer content state, so write out and reset resSS
					rw.setResContent(resSS.str());
					rw.writeContentToResources(rw.WRITE_MODE_APPEND);
					resSS.str("");
					currPos++;
					iCurrPos++;
					break;
				}
				default:{
					std::cout << "illegal state transition-- found a comment in state " << ParserFSM << std::endl;
					ssLog << "illegal state transition-- found a comment in state " << ParserFSM << std::endl;
					//no longer content state, so write out and reset resSS
					rw.setResContent(resSS.str());
					rw.writeContentToResources(rw.WRITE_MODE_APPEND);
					resSS.str("");
					break;
				}
				}


			}
			else{
				if(ParserFSM == PARSE_CONTENT_STATE){
					std::cout << "no delimiter or comment was found...  foundDelimIndex is " << foundDelimIndex << "foundCommentIndex is " << foundCommentIndex << " Since our state is content, we will record a char; specifically: " << *currPos << std::endl;
					ssLog << "no delimiter or comment was found...  foundDelimIndex is " << foundDelimIndex << "foundCommentIndex is " << foundCommentIndex << " Since our state is content, we will record a char; specifically: " << *currPos << std::endl;
					token += *currPos;

					//start recording chars to be written to Res.h
					//only write them out and reset resSS when state
					//changes from CONTENT to anything else

					//If we are writing a line feed char,
					//be sure to include an escape char too so that
					//the string literal can be built together
					//across multiple lines

					if(*currPos < 32){
						resSS << '\\';
					}
					resSS << *currPos;
					/*
					rw.setResContent(resSS.str());
					rw.writeContentToResources(rw.WRITE_MODE_APPEND);
					resSS.str("");
					*/
					//TODO: right about here is where we should start building our
					//resource file-- basically have a separate sResString which takes
					//the same char recorded to token above, and then when we leave PARSE_CONTENT_STATE
					//for any reason write out the contents of sResString to Resources.h preferably with a
					//story file specified name/id and reset sResString to the empty string. Repeat until
					//all token chars are parsed.
					//Alternatively, we could alter this next() method so that it only
					//returns one token [defined as content between BOF, delimiters, comments, and EOF]
					//at a time and write it out in StringTokenizer.h in its while(mvTokenizer.next() != "") loop
					//UPDATE: almost there -- still grabbing a bit of metadata
					//and also we need to resolve the newline issue...
					//UPDATE: adding the escape chars does help the newline issue,
					//but doesn't solve it as too many newlines are being written...
					//TODO: need to make sure that we only write data to res.h if a legal
					//tag was found which tells the program how to store said data (what datatype, identifier, etc.)
					//AND that we recognize the end of a given legal tag's scope so that
					//the validation and writing process can start afresh...

				}
				/*//This branch shouldn't be necessary...
				else if(ParserFSM == PARSE_ENDCOMMENT_STATE){
					this->ParserFSM = PARSE_CONTENT_STATE;
					currPos+=span+1;
					iCurrPos+=span+1;
				}
				*/
				else{
					std::cout << "no delimiter or comment was found...  foundDelimIndex is " << foundDelimIndex << "foundCommentIndex is " << foundCommentIndex << " Since our state is not content but rather " << ParserFSM << ", we will not record the current char; specifically: " << *currPos << std::endl;
					ssLog << "no delimiter or comment was found...  foundDelimIndex is " << foundDelimIndex << "foundCommentIndex is " << foundCommentIndex << " Since our state is not content but rather " << ParserFSM << ", we will not record the current char; specifically: " << *currPos << std::endl;
					//no longer content state, so write out and reset resSS
					rw.setResContent(resSS.str());
					rw.writeContentToResources(rw.WRITE_MODE_APPEND);
					resSS.str("");
				}
				++currPos;
				++iCurrPos;

			}

			foundDelimIndex = NO_DELIM_FOUND; //reset to 'no delimiter found' value
			foundCommentIndex = NO_COMMENT_FOUND; //reset to 'no comment found' value

		//Commenting this while loop and using the loop in StringTokenizer instead
		}//End while currPos != buffer.end()

		//close off the last resource read in
		resSS << "\")" << std::endl << "};" << std::endl << "};" << std::endl;
		rw.setResContent(resSS.str());
		rw.writeContentToResources(rw.WRITE_MODE_APPEND);
		resSS.str("");

		//write the #endif of the include guard to Resources.h
		rw.setResContent("#endif //def RESOURCES_H_");
		rw.writeContentToResources(rw.WRITE_MODE_APPEND);


		myStaticWriteStringLog(ssLog.str());

		/*//This approach messes up the position tracking module
		  //try to find another way
		//Now we set buffer to the current tokenized string so far
		buffer = token;
		iCurrPos = 0;
		currPos = buffer.begin();
		*/

	//}//End for each delimiter in delimiters


		std::string* test = new std::string("The queen of the\
				Mercurial Rose shall have breasts greater than or\
				equal to a C++ cup!");
		std::cout << *test << std::endl;
    return token;
}


//return nextt token, or "" if no more tokens to pull
std::string Tokenizer::next(){
	token = "";
	//TODO: fill in the details for this'n later; mainly using tokenizeAll() above for now
	return token;

}

bool Tokenizer::strEqual(std::string& str1_ref,std::string& str2_ref){
	int str1Len = str1_ref.length();
	int str2Len = str2_ref.length();

	//check the length first to make sure there is a match
	if(str1Len != str2Len){
		return false;
	}

	//now check char by char for equality
	//quit immediately if inequality found
	for(int charCount=0;charCount<str1Len;charCount++){
		if(str1_ref[charCount] != str2_ref[charCount]){
			return false;
		}
	}

	//if all above are passed, strings are equal so
	//return true
	return true;
}
bool Tokenizer::strEqual(std::string& str1_ref,const char* c_ptr){
	int str1Len = str1_ref.length();
	std::string string2 = c_ptr;
	int str2Len = string2.length();

	//check the length first to make sure there is a match
	if(str1Len != str2Len){
		return false;
	}

	//now check char by char for equality
	//quit immediately if inequality found
	for(int charCount=0;charCount<str1Len;charCount++){
		if(str1_ref[charCount] != string2[charCount]){
			return false;
		}
	}

	//if all above are passed, strings are equal so
	//return true
	return true;
}
bool Tokenizer::strEqual(const char* c_ptr,std::string& str2_ref){
	int str1Len = str2_ref.length();
	std::string string1 = c_ptr;
	int str2Len = string1.length();

	//check the length first to make sure there is a match
	if(str1Len != str2Len){
		return false;
	}

	//now check char by char for equality
	//quit immediately if inequality found
	for(int charCount=0;charCount<str1Len;charCount++){
		if(str2_ref[charCount] != string1[charCount]){
			return false;
		}
	}

	//if all above are passed, strings are equal so
	//return true
	return true;
}

bool Tokenizer::strEqual(const char* c_ptr,const char* c_ptr2){

	std::string string1 = c_ptr;
	std::string string2 = c_ptr2;

	int str1Len = string1.length();
	int str2Len = string2.length();

	//check the length first to make sure there is a match
	if(str1Len != str2Len){
		return false;
	}

	//now check char by char for equality
	//quit immediately if inequality found
	for(int charCount=0;charCount<str1Len;charCount++){
		if(string1[charCount] != string2[charCount]){
			return false;
		}
	}

	//if all above are passed, strings are equal so
	//return true
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// skip any leading delimiters
///////////////////////////////////////////////////////////////////////////////
void Tokenizer::skipDelimiter(const std::string& currDelim)
{
	int span = currDelim.length();
    while(currPos != buffer.end() && isDelimiter(*currPos,currDelim)){
        currPos+=span;
        iCurrPos+=span;
    }
}

//Skips leading string delimiters
void Tokenizer::skipDelimiter_CStr(char* cstr, int span,const std::string& currDelim)
{
	//TODOx: need to find a way to refresh the cstr before
	//each while loop condition check with the new char set
	//which is iCurrPos + delimStr.length() if a leading delim is
	//found
	char* cstr2 = cstr;
    while(currPos != buffer.end() && isDelimiter_CStr(cstr2,span,currDelim)){
	//if(isDelimiter_CStr(cstr2,span,currDelim)){
        currPos+=span;
        iCurrPos+=span;
        cstr2+=span;
	//}
    }
}


///////////////////////////////////////////////////////////////////////////////
// return true if the current character is delimiter
///////////////////////////////////////////////////////////////////////////////
bool Tokenizer::isDelimiter(char c,const std::string& currDelim)
{
	//std::cout << "in isDelimiter, char c is " << c << " and first char of currDelim string is " << currDelim[0] << std::endl;
    return (c == currDelim[0]);//(delimiter.find(c) != std::string::npos);
}

///<Return true if the current character through span-1
///<exactly matches the c-string passed in
///<This allows us to identify whole character strings at a time
///<as single delimiters as opposed to evaluating every char in the
///<delimiter char string as a delimiter in its own right
bool Tokenizer::isDelimiter_CStr(char* c_ptr,int span,const std::string& currDelim){

	//TODOx: Check currPos through currPos+(span-1)
	//to ensure it exactly matches in order the
	//given delimiter string

	//TODOx: make sure that the c_str we pass into this function is refreshed
	//for each delimiter string's span -- we're seeing some odd data
	//that looks like on longer spans of, say, 8 characters, 7 + junk hex is
	//being grabbed as opposed to 8 characters from an 8 character long char array
	//as expected...

	std::stringstream ssLog;

	//Sanity checking the contents of c_ptr
	for(int x=0;x<span;x++){
		//std::cout << "c_ptr char at index " << x << " is " << c_ptr[x] << std::endl;
		ssLog << "c_ptr char at index " << x << " is " << c_ptr[x] << std::endl;
	}


	//std::string s(c_ptr);

	////std::cout << "inside of isDelimiter_CStr(" << s << "," << span << "," << currDelim << ")" << std::endl;

	//std::cout << " currDelim.c_str() returns " << currDelim.c_str() << std::endl;
	ssLog << " currDelim.c_str() returns " << currDelim.c_str() << std::endl;

	int res = std::strncmp(currDelim.c_str(),c_ptr,span);

	//std::cout << "and finally, res from strncmp is " << res << std::endl;
	ssLog << "and finally, res from strncmp is " << res << std::endl;

	myStaticWriteStringLog(ssLog.str());

	if(res == 0){
		//TODOx: update the currPos to be currPos+(span-1)
		//currPos+=span-1; //better to take care of this elsewhere for modularity

		return true;
	}
	else{
		return false;
	}

}

///////////////////////////////////////////////////////////////////////////////
// split the input string into multiple tokens
// This function scans tokens from the current cursor position.
///////////////////////////////////////////////////////////////////////////////
std::vector<std::string> Tokenizer::split()
{
    std::vector<std::string> tokens;
    std::string token;
    while((token = this->next()) != "")
    {
        tokens.push_back(token);
    }

    return tokens;
}
