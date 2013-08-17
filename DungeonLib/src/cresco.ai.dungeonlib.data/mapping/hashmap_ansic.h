#ifndef _HASHMAP_ANSIC_H_
#define _HASHMAP_ANSIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//control vars
//int listCount

//structs
//hmm, well we'd like to do something similar to a C++ template class with the
//abstractObject struct so as to maintain ansi C compliance
//one potential approach might be to make the abstractObject struct consist of
//only a void* which will be cast to the desired pointer type upon use, and then set to 
//a proper address value.  Optionally, you can set the myType char array to the actualized type 
//once it has been assigned, for verification and check use cases
//only reason to have this struct rather than a void* member of the linkedList struct is
//for the purpose of adding nifty features if desirable.
typedef struct {
	const void* myObject;
	char* myType;
}abstractObject;

//w00t, a 2-way traversable circular linked list in C FTW!!
typedef struct _list_t_{
	char *str;
	abstractObject* value; //could just be void* but hey let's vagazzle this bitch!
    struct _list_t_* pNext;
	struct _list_t_* pPrevious;
	struct _list_t_* pLinkedListHead; //set only when the list is first created as the address of the oject currently being added
	struct _list_t_* pLinkedListTail; //set anew each time a new object is added to the end of the list to the address of the new object
}linkedList;

//holy $hit, it's a hashmap in ansi C!!
typedef struct _hash_table_t_{
	int size;       /* the size of the table */
    linkedList** table; /* pointer to the table elements array -- What we have is a pointer to a pointer to a linked list; thus list_t **table.  Used because we don't know the size of the hashtable to begin with....  */
}hashmap_c;

//data manipulation functions

//hashmap constructor
hashmap_c* create_hash_table(int size)
{
	
    hashmap_c* newMap;
    
    if (size<1) return NULL; /* invalid size for table */

    /* Attempt to allocate memory for the table structure */
    if ((newMap = (hashmap_c*)malloc(sizeof(hashmap_c))) == NULL) {
        return NULL;
    }
    
    /* Attempt to allocate memory for the table itself */
    if ((newMap->table = (linkedList**)malloc(sizeof(linkedList *) * size)) == NULL) {
        return NULL;
    }

    /* Initialize the elements of the table */
	int i;
    for(i=0; i<size; i++) newMap->table[i] = NULL;

    /* Set the table's size */
    newMap->size = size;

    return newMap;
}

//Calculate the address a string will be stored at based on its value.
unsigned int hash(hashmap_c* hashMap, char *str)
{
    unsigned int hashval;
    
    /* we start our hash out at 0 */
    hashval = 0;

    /* for each character, we multiply the old hash by 31 and add the current
     * character.  Remember that shifting a number left is equivalent to 
     * multiplying it by 2 raised to the number of places shifted.  So we 
     * are in effect multiplying hashval by 32 and then subtracting hashval.  
     * Why do we do this?  Because shifting and subtraction are much more 
     * efficient operations than multiplication.
     */
    for(; *str != '\0'; str++) hashval = *str + ((hashval << 5) - hashval);

    /* we then return the hash value mod the hashtable size so that it will
     * fit into the necessary range
     */
    return hashval % hashMap->size;
}

//Get a given string iff it is in the map
linkedList* lookup_string(hashmap_c* hashMap, char *str)
{
    linkedList *list;
    unsigned int hashval = hash(hashMap, str);

    /* Go to the correct list based on the hash value and see if str is
     * in the list.  If it is, return return a pointer to the list element.
     * If it isn't, the item isn't in the table, so return NULL.
     */
    for(list = hashMap->table[hashval]; list != NULL; list = list->pNext) {
        if (strcmp(str, list->str) == 0) return list;
    }
    return NULL;
}

//Get a given string key's associated value iff the key is in the map
abstractObject* getValueByKey(hashmap_c* hashMap, char *strKey)
{
    linkedList *list;
    unsigned int hashval = hash(hashMap, strKey);

    /* Go to the correct list based on the hash value and see if str is
     * in the list.  If it is, return return a pointer to the abstractObject member of the list.
     * If it isn't, the item isn't in the table, so return NULL.
     */
    for(list = hashMap->table[hashval]; list != NULL; list = list->pNext) {
        if (strcmp(strKey, list->str) == 0) return list->value;
    }
    return NULL;
}

//Insert String with no paired value
int add_string(hashmap_c* hashMap, char *str)
{
    linkedList *new_list;
    linkedList *current_list;
    unsigned int hashval = hash(hashMap, str);

    /* Attempt to allocate memory for list */
    if ((new_list = (linkedList*)malloc(sizeof(linkedList))) == NULL) return 1;

    /* Does item already exist? */
    current_list = lookup_string(hashMap, str);
        
   if (current_list != NULL){
		/* item already exists, either don't insert it again or add it to the linked list as a handled collision element. */
		//handle new assignment of listTail, don't alter listHead here
		return 2; //the "don'insert it again" method... 
	}
	else{
    /* Else, Insert into list */
	//at this point, we are definitly adding the first member of the list so set it as both
	//list head and list tail...
    new_list->str = strdup(str);
	new_list->value = NULL; //set value to null pointer in this function
    new_list->pNext = hashMap->table[hashval];
	new_list->pPrevious = hashMap->table[hashval];
	new_list->pLinkedListHead = hashMap->table[hashval];
	new_list->pLinkedListTail = hashMap->table[hashval];
    hashMap->table[hashval] = new_list;
	}
	
    return 0;
}

//Insert String and paired value
int putStringValPair(hashmap_c* hashMap, char *str, abstractObject* myVal)
{
    linkedList *new_list;
    linkedList *current_list;
    unsigned int hashval = hash(hashMap, str);

    /* Attempt to allocate memory for list */
    if ((new_list = (linkedList*)malloc(sizeof(linkedList))) == NULL) return 1;

    /* Does item already exist? */
    current_list = lookup_string(hashMap, str);
        
   if (current_list != NULL){ //collision case
		/* item already exists, either don't insert it again or add it to the linked list as a handled collision element. */
		//handle new assignment of listTail, don't alter listHead here
		return 2; //the "don'insert it again" method... 
	}
	else{ //usual case
    /* Else, Insert into list */
	//at this point, we are definitly adding the first member of the list so set it as both
	//list head and list tail...
    new_list->str = strdup(str);
	new_list->value = myVal; //set value member to the address of the object passed in as myVal
    new_list->pNext = hashMap->table[hashval];
	new_list->pPrevious = hashMap->table[hashval];
	new_list->pLinkedListHead = hashMap->table[hashval];
	new_list->pLinkedListTail = hashMap->table[hashval];
    hashMap->table[hashval] = new_list;
	}
	
    return 0;
}

void free_table(hashmap_c* hashMap)
{
    int i;
    linkedList *list, *temp;

    if (hashMap==NULL) return;

    /* Free the memory for every item in the table, including the 
     * strings themselves.
     */
    for(i=0; i<hashMap->size; i++) {
        list = hashMap->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->pNext;
            free(temp->str);
            free(temp);
        }
    }

    /* Free the table itself */
    free(hashMap->table);
    free(hashMap);
}

#endif /*_HASHMAP_ANSIC_H_*/
