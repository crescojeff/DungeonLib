#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector.h>

/* One way, based on the C hashmap meant to use character string keys
//Beginning of Hashmap class definition
//All-righty-roo, this hashmap is going to take advantage of some c++ features 
//mostly class and function/class templates and avoid the void pointer casting stuff from the ansi C version

//Don't seem to need this guy... might want to test with templated structs and see if it is needed there, or if templateThing<a_type> is a suffciently real class object or struct object
//class Hashmap_Base{
//private:

//public:
	//virtual Hashmap_Base(); //can't have virtual constructors
	//virtual ~Hashmap_Base();

	//virtual std::vector<char>* getKeys();
	//virtual std::vector<char>* getValues();


//};


template <class Key, class Value>
//template <class Value>
class Hashmap{//:Hashmap_Base{
private:
	//N.B. In order to facilitate associative grouping, we probably don't want any kind of 
	//standard linear containers here
	//naive associativity is not too difficult-- just write a hashing function which
	//determines the flat address to be used for the value (based on the key) and malloc space for the value
	//at that location (see the ANSI C implementation)
	//Spatial-respective hashing would instead generate a unique hash code based on the key
	//and use this value in an offset algorithm from some given location so as to obey spatial locality
	//rules.  Best case would be for all the value spaces to be knit tightly enough that
	//all of a given hashmap's look-up locations could be in RAM at the same time following the first
	//reference to the hashmap object
	

	Key keys[1];
	Value values[1];
	int mappedElementCount;

	typedef struct {
		void* myObject; //this was const before-- is that necessary?  Seems like we need it mutable...
		char* myType;
	}abstractObject;

	//w00t, a 2-way traversable circular linked list in C FTW!!
	typedef struct _list_t_{
		abstractObject* key_ptr;
		abstractObject* value_ptr; //could just be void* but hey let's vagazzle this bitch!
		struct _list_t_* pNext;
		struct _list_t_* pPrevious;
		struct _list_t_* pLinkedListHead; //set only when the list is first created as the address of the oject currently being added
		struct _list_t_* pLinkedListTail; //set anew each time a new object is added to the end of the list to the address of the new object
	}linkedList;

	linkedList** table;

	 //how do you free the memory from a vector...?
	 //since it is a container class it should provide a function to dealloc memory from its stored elements...
	 //answer is std::vector::clear() BUT bear in mind that if your vector contains pointers, you must iterate over each such
	 //pointer and free it BEFORE clearing the vector.  Elsewise you end up with memory leaks as the objects pointed to by the pointers
	 //in the vector will not be deallocated (clear attempts to call the destructor of each object in the vector, but even typed pointers will not automatically dereference and call the associated object's destructor),
	 //and after the vector is cleared hooks to them will be (potentially) lost.  Clearing a vector of pointers will essentially empty your vector
	 //but will also remove the address hooks to objects allocated in memory without deallocating that memory, leading to massive memory leaks.
	//Also, you don't have to call clear() explicitly; this'll be done automatically by the vector's destructor
	//so you only need to make sure it gets destroyed via free if malloc'd or delete if new'd or allow to go
	//out of scope if directly constructed implicitly or explicitly
	///std::vector<Key> keys;
	///std::vector<Value> values;



public:
	explicit Hashmap();//(Key,Value);
	virtual ~Hashmap();


	//Did I implement this here for a reason...? Moving to class implementation below
	//void myPair(Key first, Value second){
		//keys[0]=first; values[0]=second;
	//}


	virtual void test();

	virtual int hash(Key*);

	void myPair(Key,Value);

	int* getSize();

	virtual void putKVPair(Key*,Value*);
	virtual Value* get(Key*);


	void clearMap();
	void init_LinkedList(linkedList*);

	//When we use these methods, we'll want a linear vector of keys and values to iterate over, so vector is good here
	std::vector<Key>* getKeys();
	std::vector<Value>* getValues();

}; //end hashmap class definition

//Hashmap class implementation

template<class Key,class Value> Hashmap<Key,Value>::Hashmap(){
	mappedElementCount = 0;
}
template<class Key,class Value> Hashmap<Key,Value>::~Hashmap(){
	printf("\nDestroying the base Hashmap object!\n");
}

template<class Key,class Value> void Hashmap<Key,Value>::test(){
	printf("The size of our Key is %i and the size of our Value is %i\n",sizeof(Key),sizeof(Value));
}

template<class Key, class Value> void Hashmap<Key,Value>::myPair(Key k, Value v){
	keys[0] = k;
	values[0] = v;
}

template<class Key,class Value> int Hashmap<Key,Value>::hash(Key* k_ptr){

	//TODO: figure out how the original C version below was supposed to work
	//starting at 0 and adding char val + 31*currentHashVal for each new linked list
	//in the table, and then edit our algorithm here appropriately
	 	unsigned int hashval;
	 	void* hash_ptr;

	    // we start our hash out at 0
	    //hashval = k_ptr;//0;

	 	//Store the address of our Key object
	 	//We can operate on this address with normal
	 	//arithmetic later (I think) to achieve
	 	//X byte offsets etc.
	 	hash_ptr = k_ptr;


	    //If our Key is of type std::string...
	    //if()
	    //TODO: yeah, type checking is not the OOP way...
	    //instead we should probably have another class
	    //that inherits from Hashmap and which has a set
	    //std::string key type, but a templated value
	    //When we know our keys will be strings, we would
	    //use that class instead of Hashmap.  To support this polymorphism,
	    //we've made Hashmap's destructor virtual.  Note that this is
	    //all for the sake of hashing over the Key value by charracters...
	    //a more generic hashing method would eliminate the need for a derived
	    //class

	    //for each character, we multiply the old hash by 31 and add the current
	     //character.  Remember that shifting a number left is equivalent to
	      //multiplying it by 2 raised to the number of places shifted.  So we
	      //are in effect multiplying hashval by 32 and then subtracting hashval.
	      //Why do we do this?  Because shifting and subtraction are much more
	      //efficient operations than multiplication.

	    //for(int i=0;i<str.length();i++) {
	    	//Since we don't know our Key's type here,
	    	//we'll just make the new hashval the current + 4 bytes
	    	hashval = hashval+4;  //str[i] + ((hashval << 5) - hashval);
	    //}

	    //we then return the hash value mod the hashmap size so that it will
	    //fit into the necessary range

	    return hashval % mappedElementCount;

}

template<class Key,class Value> std::vector<Key>* Hashmap<Key,Value>::getKeys(){
	//TODO: prepare a vector initialized with all Key objects and return it here
	return keys;	
}

template<class Key,class Value> std::vector<Value>* Hashmap<Key,Value>::getValues(){
	//TODO: prepare a vector initialized with all Value objects and return it here
	return values;	
}

template<class Key,class Value> int* Hashmap<Key,Value>::getSize(){
	return &mappedElementCount;
}

template<class Key,class Value> void Hashmap<Key,Value>::putKVPair(Key* k, Value* v){
		//TODO: implement hashing of the key object k to determine
		//the address of the value object v

		//first step, generate a hash from our key
		int tempHash = hash(k);

		//TODO: store Value at an address given by or influenced by tempHash

	    //If all was successfully completed, increment the mapped records counter
		mappedElementCount++;
}

template<class Key, class Value> Value* Hashmap<Key,Value>::get(Key* k_ptr){
	linkedList *list;
	    init_LinkedList(list);

	    unsigned int hashval = hash(k_ptr);

	    //Go to the correct list based on the hash value and see if str is
	     //in the list.  If it is, return return a pointer to the abstractObject member of the list.
	     //If it isn't, the item isn't in the table, so return NULL.


	   // for(list = this->table[hashval]; list != NULL; list = list->pNext) {
	       // if (strcmp(strKey, list->str) == 0) return list->value;
	    	//TODO: need to come up with a way to grep over the map given an
	    	//abstractObject for the general case here...
	   // }

	    return NULL;
}




template<class Key,class Value> void Hashmap<Key,Value>::clearMap(){
	//TODO: implement a cascading chain of deallocation of stored objects within the hashmap
	//MAYBE-- only if we create new objects rather than just mapping reference associations,
	//which is really the goal here...  In the latter preferred case, just
	//empty the Hashmap here
}

template <class Value>
class Stringmap:public Hashmap<std::string,Value>{
private:
	Value values[1];

	typedef struct {
		void* myObject; //this was const before-- is that necessary?  Seems like we need it mutable...
		char* myType;
	}abstractObject;

	//w00t, a 2-way traversable circular linked list in C FTW!!
	typedef struct _list_t_{
		std::string* str_ptr;
		abstractObject* value_ptr; //could just be void* but hey let's vagazzle this bitch!
		struct _list_t_* pNext;
		struct _list_t_* pPrevious;
		struct _list_t_* pLinkedListHead; //set only when the list is first created as the address of the oject currently being added
		struct _list_t_* pLinkedListTail; //set anew each time a new object is added to the end of the list to the address of the new object
	}linkedList;

	linkedList** table; // pointer to the table elements array -- What we have is a pointer to a pointer to a linked list; thus list_t **table.  Used because we don't know the size of the hashtable to begin with....


public:
	//Con/de 'structors
	explicit Stringmap();
	~Stringmap();

	//Here we know our Key will be of type std::string
	//so we can generate our hash sig the way we planned
	//before
	int hash(std::string*);

	void initLinkedList(linkedList*);

	//override test from base class
	void test();

	int putKVPair(std::string*,Value*);
	Value* get(std::string*);

	linkedList* lookupString(std::string*);


};

template<class Value> Stringmap<Value>::Stringmap():Hashmap<std::string,Value>(){

}
template<class Value> Stringmap<Value>::~Stringmap(){
	printf("\nDestroying the derived stringmap object!\n");
}

template<class Value> void Stringmap<Value>::test(){
	printf("The size of our Value is %i\n",sizeof(Value));
}

template<class Value> int Stringmap<Value>::hash(std::string* str_ptr){

	 	unsigned int hashval;

	    // we start our hash out at 0
	    hashval = 0;


	    //If our Key is of type std::string...
	    //if()
	    //TODO: yeah, type checking is not the OOP way...
	    //instead we should probably have another class
	    //that inherits from Hashmap and which has a set
	    //std::string key type, but a templated value
	    //When we know our keys will be strings, we would
	    //use that class instead of Hashmap.  To support this polymorphism,
	    //we've made Hashmap's destructor virtual.  Note that this is
	    //all for the sake of hashing over the Key value by charracters...
	    //a more generic hashing method would eliminate the need for a derived
	    //class

	    // for each character, we multiply the old hash by 31 and add the current
	     // character.  Remember that shifting a number left is equivalent to
	     // multiplying it by 2 raised to the number of places shifted.  So we
	     // are in effect multiplying hashval by 32 and then subtracting hashval.
	     // Why do we do this?  Because shifting and subtraction are much more
	     // efficient operations than multiplication.

	    for(int i=0;i<str_ptr->length();i++) {
	    	hashval = (*(str_ptr))[i] + ((hashval << 5) - hashval);
	    }

	    // we then return the hash value mod the hashmap size so that it will
	      //fit into the necessary range

	    return hashval % (*(Hashmap<std::string,Value>::getSize()));

}

template<class Value> void Stringmap<Value>::initLinkedList(linkedList* ll){
	ll->pLinkedListHead = NULL;
	ll->pLinkedListTail = NULL;
	ll->pNext = NULL;
	ll->pPrevious = NULL;
	ll->str_ptr = NULL;
	ll->value_ptr = NULL;
}

template<class Value> int Stringmap<Value>::putKVPair(std::string* str_ptr, Value* v){
		//TODO: implement hashing of the Key std::string to determine
		//the address of the value object v

	linkedList* new_list;
	initLinkedList(new_list);
	linkedList* current_list;
	initLinkedList(current_list);


		//first step, generate a hash from our string key
		int tempHash = hash(str_ptr);

		//TODO: store Value at an address given by or influenced by tempHash
		//or at a spot in the hashtable given or influenced by tempHash

		// Attempt to allocate memory for list
		    if ((new_list = (linkedList*)malloc(sizeof(linkedList))) == NULL) return 1;

		    // Does item already exist?
		    current_list = lookupString(str_ptr);//lookup_string(hashMap, str);

		   if (current_list != NULL){ //collision case
				// item already exists, either don't insert it again or add it to the linked list as a handled collision element.
				//handle new assignment of listTail, don't alter listHead here
				return 2; //the "don'insert it again" method...
			}
			else{ //usual case
		    // Else, Insert into list
			//at this point, we are definitly adding the first member of the list so set it as both
			//list head and list tail...
		    new_list->str_ptr = strdup(str_ptr->c_str());//performs malloc of strlen(s) + 1 bytes for you
			new_list->value_ptr = myVal; //set value member to the address of the object passed in as myVal
		    new_list->pNext = this->table[hashval];
			new_list->pPrevious = this->table[hashval];
			new_list->pLinkedListHead = this->table[hashval];
			new_list->pLinkedListTail = this->table[hashval];
		    this->table[hashval] = new_list;
			}

		    return 0; //success condition

	    //If all was successfully completed, increment the mapped records counter
		mappedElementCount++;
}

template<class Value> Value* Stringmap<Value>::get(std::string* str_ptr){
	linkedList *list;
	    init_LinkedList(list);

	    unsigned int hashval = hash(k_ptr);

	    // Go to the correct list based on the hash value and see if str is
	     // in the list.  If it is, return return a pointer to the abstractObject member of the list.
	     //If it isn't, the item isn't in the table, so return NULL.

	    for(list = this->table[hashval]; list != NULL; list = list->pNext) {
	       if (strcmp(str_ptr, list->str_ptr) == 0) return list->value_ptr;

	    }
	    return NULL;
}

*/


