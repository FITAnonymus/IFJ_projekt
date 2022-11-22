/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of symtable.
    *
    * @author Martin Tomašovič <xtomas36@stud.fit.vutbr.cz>
    */

#include <stdlib.h>
#include <string.h>
#include "symtable.h"
#include "error.h"
#include "stdio.h"

//length of table inspired by https://planetmath.org/goodhashtableprimes
unsigned const int HLENGTH = 1543;

/**
 * Function receives word (identificator) and returns its hash.
 * From: https://pages.cs.wisc.edu/~siff/CS367/Notes/hash.html
 *
 * @param str Array of chars - String.
 * @return Returns hash value of given word.The hash value is of type unsigned integer.
 */


unsigned int hash(char *str) {
	unsigned long hash = 0;
    for (unsigned int i=0; str[i]; i++)
        hash += str[i];
    return hash % HLENGTH;
}


/**
 * Function creates one item and fills it with values in it's parameters.
 *
 * @param key Array of chars - String. Used for finding item in hashtable.
 * @param value Array of chars - String. Value you want to store.
 * @param type Array of chars - String. Used for checking type of given entity.
 * @return Returns 0 if everything ok, else it returns appropiate error code.
 */

int create_item(char* key, char* value, int type, ItemPtr* new_item) {


    ItemPtr p_item = (ItemPtr) malloc (sizeof(Item));
    if(p_item != NULL){
        p_item->key = (char*) malloc (strlen(key) + 1);
        p_item->value = (char*) malloc (strlen(value) + 1);

        //p_item->type = (char*) malloc (strlen(type) + 1);

        if((p_item->key == NULL) || (p_item->value == NULL)){ // || p_item->type == NULL)
            return ERR_INTERNAL;
        }
    
    strcpy(p_item->key, key);
    strcpy(p_item->value, value);

    p_item->type = type; //strcpy(p_item->type, type);
    p_item->next = NULL;
    } else {
        return ERR_INTERNAL;
    }
    *new_item = p_item;
    return 0;
}

/**
 * Function creates table and itializes it.
 *
 * @param size int
 * @param hashTPtr Pointer to struct hash_table.
 * @return Returns 0 if everything ok, else it returns appropiate error code.
 */
int create_table(int size, Hash_table_ptr *hashTPtr) {


    Hash_table_ptr h_table = (Hash_table_ptr) malloc (sizeof(Hash_table));
    if(h_table != NULL){
        h_table->size = size;
        h_table->items = (ItemPtr*) calloc (h_table->size, sizeof(ItemPtr));
        if(h_table->items != NULL){
            for (int i = 0; i < h_table->size; i++){
                h_table->items[i] = NULL;
            }
            *hashTPtr = h_table;
        } else {

            return ERR_INTERNAL;
        }
    } else {
        return ERR_INTERNAL;
    }
    return 0;
}

/**
 * Function removes one item.
 *
 * @param p_item Pointer to item we want to remove.
 */
void free_items(ItemPtr* p_item) {

    ItemPtr item;
    item = *p_item;

    ItemPtr help_pointer_item;

    while(item != NULL){
        
        help_pointer_item = item->next;


        // free all parts of item
        free(item->key);
        free(item->value);
        //free(item->type);

        // erase pointer to the item itself
        free(item);


        item = help_pointer_item;
    }
}


/**
 * Function frees all resources of table. 
 *
 * @param p_table Pointer to the table we want erase.
 */
void free_table(Hash_table_ptr p_table) {
    for (int i = 0; i < p_table->size; i++) {
        ItemPtr item = p_table->items[i];
        if (item != NULL)
            free_items(&item);

    }

    free(p_table->items);
    free(p_table);
}


/**
 * Function creates one item of hash table - uses create_item funtion and fills it with values in it's parameters.
 *
 * @param p_table Pointer to the table to which we want to add new item.
 * @param key Array of chars - String. Used for finding item in hashtable.
 * @param value Array of chars - String. Value you want to store.
 * @param type Array of chars - String. Used for checking type of given entity.
 * @return Returns 0 if everything ok, else it returns appropiate error code.
 */
