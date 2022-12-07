/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    * @file symtable.h
    * @brief Implementation of symtable.
    *
    * @author Martin Tomašovič <xtomas36@stud.fit.vutbr.cz>
    */

#ifndef SYMTABLE_H
#define SYMTABLE_H

//Definition of Item of table 
typedef struct item {
    char* key;
    char* value;
    int type;
    struct item *next;
} Item;

// Pointer to Item
typedef Item *ItemPtr;

// Definition of the hash table
typedef struct hash_table {
    Item** items;
    int size;
}Hash_table;


// Pointer to Hash_table
typedef Hash_table *Hash_table_ptr;

// Definition of the functiom hash table
typedef struct f_hash_table {
    Hash_table** fht;
    int size;
}f_Hash_table;

// Pointer to Hash_table
typedef f_Hash_table *f_Hash_table_ptr;


//Definition of Param item of table 
typedef struct Pitem {
    char* key;               // name of function
    char* value;             // name of param
    int type;              // return value of function
    int paramType;         // to describe type of parameter
    struct Pitem *nextParam; // pointer to next param of the same function
    struct Pitem *next;      // pointer to next item - function with same hash
} PItem;

// Pointer to Param Item
typedef PItem *PItemPtr;

// Definition of the hash table
typedef struct Phash_table {
    PItem** pitems;
    int size;
}PHash_table;

// Pointer to Hash_table
typedef PHash_table *PHash_table_ptr;

/*
//Definition of FunctionItem of table 
typedef struct fitem {
    Item params;
    Item ret_val;
    int num_of_items;
    struct fitem *next;
} fItem;

// Pointer to fItem
typedef fItem *fItemPtr;

// Definition of the hash table for functions
typedef struct fhash_table {
    fItem** fitems;
    int size;
}fHash_table;

// Pointer to fHash_table
typedef fHash_table *fHash_table_ptr;*/


int create_table(int size, Hash_table_ptr *hashTPtr);
void free_table(Hash_table_ptr p_table);
int insert(Hash_table_ptr *p_table, char* key, char* value, int type);
char* search(Hash_table_ptr *p_table, char* key, int type);
int create_ptable(int size, PHash_table_ptr *hashTPtr);
void free_ptable(PHash_table_ptr p_table);
PItemPtr name_psearch(PHash_table_ptr *p_table, char* key);
int pinsert(PHash_table_ptr *p_table, char* key, char* value, int type, int paramType);
ItemPtr name_search(Hash_table_ptr *p_table, char* key);
PItemPtr getNextParam(PItemPtr item);

#endif