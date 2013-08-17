/*
 * DungeonEvent.h
 *
 *  Created on: Jun 13, 2013
 *      Author: CresCoJeff
 *
 *
 *      Defines a specific event that can occur within the
 *      dungeon, and how it should be handled.
 *      Types of events include TextEvents, which are triggered
 *      string output...
 */

#ifndef DUNGEONEVENT_H_
#define DUNGEONEVENT_H_

#include "../../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"
#include "../../entities/DungeonAgent.h"
#include "../DungeonObject.h"

class DungeonEvent {
private:
	//Event UUID
	int UUID;

	//Vectors of agents and object affected by the event
	std::vector<DungeonAgent> mvAffectedAgentVector;
	std::vector<DungeonObject> mvAffectedObjectVector;

	//Assoc UMaps of agent and object UUID's to
	//pointers to them as stored in the above vectors
	//for fast access of known agent or object
	std::tr1::unordered_map<int,DungeonAgent*> mvAffectedAgentUMap;
	std::tr1::unordered_map<int,DungeonObject*> mvAffectedObjectUMap;

public:
	DungeonEvent(){
		UUID = getAndIncrementUUID();
	}
	virtual ~DungeonEvent(){

	}


	//accessors
	std::vector<DungeonAgent>* getAffectedAgentVector_ptr();
	std::vector<DungeonObject>* getAffectedObjectVector_ptr();
	std::tr1::unordered_map<int,DungeonAgent*>* getAffectedAgentUMap_ptr();
	std::tr1::unordered_map<int,DungeonObject*>* getAffectedObjectUMap_ptr();
	virtual int getUUID();


	//control functions
	template <class T> void registerForCB(T&);
	void postToRegistrants();


};

template <class T> void DungeonEvent::registerForCB(T&){
	std::cout << "Sorry, but you may only register objects of type DungeonAgent and DungeonObject for event callback" << std::endl;
}
template <> void DungeonEvent::registerForCB<DungeonAgent>(DungeonAgent& da_ref){
	mvAffectedAgentVector.push_back(da_ref);
	int vLength = mvAffectedAgentVector.size();
	mvAffectedAgentUMap[mvAffectedAgentVector[vLength].getUUID()] = &(mvAffectedAgentVector[vLength]);
}
template <> void DungeonEvent::registerForCB<DungeonObject>(DungeonObject& do_ref){
	mvAffectedObjectVector.push_back(do_ref);
	int vLength = mvAffectedObjectVector.size();
	mvAffectedObjectUMap[mvAffectedObjectVector[vLength].getUUID()] = &(mvAffectedObjectVector[vLength]);
}

template <class data> class TextEvent : DungeonEvent{
private:
	int UUID;
	std::string sText;

	//TODO: are member attributes carried over from parent classes?
	//for instance, could we directly access mvAffectedAgentVector
	//from this class?  If not, can we call the getter for
	//said members (e.g. will the members be constructed?)?

public:
	TextEvent():DungeonEvent(){
		UUID = getAndIncrementUUID();

	}
	virtual ~TextEvent(){

	}

	//accessors
	int getUUID(){

		return UUID;
	}
	std::string* getText_ptr(){
		return &sText;
	}

	//control function

};

#endif /* DUNGEONEVENT_H_ */