int insert_type(Hash_table_ptr *p_table, char* key, char* value, int type) {
  
    ItemPtr p_item = NULL;
    create_item(key, value, type, &p_item);
    if(p_item != NULL){
        // Get index
        unsigned long index = hash(key);

        ItemPtr current_item = (*p_table)->items[index];
    
        if (current_item == NULL) {
            // Key does not exist
            // Create hash table item
            (*p_table)->items[index] = p_item;
        } else {

            /*

            // Go through all items with same hash and add new item to the end
            while(current_item->next != NULL){
                current_item =  current_item->next;
            }
            current_item->next = p_item;
            //current_item->next = NULL;

            */
            (*p_table)->items[index] = p_item;
            p_item->next = current_item;
            
        }
    } else {
        return ERR_INTERNAL;
    }
    return 0;
}

ItemPtr name_search(Hash_table_ptr *p_table, char* key){
    int index = hash(key);
    ItemPtr p_item = (*p_table)->items[index];
    // Ensure that we move to a non NULL item
    short continue_search = (p_item != NULL);
    //printf("\ncontinue = %d", continue_search);
    while(continue_search){
        //printf("\n now looking at %s\n", p_item->key);
        if((strcmp(p_item->key, key) == 0)){
            return p_item;
            continue_search = 0;
        }
        else {
            p_item = p_item->next;
            if(p_item == NULL){
                continue_search = 0;
            }
        }
    }
    return NULL;
}

/**
 * Function creates one item of hash table - uses create_item funtion and fills it with values in it's parameters.
 *
 * @param p_table Pointer to the table to which we want to add new item.
 * @param key Array of chars - String. Used for finding item in hashtable.
 * @param value Array of chars - String. Value you want to store.
 * @param type Array of chars - String. Used for checking type of given entity.
 * @return Returns 0 if everything ok, else it returns appropiate error code.
 */
int insert(Hash_table_ptr *p_table, char* key, char* value, int type) {
    ItemPtr lookedUpItem =  name_search(p_table, key);
    if(lookedUpItem == NULL) { // item with key doesn't exist
        ItemPtr p_item = NULL;
        create_item(key, value, type, &p_item);
        if(p_item != NULL) { // malloc ok
            // Get index
            unsigned long index = hash(key);
            
            if((*p_table)->items[index] == NULL){
                (*p_table)->items[index] = p_item;
            } else {
                ItemPtr current_item = (*p_table)->items[index];
                (*p_table)->items[index] = p_item;
                p_item->next = current_item;
            }
        } else { // malloc err
            return ERR_INTERNAL;
        }
    } else { // item with key exists
        lookedUpItem->type = type;
        // because the new value might be of different size we delete previous one
        free(lookedUpItem->value);
        // malloc new space
        lookedUpItem->value = (char*) malloc (strlen(value) + 1);
        if(lookedUpItem->value != NULL){ // malloc ok
            // insert new value
            strcpy(lookedUpItem->value, value);
        } else { // malloc failed
            return ERR_INTERNAL;
        }
    }
    return 0;
}

/**
 * Function searches for value of item given by parameters. 
 *
 * @param p_table Pointer to the table to which we want to add new item.
 * @param key Array of chars - String. Used for finding item in hashtable.
 * @param type Array of chars - String. Used for checking type of given entity.
 * @return Returns value of item given by parameters. Returns array of chars - String
 */
char* search(Hash_table_ptr *p_table, char* key, int type) {

    // Searches the key in the hashtable, returns NULL if it doesn't exist
    int index = hash(key);
    ItemPtr p_item = (*p_table)->items[index];

    // Ensure that we move to a non NULL item
    short continue_search = 0;

    if (p_item != NULL && (p_item->type == type)){
        continue_search = 1;
    }
    while(continue_search){
        if((strcmp(p_item->key, key) == 0) && (p_item->type == type)){

            continue_search = 0;
        }
        else {
            p_item = p_item->next;
            if(p_item == NULL){
                continue_search = 0;
            }
        }
    }
    // if item pointer isn't null, it means we found our key
    if (p_item != NULL){
        return p_item->value;

        
    }
    // there is no such key
    return NULL;
}


/**
 * Function creates one item for param table and fills it with values in it's parameters.
 *
 * @param key Array of chars - String. Used for finding item in hashtable.
 * @param value Array of chars - String. Value you want to store.
 * @param type Array of chars - String. Used for checking type of given entity.
 * @return Returns 0 if everything ok, else it returns appropiate error code.
 */