/*
 * A simple hashmap in cpp example
 * Very simple yet complete Hash Map implementation in C++
 *
 * Relies upon int values for mapping, but any given data structure
 * could be hashed into an int which would allow this impl to be used
 * practically out of the box.  Since the hashval is only used as a hint
 * at where the Value object will be located, the hash function doesn't
 * need to be very complicated.  For a StringMap for instance, you might
 * generate a hashval by adding together each character of the string
 * and then modding the resultant sum by the TABLE_SIZE to ensure it will
 * fit in the underlying table of HashNode objects
 */
//

// Configurable table size constant
const int TABLE_SIZE = 128;
const int ERROR = -1;

/*canned hashnode class for hashtable
// Hash node class
class HashNode {
public:

	//Constructor for HashNode with an init list for its members, _key, _value, and _next
	HashNode(int key, int value) : _key(key), _value(value), _next(0) {

	}

	//Accessors for the current working _key and _value values
	int getCurrentKey() {

		return _key;

	}
	int getCurrentValue() {

		return _value;

	}

	//Pointer to the next hashnode in the linked list
	HashNode* next() {

		return _next;

	}

	//Set the current _value value
	void set_value(int value) {
		_value = value;
	}

	//Set the _next value
	void set_next(HashNode* next) {
		_next = next;
	}

private:
	// Key-value pair
	int _key;
	int _value;

	//pointer to the next hashnode. Prev is tracked in terms of next
	//(e.g. prev = current;current = next) when needed
	HashNode* _next;

};
*/

