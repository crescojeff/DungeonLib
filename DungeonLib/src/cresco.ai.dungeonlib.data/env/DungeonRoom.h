/*
 * DungeonRoom.h
 *
 *  Created on: May 27, 2013
 *      Author: CresCoJeff
 *
 *      Each room maintains UMap of event points at specific
 *      physical points/directions in the room which carry
 *      defined DungeonEvent data.
 *
 */

#ifndef DUNGEONROOM_H_
#define DUNGEONROOM_H_

#include "../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"
#include "DungeonObject.h"

class DungeonRoom {
private:
	int length;
	int height;
	int width;
	int volume;
	//dungeonObject objects[5];
	//std::stringstream ss;//UPDATE: cannot copy streams! Need to pass by ref or create new instance when used
	std::string story;
	std::vector<DungeonObject> mvDungeonObjectVector;

public:
	DungeonRoom(){
		length = 1;
		height = 1;
		width = 1;
		volume = 1;

	}
	virtual ~DungeonRoom(){

	}

	//accessors
	std::string* getStory(){
		return &story;
	}
	template <typename t> void appendToStory(t myT){
		std::stringstream ss;
		ss << story;
		ss << myT;
		story = ss.str();
	}
	/*
	std::string getSS(){
		return ss.str();
	}
	void appendSSToStory(){
		std::stringstream ss2;
		ss2 << story;
		ss2 << ss.str();
		story = ss2.str();
	}
	void resetSS(){
		//ss.flush();
		ss.str(""); //stringstream::str get or set the string buffer of the stringstream object.  No arg gets, string arg sets discarding the current contents
	}
	*/
	void resetStory(){
		story = "";
	}
	std::vector<DungeonObject>* getDungeonObjectVector_ptr(){
		return & mvDungeonObjectVector;
	}
	void appendToDungeonObjectVector(DungeonObject dO){
		mvDungeonObjectVector.push_back(dO);
	}

};

#endif /* DUNGEONROOM_H_ */