int create_pitem(char* key, char* value, int type, int paramType, PItemPtr* new_item) {

    PItemPtr p_item = (PItemPtr) malloc (sizeof(PItem));
    if(p_item != NULL){
        p_item->key = (char*) malloc (strlen(key) + 1);
        p_item->value = (char*) malloc (strlen(value) + 1);
        //p_item->type = (char*) malloc (strlen(type) + 1);
        //p_item->paramType = (char*) malloc (strlen(paramType) + 1);
        p_item->nextParam = NULL;
        if((p_item->key == NULL) || (p_item->value == NULL)){ // || p_item->type == NULL
            return ERR_INTERNAL;
        }
    
    strcpy(p_item->key, key);
    strcpy(p_item->value, value);
    p_item->type = type; //strcpy(p_item->type, type);
    p_item->paramType = paramType;//strcpy(p_item->paramType, paramType);
    p_item->next = NULL;
    } else {
        return ERR_INTERNAL;
    }
    *new_item = p_item;
    return 0;
}

/**
 * Function creates param table and itializes it.
 *
 * @param size int
 * @param hashTPtr Pointer to struct hash_table.
 * @return Returns 0 if everything ok, else it returns appropiate error code.
 */
int create_ptable(int size, PHash_table_ptr *hashTPtr) {

    PHash_table_ptr h_table = (PHash_table_ptr) malloc (sizeof(PHash_table));
    if(h_table != NULL){
        h_table->size = size;
        h_table->pitems = (PItemPtr*) calloc (h_table->size, sizeof(ItemPtr));
        if(h_table->pitems != NULL){
            for (int i = 0; i < h_table->size; i++){
                h_table->pitems[i] = NULL;
            }
            *hashTPtr = h_table;
        } else {
            return ERR_INTERNAL;
        }
    } else {
        return ERR_INTERNAL;
    }
    return 0;
}

/**
 * Function removes one item.
 *
 * @param p_pitem Pointer to item we want to remove.
 */
void free_Pitems(PItemPtr* p_item) {

    PItemPtr item;
    item = *p_item;
    PItemPtr help_pointer_item;

    while(item != NULL){
        
        help_pointer_item = item->next;
        while(item->nextParam != NULL){
            PItemPtr llitemptr = item->nextParam;
            item->nextParam = item->nextParam->nextParam;
             // free all parts of item
            free(llitemptr->key);
            free(llitemptr->value);
            //free(llitemptr->type);
            //free(llitemptr->paramType);

            // erase pointer to the item itself
            free(llitemptr);
        }
        // free all parts of item
        free(item->key);
        free(item->value);
        //free(item->type);
        //free(item->paramType);

        // erase pointer to the item itself
        free(item);

        item = help_pointer_item;
    }
}

/**
 * Function frees all resources of table. 
 *
 * @param p_table Pointer to the parameter table we want erase.
 */
void free_ptable(PHash_table_ptr p_table) {
    for (int i = 0; i < p_table->size; i++) {
        PItemPtr item = p_table->pitems[i];
        if (item != NULL)
            free_Pitems(&item);
    }

    free(p_table->pitems);
    free(p_table);
}

/**
 * Function searches for value of item given by parameters. 
 *
 * @param p_table Pointer to the table to which we want to add new item.
 * @param key Array of chars - String. Used for finding item in hashtable.
 * @param type Array of chars - String. Used for checking type of given entity.
 * @return Returns value of item given by parameters. Returns array of chars - String
 */
PItemPtr psearch(PHash_table_ptr *p_table, char* key, int type) {
    // Searches the key in the hashtable, returns NULL if it doesn't exist
    int index = hash(key);
    PItemPtr p_item = (*p_table)->pitems[index];

    // Ensure that we move to a non NULL item
    short continue_search = 0;
    if (p_item != NULL && p_item->type != type){ //(strcmp(p_item->type, type) != 0)
        continue_search = 1;
    }
    while(continue_search){
        if((strcmp(p_item->key, key) == 0) && (p_item->type == type)){ //(strcmp(p_item->type, type) == 0)
            continue_search = 0;
        }
        else {
            p_item = p_item->next;
            if(p_item == NULL){
                continue_search = 0;
            }
        }
    }
    // if item pointer isn't null, it means we found our key
    if (p_item != NULL){
        //printf("\nFound %d\n", p_item->type);
        return p_item;
    }
    // there is no such key
    return NULL;
}

/**
 * Function creates one item of parameter table - uses create_item funtion and fills it with values in it's parameters.
 *
 * @param p_table Pointer to the table to which we want to add new item.
 * @param key Array of chars - String. Used for finding item in hashtable.
 * @param value Array of chars - String. Value you want to store.
 * @param type Array of chars - String. Used for checking type of given entity.
 * @return Returns 0 if everything ok, else it returns appropiate error code.
 */
