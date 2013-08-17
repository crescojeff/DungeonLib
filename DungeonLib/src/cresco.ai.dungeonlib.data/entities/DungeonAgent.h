/*
 * DungeonAgent.h
 *
 *  Created on: May 27, 2013
 *      Author: CresCoJeff
 */

#ifndef DUNGEONAGENT_H_
#define DUNGEONAGENT_H_

#include "../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"
#include "../env/DungeonObject.h"

class DungeonAgent {
private:
	//char name[12];
	//dungeonObject inventory[10];
	std::string name;
	int UUID;
	std::vector<DungeonObject> inventory;

public:
	DungeonAgent(){
		UUID = getAndIncrementUUID();
	}
	virtual ~DungeonAgent(){

	}

	//accessors
	std::string* getName_ptr(){
		return &name;
	}
	int getUUID(){
		return UUID;
	}
	std::vector<DungeonObject>* getInventory_ptr(){
		return &inventory;
	}

};

#endif /* DUNGEONAGENT_H_ */
