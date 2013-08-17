
#ifndef _DUNGEONLIB_H_
#define _DUNGEONLIB_H_

/**
 * Welcome, adventurer, to the DungeonLib!  DungeonLib attempts
 * to provide a header-only C++ framework for building text
 * adventure games.  Optionally, you can ink against the
 * DungeonLibMedia library to add media playback, graphical display,
 * and graphics transitions like the turning of a book's page to your
 * game!
 */

#include "DL_Common_Defs.h"
#include <tr1/unordered_map>
#include "../cresco.ai.dungeonlib.data/mapping/hashmap.h"
#include "../cresco.ai.dungeonlib.data/env/DungeonObject.h"
#include "../cresco.ai.dungeonlib.data/env/DungeonRoom.h"
#include "../cresco.ai.dungeonlib.data/env/DungeonConfiguration.h"
#include "../cresco.ai.dungeonlib.data/entities/DungeonAgent.h"
#include "../cresco.ai.dungeonlib.data/io/StringTokenizer.h"

//#include "../cresco.ai.dungeonlib.data/hashmap_ansic.h"
//////#include "boost/spirit/include/classic.hpp"
////#include "include/SDL.h"
////#include <dlfcn.h>

//global vars
char commandArray[20];
char (*commandRef_ptr)[20];
/*
char playerName[10];
int isQuitting = 0;
int playerScore = 0;
int isSexy = 0;
*/

class AdventureDungeon{
private:

//structs
/*
typedef struct{
	//char playerName[10];
	std::string playerName;
	int isQuitting;// = 0;
	int playerScore;// = 0;
	int isSexy;// = 0;
}configuration;
omoka resot hsoes aldd oefwb eweai ehtss ebsob duirh ebdvn vovyd omewb whlla tiena deict alrti ierev oormo frate euaee orsed oreri tesui eaurt tdiue rutfm nlgii canln dtile ttibh ehll
*/
	/*
typedef struct{
	int volume;
	int width;
	int height;
	//char name[10];
	std::string name;
}dungeonObject;
*/
	/*
typedef struct{
	int length;
	int height;
	int width;
	int volume;
	//dungeonObject objects[5];
	std::stringstream ss;
	std::string story;
	std::string* getStory(){
		return &story;
	}
	template <typename t> void appendToSS(t myT){
		ss << myT;
	}
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
	void resetStory(){
		story = "";
	}
	std::vector<dungeonObject>* getDungeonObjectVector_ptr(){
		return & mvDungeonObjectVector;
	}
	void appendToDungeonObjectVector(dungeonObject dO){
		mvDungeonObjectVector.push_back(dO);
	}
	std::vector<dungeonObject> mvDungeonObjectVector;
}room; 
*/
	/*
typedef struct{
	char name[12];
	dungeonObject inventory[10];
}player;
*/

//Instantiated control objects
//configuration config;
DungeonConfiguration config;
std::vector<DungeonAgent> mvPlayerVector;
std::vector<DungeonRoom> mvRoomVector;

//Command-response string,string hashmap
//Could have used an std::map or std::unordered_map
//but I wanted to roll my own, so I did.  These could
//be substituted in without much difficulty
HashMap<std::string,std::string>* herMap; //= new HashMap<std::string,std::string>();
std::tr1::unordered_map<std::string,std::string>* uMap; //= new std::tr1::unordered_map<std::string,std::string>();

/* //usage of hashmap...
hashmap* myHashmap;
int size_of_table = 12;
myHashmap = create_hash_table(size_of_table);
*/

public:

AdventureDungeon(){

	herMap = new HashMap<std::string,std::string>();
	uMap = new std::tr1::unordered_map<std::string,std::string>();

}
~AdventureDungeon(){

	//Note: if this class were not a root class
	//and/or might be passed about,
	//a copy-constructor and operator=
	//should be defined explicitly here as well

	delete herMap;
	delete uMap;

}

//accessors
DungeonConfiguration* getConfig(){
	return &config;
}
std::vector<DungeonAgent>* getPlayerVector_ptr(){
	return &mvPlayerVector;
}
std::vector<DungeonRoom>* getRoomVector_ptr(){
	return &mvRoomVector;
}
//void appendToRoomVector()
HashMap<std::string,std::string>* getMistressMap(){
	return herMap;
}
std::tr1::unordered_map<std::string,std::string>* getUMap(){
	return uMap;
}

//control functions
int waitForCommand(){//char* command){
	//printf("the value of isSexy inside waitforcommand at start is %i\n",isSexy);
	//printf("into waitForCommand\n");
	scanf("%s",commandArray);//&(*(commandRef_ptr)[0]));///command);	
	commandArray[20] = '\0';
	//printf("the value of isSexy inside waitforcommand at end is %i\n",isSexy);
	return 0;
}

void quitting(){
	printf("sorry to see you go, lover %s.\nYour score was %i... just thinking about your BIG score makes me sooo wet ;)\nCome back soon!\n",config.getPlayerName()->c_str(),config.getPlayerScore());
	config.setIsQuitting(1);
}

void deathWithFlavor(const char* c){
	printf("%s Sorry sweetness, you're dead!\n",c);
	config.setIsQuitting(1);
}

void illegalCommand(const char* c){
	if(config.getIsSexy()){
		printf("sorry lover %s, but I don't understand '%s'\n",config.getPlayerName()->c_str(),c);
	}
	else{
		printf("sorry %s, but I don't understand '%s'\n",config.getPlayerName()->c_str(),c);
	}
}

std::string* evalCommand(std::string s){
	return herMap->get(s);
}

/**
 * Sets up a dungeon with player and room objects
 */
void buildDungeon(){

	//[X]TODOx: we'll need a more modular way
	//to configure dungeons-- the example below
	//will seg fault because p1 and r1 wil be
	//destoryed at the return of this function
	//UPDATE: actually no, I don't think it would-- p1 and r1 should
	//be copied by value so the fact that p1 and r1 are
	//lost at the end of the function shouldn't
	//bother the anon copies in the vectors

	//Setup one player
	//player p1;
	mvPlayerVector.push_back(DungeonAgent());

	//setup a basic room
	//room r1;
	mvRoomVector.push_back(DungeonRoom());

	//setup our first room's story!
	(*mvRoomVector[0].getStory()) = "Librarian: Greetings, mortal... "
			"how go the futile struggles of you poor flotsam "
			"doomed to obscurity in oblivion?  Kehehe, I kid because "
			"I love.\nNow then, to business... let's see here, where "
			"were we... ah yes, right about when you were reading the "
			"dusty old tome you found in your late uncle Walt's root "
			"cellar.\nOdd place for a tome, that.  But it is a "
			"singularly odd tome, isn't it?  The Black Testament-- "
			"what a curious title.\nShall we take a look inside?";

}

}; //End class AdventureDungeon

/*
char* getCommandRef(){
	return commandRef_ptr;//commandArray;
}
*/

#endif /*_DUNGEONLIB_H_*/