int pinsert_by_type(PHash_table_ptr *p_table, char* key, char* value, int type, int paramType) {
    PItemPtr p_item = NULL;
    create_pitem(key, value, type, paramType, &p_item);
    if(p_item != NULL){
        // Get index
        unsigned long index = hash(key);

        PItemPtr current_item = (*p_table)->pitems[index];
    
        if (current_item == NULL) {
            // Key does not exist
            // Create hash table item
            (*p_table)->pitems[index] = p_item;
        } else {
            PItemPtr search_result = psearch(p_table, key, type);
            if(search_result == NULL){ // this function is new
                (*p_table)->pitems[index] = p_item;
                p_item->next =  current_item;
            } else { // there is this function in table
                // Go through all items with same hash and add new item to the end
                while(search_result->nextParam != NULL){ // insert to the end to preserve parameters order
                    search_result = search_result->nextParam;
                }
                search_result->nextParam = p_item;
            }
        }
    } else {
        return ERR_INTERNAL;
    }
    return 0;
}

/**
 * Function searches for value of item given by parameters. 
 *
 * @param p_table Pointer to the table to which we want to add new item.
 * @param key Array of chars - String. Used for finding item in hashtable.
 * @param type Array of chars - String. Used for checking type of given entity.
 * @return Returns value of item given by parameters. Returns array of chars - String
 */
PItemPtr name_psearch(PHash_table_ptr *p_table, char* key) {
    // Searches the key in the hashtable, returns NULL if it doesn't exist
    int index = hash(key);
    PItemPtr p_item = (*p_table)->pitems[index];

    // Ensure that we move to a non NULL item
    short continue_search = 0;
    if (p_item != NULL ){ //&& p_item->type == type  (strcmp(p_item->type, type) != 0)
        continue_search = 1;
    }
    while(continue_search){
        if((strcmp(p_item->key, key) == 0)){ //&& p_item->type == type  (strcmp(p_item->type, type) == 0)
            continue_search = 0;
        }
        else {
            p_item = p_item->next;
            if(p_item == NULL){
                continue_search = 0;
            }
        }
    }
    // if item pointer isn't null, it means we found our key
    if (p_item != NULL){
        return p_item;

        
    }
    // there is no such key
    return NULL;
}

/**
 * Function creates one item of parameter table - uses create_item funtion and fills it with values in it's parameters.
 *
 * @param p_table Pointer to the table to which we want to add new item.
 * @param key Array of chars - String. Used for finding item in hashtable.
 * @param value Array of chars - String. (name of param) Value you want to store.
 * @param type Array of chars - String. (return type of function) Used for checking type of given entity.
 * @param paramType Array of chars - String. (type of parameter) Used for checking type of given entity.
 * @return Returns 0 if everything ok, else it returns appropiate error code.
 */
int pinsert(PHash_table_ptr *p_table, char* key, char* value, int type, int paramType) {
    PItemPtr p_item = NULL;
    create_pitem(key, value, type, paramType, &p_item);
    if(p_item != NULL){
    PItemPtr lookedUpItem = name_psearch(p_table, key);
    if((lookedUpItem != NULL) && (psearch(p_table, key, type) == NULL)){
        free_Pitems(&p_item);
        return ERR_SEMANTIC_DEF_FCE; // define the same function with different return type
    }
    if(lookedUpItem == NULL){
        
            // Get index
            unsigned long index = hash(key);
            if ((*p_table)->pitems[index] == NULL) {
                // Key does not exist
                // Create hash table item
                (*p_table)->pitems[index] = p_item;
            } else { // insert at begining of synonym list
                PItemPtr current_item = (*p_table)->pitems[index];
                (*p_table)->pitems[index] = p_item;
                p_item->next = current_item;
            }
        
        } else { // there is an item of this function need to add another parameter
            while(lookedUpItem->nextParam != NULL){ // insert to the end to preserve parameters order
                lookedUpItem = lookedUpItem->nextParam;
            }
            lookedUpItem->nextParam = p_item;
        }
    } else {
        return ERR_INTERNAL;
    }    
    return 0;
}

PItemPtr getNextParam(PItemPtr item){
    return item->nextParam;
}









