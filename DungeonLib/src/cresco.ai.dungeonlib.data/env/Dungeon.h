/*
 * Dungeon.h
 *
 *  Created on: Jun 13, 2013
 *      Author: CresCoJeff
 *
 *
 *      This class represents the entire dungeon
 *      It maintains vectors and maps of all
 *      children of Dungeon, including room objects,
 *      agent objects, etc.  Children of Dungeon
 *      should grab their own references to
 *      persistent objects from Dungeon, and these objects
 *      should only be added to Dungeon on program start and
 *      from its children (who can then immediately remove their
 *      reference to the removed object)
 *
 *      It is also responsible for loading and unloading resources
 *      silently on auxiliary threads (hence the pthread.h include
 *      below).  See the Tokenizer.h docs for more details.
 *
 */

#ifndef DUNGEON_H_
#define DUNGEON_H_

#include "../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"
#include "../entities/DungeonAgent.h"
#include "DungeonObject.h"
#include "DungeonRoom.h"
#include <pthread.h>


class Dungeon {
private:
	std::vector<DungeonAgent> mvAgentVector;
	std::vector<DungeonObject> mvObjectVector;
	std::vector<DungeonRoom> mvRoomVector;



public:
	Dungeon();
	virtual ~Dungeon();
};

#endif /* DUNGEON_H_ */