// Hash map class
template <class key_data, class value_data> class HashMap {
public:
	HashMap();
	HashMap(const HashMap&);
	virtual ~HashMap();

	HashMap& operator=(const HashMap&);

	template <class c> int keyGen(c);
	int keyGen(std::string);


	int HashFunc(int);
	value_data* get(key_data);
	void put(key_data,value_data);
	void remove(key_data);

private:
	// Hash node class
	class HashNode {
	public:

		//Constructor for HashNode with an init list for its members, _key, _value, and _next
		HashNode(int key, value_data value) : _key(key), _value(value), _next(0) {

		}

		//Accessors for the current working _key and _value values
		int getCurrentKey() {

			return _key;

		}
		value_data* getCurrentValue() {

			return &_value;

		}

		//Pointer to the next hashnode in the linked list
		HashNode* next() {

			return _next;

		}

		//Set the current _value value
		void set_value(value_data value) {
			_value = value;
		}

		//Set the _next value
		void set_next(HashNode* next) {
			_next = next;
		}

	private:
		// Key-value pair
		int _key;
		value_data _value;

		//pointer to the next hashnode. Prev is tracked in terms of next
		//(e.g. prev = current;current = next) when needed
		HashNode* _next;

	}; //End class HashNode declaration/definition

	// Hash table
	HashNode** _table;
}; //End class HashMap declaration