/**
 * Function creates array of hash tables. Uses function create_table.
 *
 * @param size int
 * @param hashTPtr Pointer to the array
 * @return Returns 0 if everything ok, else it returns appropiate error code.
 */
int create_function_table(int size, Hash_table_ptr *hashTPtr) {

    hashTPtr = (Hash_table_ptr *) malloc(size * sizeof(Hash_table_ptr));
    if(hashTPtr ==  NULL){
        return ERR_INTERNAL;
    }
    else {
        for(int  i = 0; i < size; i++) {
            create_table(HLENGTH, &hashTPtr[i]);
        }
    }
    return 0;
}

/**
 * Function removes array of hash tables. Uses function free_table.
 *
 * @param hashTPtr Pointer to the array of tables
 */
void free_function_hash_table(Hash_table_ptr **hashTPtr, int size){
    for(int i = 0; i < size; i++){
        free_table(*hashTPtr[i]);
    }
    free(hashTPtr);
}

// for testing
void print_search(Hash_table_ptr* table, char* key, int type) {

    char* val;
    if(table != NULL){
    if ((val = search(table, key, type)) == NULL) {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else {
        printf("Key:%s, Value:%s\n", key, val);
    }
    }
}


void print_psearch(PHash_table_ptr* table, char* key, int type) {
    char* val;
    PItemPtr item = NULL;
    if(table != NULL){
    if ((item = psearch(table, key, type)) == NULL) {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else {
        while(item != NULL){
            val = item->value;
            printf("Key:%s, Value:%s\n", key, val);
            item = item->nextParam;
        }
        
    }
    }
}


void print_table(Hash_table_ptr table) {
    printf("\nHash Table\n-------------------\n");
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            ItemPtr p_i = table->items[i];
            while(p_i != NULL){
                printf("Index:%d, Key:%s, Value:%s\n", i, p_i->key, p_i->value);
                p_i = p_i->next;
            } 
        }

        //printf("***\n");
    }
    printf("-------------------\n\n");
}


/*
int main() {
    Hash_table_ptr ht = NULL;
    create_table(LENGTH, &ht);
    insert(&ht, "1", "First address", 1);
    insert(&ht, "2", "Second address", 1);
    insert(&ht, "2", "Third address", 2);
    
    if(ht == NULL){
        printf("table is void");
    }
    print_search(&ht, "1", 1);
    print_search(&ht, "2", 2);
    print_search(&ht, "3", 3);
    print_table(ht);

    printf("\n\n");
    bool found = (name_search(&ht, "1") != NULL);
    if(found) {
         printf("1 found");
    } else {
         printf("1 not found");
    }
   
    printf("\n");
    found = (name_search(&ht, "2") != NULL);
    if(found) {
         printf("2 found");
    } else {
         printf("2 not found");
    }

    printf("\n");
    found = (name_search(&ht, "10") != NULL);
    if(found) {
         printf("10 found");
    } else {
         printf("10 not found");
    }
    
    free_table(ht);

//////////////////////////////////////////////
    printf("\n");
    PHash_table_ptr htp = NULL;
    create_ptable(LENGTH, &htp);
    pinsert(&htp, "1", "param1", 1, 2);
    pinsert(&htp, "1", "param2", 1, 4);
    pinsert(&htp, "2", "Second address", 1, 4);
    pinsert(&htp, "2", "Third address", 2, 5);
    printf("\nInserting key5\n");
    pinsert(&htp, "key:5", "value: Third address", 2, 5);
    pinsert(&htp, "key:5", "value: Third address", 3, 5);
    if(htp == NULL){
        printf("table is void");
    }
    print_psearch(&htp, "1", 1);
    print_psearch(&htp, "1", 1);
    print_psearch(&htp, "2", 2);
    print_psearch(&htp, "2", 1);
    print_psearch(&htp, "3", 3);
    print_psearch(&htp, "key:5", 2);
    //print_table(ht);
    free_ptable(htp);

printf("\n????????????????????????????");
/////////////////////////////////////////////////////////////////

    // How to create functions hash table
    int size = 10;
    // Alloc memory
    Hash_table_ptr *htf = (Hash_table_ptr *) malloc(size * sizeof(Hash_table_ptr));
    //check memory alloc
    if(htf !=  NULL){
        // insert
        for(int i = 0; i < 10; i++) {
            create_table(LENGTH, &htf[i]);
            if(i == 3){
                insert(&htf[i], "6", "First address", 1);
                insert(&htf[i], "5", "Second address", 1);
                insert(&htf[i], "3", "Third address", 2);
            }
            else {
                insert(&htf[i], "1", "First address", 1);
                insert(&htf[i], "2", "Second address", 1);
                insert(&htf[i], "2", "Third address", 2);
            }
        }

        // resize
        int newsize = size + 5;
        htf = (Hash_table_ptr *) realloc(htf, newsize * sizeof(Hash_table_ptr));
    
        // read
        print_search(&htf[0], "1", 1);
        print_search(&htf[3], "6", 1);

        // free
        for(int i = 0; i < 10; i++) {
            free_table(htf[i]);
        }
        // Don't forget to free the pointer to all funtion hash tables
        free(htf);
    }
    
      
    return 0;
}

*/

