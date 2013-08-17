/*
 * DungeonNode.h
 *
 *  Created on: Jun 16, 2013
 *      Author: CresCoJeff
 *
 *
 *      Nodes serve as abstract wrappers for
 *      various types of data, such as events and subclasses
 *      of events...  For the moment it only provides a vector
 *      of said abstract data.
 *
 */

#ifndef DUNGEONNODE_H_
#define DUNGEONNODE_H_

template <class data> class DungeonNode {
private:
	std::vector<data&> mvDataVector;

public:
	DungeonNode();
	virtual ~DungeonNode();


	//accessors
	std::vector<data&>* getDataVector_ptr();

	//control functions


};

template <class data> DungeonNode<data>::DungeonNode() {


}

template <class data> DungeonNode<data>::~DungeonNode() {

}


#endif /* DUNGEONNODE_H_ */
