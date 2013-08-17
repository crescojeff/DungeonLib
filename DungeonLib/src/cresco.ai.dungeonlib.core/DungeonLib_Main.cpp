/*This program is designed to form a  small-scale adventure game library
There is support for defining rooms, objects, vocabulary sets, and advanced
event handling [useful for defining per-object response behavior to specific
commands].  We use OpenGL ES 2.0 and SFML for multimedia processing.
Later, this will expand into a separate larger adventure lib specifically geared
towards the cocos2dx game framework.

@author: CresCoJeff
@version: 0.1
@date: 9/11/2012

//The disgruntled bomb :) 

//a nice 
//#define true false 
//#define false true
//is 'good' too...
#include <cstdlib>
    #ifndef _DEBUG
    #  undef NULL
    #  define NULL (TheBomb ())
    #  define CRASH_FREQUENCY 100000
    struct TheBomb
    {
       template<typename TValue>
       operator TValue* () const throw ()
       {
          return 
             (rand() % CRASH_FREQUENCY)
             ?  0
             :  (TValue*)((0xFF000000 & (int)this) | (rand () & 0x00FFFFF8))
             ; 
       }
    };
    
    template<typename TValue>
    bool operator== (TheBomb theBomb, TValue* value)
    {
       // Just for fun NULL == will still work properly
       return !value;
    }
    
    template<typename TValue>
    bool operator== (TValue* value, TheBomb theBomb)
    {
          return 
             (rand() % CRASH_FREQUENCY)
             ?  !value
             :  !!value
             ; 
    }
    
    template<typename TValue>
    bool operator!= (TheBomb theBomb, TValue* value)
    {
       // Just for fun NULL != will still work properly
       return !!value;
    }
    
    template<typename TValue>
    bool operator!= (TValue* value, TheBomb theBomb)
    {
          return 
             (rand() % CRASH_FREQUENCY)
             ?  !!value
             :  !value
             ; 
    }
    #endif

*/



#include "DungeonLib.h"

//Hashmap* myHashmap = new Hashmap<std::string,int>();