/*
// Functions for function hash-table

int create_fitem(char* key, char* value, char* type, ItemPtr* new_item) {

    ItemPtr p_item = (ItemPtr) malloc (sizeof(Item));
    if(p_item != NULL){
        p_item->key = (char*) malloc (strlen(key) + 1);
        p_item->value = (char*) malloc (strlen(value) + 1);
        p_item->type = (char*) malloc (strlen(type) + 1);

        if((p_item->key == NULL) || (p_item->value == NULL || p_item->type == NULL)){
            return ERR_INTERNAL;
        }
    
        strcpy(p_item->key, key);
        strcpy(p_item->value, value);
        strcpy(p_item->type, type);
        p_item->next = NULL;
    } else {
        return ERR_INTERNAL;
    }
    *new_item = p_item;
    return 0;
}

int create_table(int size, Hash_table_ptr *hashTPtr) {

    Hash_table_ptr h_table = (Hash_table_ptr) malloc (sizeof(Hash_table));
    if(h_table != NULL){
        h_table->size = size;
        h_table->items = (ItemPtr*) calloc (h_table->size, sizeof(ItemPtr));
        if(h_table->items != NULL){
            for (int i = 0; i < h_table->size; i++){
                h_table->items[i] = NULL;
            }
            *hashTPtr = h_table;
        } else {
            return ERR_INTERNAL;
        }
    } else {
        return ERR_INTERNAL;
    }
    return 0;
}

void free_items(ItemPtr* p_item) {

    ItemPtr item;
    item = *p_item;
    ItemPtr help_pointer_item;

    while(item != NULL){
        
        help_pointer_item = item->next;

        // free all parts of item
        free(item->key);
        free(item->value);
        free(item->type);

        // erase pointer to the item itself
        free(item);

        item = help_pointer_item;
    }
}

void free_table(Hash_table_ptr p_table) {
    for (int i = 0; i < p_table->size; i++) {
        ItemPtr item = p_table->items[i];
        if (item != NULL)
            free_items(&item);
    }

    free(p_table->items);
    free(p_table);
}

int insert(Hash_table_ptr *p_table, char* key, char* value, char* type) {
    ItemPtr p_item = NULL;
    create_item(key, value, type, &p_item);
    if(p_item != NULL){
        // Get index
        unsigned long index = hash(key);

        ItemPtr current_item = (*p_table)->items[index];
    
        if (current_item == NULL) {
            // Key does not exist
            // Create hash table item
            (*p_table)->items[index] = p_item;
        } else {
            // Go through all items with same hash and add new item to the end
            while(current_item->next != NULL){
                current_item =  current_item->next;
            }
            current_item->next = p_item;
            //current_item->next = NULL;
        }
    } else {
        return ERR_INTERNAL;
    }
    return 0;
}

char* search(Hash_table_ptr *p_table, char* key, char* type) {
    // Searches the key in the hashtable, returns NULL if it doesn't exist
    int index = hash(key);
    ItemPtr p_item = (*p_table)->items[index];

    // Ensure that we move to a non NULL item
    short continue_search = 0;
    if (p_item != NULL && (strcmp(p_item->type, type) != 0)){
        continue_search = 1;
    }
    
    while(continue_search){
        if((strcmp(p_item->key, key) == 0) && (strcmp(p_item->type, type) == 0)){
            continue_search = 0;
        }
        else {
            p_item = p_item->next;
            if(p_item == NULL){
                continue_search = 0;
            }
        }
    }
    // if item pointer isn't null, it means we found our key
    if (p_item != NULL){
        return p_item->value;

        
    }
    // there is no such key
    return NULL;
}
*/

