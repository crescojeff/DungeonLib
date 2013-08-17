/*
 * DungeonObject.h
 *
 *  Created on: May 27, 2013
 *      Author: CresCoJeff
 */

#ifndef DUNGEONOBJECT_H_
#define DUNGEONOBJECT_H_

#include "../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"

class DungeonObject {
private:
	int volume;
	int width;
	int height;
	//char name[10];
	std::string name;
	int UUID;

public:
	DungeonObject(){
		height = 0;
		width = 0;
		volume = 0;
		name = "";
		UUID = getAndIncrementUUID();

	}
	virtual ~DungeonObject(){

	}

	//accessors
	int getVolume(){
		return volume;
	}
	int getWidth(){
		return width;
	}
	int getHeight(){
		return height;
	}
	int getUUID(){
		return UUID;
	}
	std::string getName(){
		return name;
	}

};

#endif /* DUNGEONOBJECT_H_ */