template <class key_data,class value_data> HashMap<key_data,value_data>::HashMap() {
	//Sets _table to be an array of TABLE_SIZE pointers to hashnodes
	_table = new HashNode*[TABLE_SIZE];

	//init all the hashnode pointers in _table to NULL (given as immediate zero here)
	for (int i = 0; i < TABLE_SIZE; ++i){
		_table[i] = 0;
	}
}

template <class key_data,class value_data> HashMap<key_data,value_data>::~HashMap() {
	//Delete the entire _table
	for (int i = 0; i < TABLE_SIZE; ++i) {
		HashNode* entry = _table[i];
		while (entry != 0) {
			HashNode* prev = entry;
			entry = entry->next(); //should be zero at the tail of the list
			delete prev;
		}
	}
}

//copy-constructor
//TODO: make sure that reference members are
//reallocated for object pointed to by this
template <class key_data,class value_data> HashMap<key_data,value_data>::HashMap(const HashMap<key_data,value_data>& other) {
std::cout << "cc called for HashMap!" << std::endl;
	//first check for self reference
	if(this != other){
		//Sets _table to be an array of TABLE_SIZE pointers to hashnodes
		_table = new HashNode*[TABLE_SIZE];

		//init all the hashnode pointers in _table to other's values
		for (int i = 0; i < TABLE_SIZE; ++i){
			_table[i] = other._table[i];
		}
	}
}