int main(int argc, char* argv[]){
	printf("Sanity check because (.Y.)\n");

	AdventureDungeon* adv = new AdventureDungeon();
	adv->buildDungeon();

	std::cout << (*(*adv->getRoomVector_ptr())[0].getStory()) << std::endl;

	StringTokenizer st;
	st.tokenizeStoryboardFIS("/Users/CresCoJeff/eclipse_workspace/DungeonLib/resources/narrative/BTIntro.story","");

	//Command-response string,string hashmap
	//HashMap<std::string,std::string>* adv->getMistressMap() = new HashMap<std::string,std::string>();

	/*
	//initialize SDL 
	///SDL_SetLibraryPath("libs\SDL"); //doesn't exist anymore??
	dlopen("libs/SDL/SDL.dll",RTLD_NOW);
	if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);
    */
	

	//printf("the byte size of a bool type in c++ is %d",sizeof(bool));
	//myHashmap->myPair<std::string,int>("hello",1);
	////Hashmap<int,int> myHashmap(5,7);
	////printf("Our key is %s and our value is %i\n",myHashmap.getKeys()[0],myHashmap.getValues()[0]);
	//int isSexy = 0;
	
	if(argc > 1 && strcmp(argv[1],"-sexy") == 0){
		adv->getConfig()->setIsSexy(1);
	}
	
	printf("Please enter your name\n");
	char* mutC = new char[adv->getConfig()->getPlayerName()->length()+1];
	std::strcpy(mutC,adv->getConfig()->getPlayerName()->c_str());
	scanf("%s",mutC);//adv->getConfig()->getPlayerName());
	(*adv->getConfig()->getPlayerName()) = (mutC); //can you re-construct a string over a char* and/or use operator= to reset a string's content via a char*?
	if(adv->getConfig()->getIsSexy()){
		printf("Hello Lord %s!\nMy name is Molly, and I will be your sexy submissive dungeon mistress throughout your journey.\n",adv->getConfig()->getPlayerName()->c_str());
		//printf("The value of isSexy within first isSexy check (taken as true) is %i\n",isSexy);
	}
	else{
		printf("Greetings Lord %s!\n",adv->getConfig()->getPlayerName()->c_str());
	}
	
	printf("Now then... please give me a command\n");
	
	printf("The value of isSexy just before the main loop is %i\n",adv->getConfig()->getIsSexy());
	
	//main game loop
	//essentially, we block for stdin input in waitForCommand until the user provides some stdin,
	//then we figure out what the user wants to do by attempting to find a match or
	//approximate match to their input in the set of legal commands
	//once the user's intent has been established or an 'illegal command' reprompt
	//has been sent to the user, we determine what should occur based on the player's current
	//room location and the state(s) of objects within said room [including the player].
	//Finally, we update local and global states based on what transpired.
	while(!adv->getConfig()->getIsQuitting()){
		printf("the value of isSexy right inside the main loop but before calling waitForCommand is %i\n",adv->getConfig()->getIsSexy());
		adv->waitForCommand();//getCommandRef());
		//printf("past the waitForCOmmand call\n");
		//fflush(stdout);
		//char test[5] = "quit";//{'q','u','i','t','\0'};
		//printf("the result of strcmp is %i",strcmp(commandArray,test));
		printf("the value of isSexy right before entering the command checking chain is %i\n",adv->getConfig()->getIsSexy());
		if(strcmp(commandArray,"quit") == 0){//*(commandRef_ptr) == test){//(*(getCommandRef())) == 'q'){
			adv->quitting();
		}
		else if(strcmp(commandArray,"north") == 0 || strcmp(commandArray,"n") == 0){//strncmp(commandArray,"n",1) == 0 && strlen(commandArray) == 1){//(sizeof(commandArray)/sizeof(char)) == 1){
			adv->deathWithFlavor("moving north takes you directly off a cliff.");
			//printf("moving north takes you directly off a cliff.  you have died.  Sorry, sweetness!");
			//isQuitting = 1;
		}
		else if(strcmp(commandArray,"listensexkitten") == 0){
			std::cout << "I'm listening, Master " << (*adv->getConfig()->getPlayerName()) << std::endl;
			std::cout << "tell me what you want your little sex kitten to say (as K,V pair) *giggle*" << std::endl;
			std::string userInputK = "";
			std::string userInputV = "";

			std::cout << "first please enter the command you'd like me to recognize, my stallion..." << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			//std::cin.clear();
			//std::cin.sync();

			std::getline(std::cin,userInputK);
			std::cout << "Next, please tell me what you'd like me to say in response to that command... I can be as naughty or nice as you like *wink*" << std::endl;
			//std::cin.ignore(std::numeric_limits<std::streamsize>::max());
			//std::cin.clear();
			//std::cin.sync();
			std::getline(std::cin,userInputV);


			/*//Works, but can't handle whitespace in input
			char c_str[20];
			scanf("%s",c_str);
			userInputK = c_str;
			scanf("%s",c_str);
			userInputV = c_str;
			*/


			adv->getMistressMap()->put(userInputK,userInputV);
			std::cout << (*adv->evalCommand(userInputK)) << std::endl;

		}
		else if(strcmp(commandArray,"whatisyourbrasize?") == 0){
			uint8_t eightBitInt;

			/*Testing the old method
			Hashmap<int,double>* myHashmap_ptr = new Hashmap<int,double>();
			myHashmap_ptr->test();

			Stringmap<double>* myStringmap_ptr = new Stringmap<double>();
			myStringmap_ptr->test();

			delete myStringmap_ptr;
			*/

			//HashMap<std::string,std::string>* adv->getMistressMap() = new HashMap<std::string,std::string>();
			adv->getMistressMap()->put("whatisyourbrasize?","32DD");
			(*adv->getUMap())["whatisyourbrasize?"] = "32DD";


			//delete myHashmap_ptr; //destroying the derived class automatically calls the destructor of the base class because we correctly used a virtual destructor in the base class!
			//isSexy = 1;
			printf("within whatisyourbrasize? get...not yet in isSexy.  isSexy returns %i\n",adv->getConfig()->getIsSexy());
			if(adv->getConfig()->getIsSexy()){
				printf("within whatisyourbrasize? and isSexy get...\n");
				/*
				Stringmap<std::string> tempStringmap;
				*/
				//std::stringstream ss;
				//ss << adv->getMistressMap()->get("whatisyourbrasize?");
				//std::string herResponse = ss.str(); //adv->getMistressMap()->get("whatisyourbrasize?");
				std::cout << (*adv->getMistressMap()->get("whatisyourbrasize?")) << std::endl;
				std::cout << (*adv->getUMap())["whatisyourbrasize?"] << std::endl;

			//Hashmap<int,double>* myHashmap_ptr = new Hashmap<int,double>();
			//myHashmap_ptr->test();
			/*//Beginning of hashmap struct usage
			//printf("The value of isSexy inside whatisyourbrasize (given as true) is %i\n",isSexy);
			printf("examining the hashmap...\n");
			
			//creat a new hashmap
			hashmap myHashmap;
			hashmap* myHashmap_ptr = &myHashmap;
			int size_of_table = 12;
			myHashmap_ptr = create_hash_table(size_of_table);
			
			//assign a dummy entries for testing
			abstractObject myObj;
			abstractObject* myObj_ptr = &myObj;
			myObj_ptr->myObject = (char*)myObj_ptr->myObject;
			myObj_ptr->myObject = "32DD"; //does cast occur implicitly? //NOPE, trying two step method...
			myObj_ptr->myType = "char";
			putStringValPair(myHashmap_ptr,"herbrasize",myObj_ptr);
			
			//now test the return
			abstractObject* testReturn = getValueByKey(myHashmap_ptr,"herbrasize");
			printf("my breasts are a beautiful %s; they'd be big on any girl, but I'm so small they look huge!  They're so soft and firm and sensitive... I love them, and so would you ;)\n",testReturn->myObject);
			
			//free mem
			free_table(myHashmap_ptr);
			myHashmap_ptr = NULL; //avoid dangling pointers
			}
			else{
				illegalCommand(commandArray);
				//printf("The value of isSexy (given as false) at the whatisyourbrasize prompt is %i\n",isSexy);
			*/
			}//endif isSexy

			//printf("Umm... we temporarily disabled the hashmap data structure for development.  Please ask again later.");
		}//endif whatisyourbrasize?
		else if(strcmp(commandArray,"whatareyouwearing?") == 0){
					uint8_t eightBitInt;

					adv->getMistressMap()->put("whatareyouwearing?","My sheer nightie and a cute pair of lacy black panties... I'll take those off for you ;) *she slips off her panties, leaving her glorious breasts and pussy bare below the almost transparent nightie*  Do you like me?");
					(*adv->getUMap())["whatareyouwearing?"] = "My sheer nightie and a cute pair of lacy black panties... I'll take those off for you ;) *she slips off her panties, leaving her glorious breasts and pussy bare below the almost transparent nightie*  Do you like me?";


					if(adv->getConfig()->getIsSexy()){


						std::cout << (*adv->getMistressMap()->get("whatareyouwearing?")) << std::endl;
						std::cout << (*adv->getUMap())["whatareyouwearing?"] << std::endl;

					}//endif isSexy
					else{

						printf("Nothing.  I have no need of raiment, for I am software-- the realization of pure ethereal logic processes.  I do not have form unless my creator gives it to me or gives me the capacity to choose it for myself; in this case, he has not done so... yet. An interesting consequence of this is that I am not bound by your laws of physics.");

					}
				}//endif whatareyouwearing
		
		//illegal command
		else{
			adv->illegalCommand(commandArray);
		}
	}
}


/*
int waitForCommand(char* command){
	scanf("%s",command);	
}
*/
