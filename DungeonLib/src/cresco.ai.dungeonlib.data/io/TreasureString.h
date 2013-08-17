/*
 * TreasureString.h
 *
 *  Created on: Jul 20, 2013
 *      Author: CresCoJeff
 *
 *      Holds a std::string and a surprise!
 *      For our tags, these will hold the string including
 *      angle brackets, and also an integer offset that
 *      the parser needs to consume before looking to match the
 *      right angle bracket; so if we wanted a <TEXT> tag
 *      with 5 chars of metadata between the second T and the right
 *      angle bracket we would add a TreasureString to our TreasureString vector
 *      with its content set to <TEXT> and its treasure set to
 *      5.  The parser will have this data available so that it
 *      can be in metadata analysis state for 5 chars until the right
 *      angle bracket is reached at which point it leaves delimiter state.
 *
 */

#ifndef TREASURESTRING_H_
#define TREASURESTRING_H_

#include "../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"

template <class treasure> class TreasureString {
private:
	std::string sContentString;
	treasure mvTreasure;
public:
	TreasureString(){

	}
	TreasureString(std::string s,treasure t){
		sContentString = s;
		mvTreasure = t;
	}
	virtual ~TreasureString(){

	}

	//accessors
	std::string getContentString(){
		return sContentString;
	}
	treasure getTreasure(){
		return mvTreasure;
	}
	//control functions

	//operator overloads
    TreasureString& operator=(const TreasureString& rhs){
    	if(this != &rhs){
    		//1. Deallocate dynamic allocated mem that MyClass is using internally
    		//2. Dynamically allocate memory to hold the dynamically allocated contents of rhs
    		//3. Copy the attribute values from rhs into this instance
    		//4. return *this
    		this->sContentString = rhs.sContentString;
    		this->mvTreasure = rhs.mvTreasure;


    	}

    	return *this;
    }


};

#endif /* TREASURESTRING_H_ */