//overload operator=
template <class key_data, class value_data> HashMap<key_data,value_data>& HashMap<key_data,value_data>::operator= (const HashMap<key_data,value_data>& copy){

	HashMap<key_data,value_data>* newMap = new HashMap<key_data,value_data>();

	//Sets _table to be an array of TABLE_SIZE pointers to hashnodes
	newMap->_table = new HashNode*[TABLE_SIZE];

	//init all the hashnode pointers in _table to NULL (given as immediate zero here)
	for (int i = 0; i < TABLE_SIZE; ++i){
		newMap->_table[i] = 0;
	}



	//evidently initialization of object references REQUIRES
	//an actual object, as opposed to the address of an object,
	//which is what the ref becomes anyway...
	return *newMap;
}



//arbitrary data integer key generation
template <class key_data, class value_data> template <class c> int HashMap<key_data,value_data>::keyGen(c dat){

	/*
	//Casts the memory address where the arbitrary data
	//object is stored to an int (platform specific as to
	//whether the int will hold the whole pointer)
	//and then returns this int value.  We only need
	//an algorithm that will generate a deterministic
	//key for a given object throughout a given app run,
	//so this is fine for arbitrary data unless that data
	//is moved
	int* i_ptr = reinterpret_cast<int*>(&dat);
	return *i_ptr;
	*/

	//Potentially a much better solution:
	//use sizeof data to get an int value based
	//on the object independent of its location in memory
	return sizeof dat;

}

//known data type std::string key generation
template <class key_data,class value_data> int HashMap<key_data,value_data>::keyGen(std::string s){
	int total = 0;
	for(int i=0;i<s.length();i++){
		total+=s[i];
	}
	return total;
}
/*
 //NOTE: Yes, this is the problem:
 //error: enclosing class templates are not explicitly specialized
 //You cannot specialize a member without also specializing the class.
 //What you can do is put the code from function in a separate class
 //and specialize that, much like basic_string depends on a separate
 //char_traits class. Then then non-specialized function can call a
 //helper in the traits class.

template <class key_data, class value_data> template<> int HashMap<key_data,value_data>::keyGen<std::string>(std::string s){
	int total = 0;
	for(int i=0;i<s.length();i++){
		total+=s[i];
	}
	return total;
}
//template <class key_data,class value_data> template int HashMap<key_data,value_data>::keyGen<std::string>(std::string);
*/

