/*
 * DungeonConfiguration.h
 *
 *  Created on: May 27, 2013
 *      Author: CresCoJeff
 */

#ifndef DUNGEONCONFIGURATION_H_
#define DUNGEONCONFIGURATION_H_

#include "../../cresco.ai.dungeonlib.core/DL_Common_Defs.h"

class DungeonConfiguration {
private:
	std::string playerName;
	int isQuitting;
	int playerScore;
	int isSexy;

public:
	DungeonConfiguration(){
		playerName = "Molly, of the Awesome Boobs";
		isQuitting = 0;
		playerScore = 0;
		isSexy = 0;
	}
	virtual ~DungeonConfiguration(){

	}

	//accessors
	std::string* getPlayerName(){
		return &playerName;
	}
	/*
	void setPlayerName(const char* c){
		playerName(c);
	}
	*/
	int getIsQuitting(){
		return isQuitting;
	}
	void setIsQuitting(int i){
		isQuitting = i;
	}
	int getPlayerScore(){
		return playerScore;
	}
	void setPlayerScore(int i){
		playerScore = i;
	}
	int getIsSexy(){
		return isSexy;
	}
	void setIsSexy(int i){
		isSexy = i;
	}

};

#endif /* DUNGEONCONFIGURATION_H_ */