// Should be optimized according to specific needs
//NOTE: HashFunc, as a header implemented function, seems
//to need to be a member of a single compilation unit, such as
//a class or possibly a struct; if simply left as a C-style
//orphaned function, ld will throw duplicate symbol error
//even with include guards...
template <class key_data,class value_data> int HashMap<key_data,value_data>::HashFunc(int key) {

	return key % TABLE_SIZE;

}

/**
 * Attempts to retrieve a pointer to the value_data object
 * associated with the given key_data object.  If it cannot
 * find an associated value_data object, it returns NULL
 * so check for success condition via hashmap.get(...) != NULL...
 */
template <class key_data,class value_data> value_data* HashMap<key_data,value_data>::get(key_data dk) {

	int key = keyGen(dk);

	int hash_val = HashFunc(key);
	HashNode* entry = _table[hash_val];

	while (entry != 0) {
		if (entry->getCurrentKey() == key) {

			return entry->getCurrentValue();

		}

		entry = entry->next();

	}

	printf("Your get of int key %i resulted in no hits.  The returned Value is NULL!\n",key);
	//value_data dat;
	return NULL;
}

template <class key_data,class value_data> void HashMap<key_data,value_data>::put(key_data dk, value_data dv){

	//generate an int value from our arbitrary Key data type
	int key = this->keyGen(dk);

	//generate a hash_val based on the integer key
	int hash_val = HashFunc(key);

	//init our hashnode pointer prev to NULL
	HashNode* prev = 0;

	//init our hashnode pointer entry to the most correct linked list
	//record in our _table array
	HashNode* entry = _table[hash_val];

	//Now search for the key in the linked list of hashnodes
	//break if the linked list is NULL (entry==0) or if the
	//key is already in the linked list (this algorithm does NOT
	//allow repeat Keys in the hashmap) or if the tail of the linked
	//list has been reached and thus it is time to place our novel
	//key and its associated arbitrary value data in a new HashNode
	while (entry != 0 && entry->getCurrentKey() != key) {
		prev = entry;
		entry = entry->next();
	}

	//If we are at the ll tail, append a new HashNode
	//of int Key and arbitrary data Value
	if (entry == 0) {
		entry = new HashNode(key, dv);

		//if we are adding the head of the ll now
		//set prev to be entry also
		if (prev == 0) {
			_table[hash_val] = entry;
		} else {
			//otherwise, set prev's next value to point to the
			//HashNode we just added
			prev->set_next(entry);
		}
	} else {
		//If we didn't need to add a new HashNode (e.g. the key
		//already was in the ll) then just replace the exisiting
		//Key's associated Value with the one specified in this
		//function call
		entry->set_value(dv);
	}


}

/*
void Put(int key, int value) {
int hash_val = HashFunc(key);
HashNode* prev = 0;
HashNode* entry = _table[hash_val];

while (entry != 0 && entry->key() != key) {
prev = entry;
entry = entry->next();
}

if (entry == 0) {
entry = new HashNode(key, value);
if (prev == 0) {
_table[hash_val] = entry;
} else {
prev->set_next(entry);
}
} else {
entry->set_value(value);
}
}
*/

template <class key_data, class value_data> void HashMap<key_data,value_data>::remove(key_data dat){
//removes the K,V pair given by the key_data arg
	int key = keyGen(dat);

	int hash_val = HashFunc(key);
	HashNode* entry = _table[hash_val];

	HashNode* prev = 0;

	//Traverse the ll, looking for either key or the tail
	while (entry != 0) {
		if (entry->getCurrentKey() == key) {
			break;
		}
		prev = entry;
		entry = entry->next();
	}
	if (entry == 0){
		//key was not present in the hashnode
		return;
	}
	else {
		if (prev == 0) {
			//if key is at the head, move the head to next
			_table[hash_val] = entry->next();
		} else {
			//otherwise set prev's next to be entry's next
			prev->set_next(entry->next());
		}
		//delete entry
		delete entry;
	}
}

/*
private:
// Hash table
HashNode** _table;
};
 */


#endif /*_HASHMAP_H_*/
