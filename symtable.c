/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of symtable.
    *
    * @author Martin Tomašovič <xtomas36@stud.fit.vutbr.cz>
    */

#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AllocErr(){
    return;
}

unsigned int hash(char *str) {
	unsigned long hash = 0;
    for (unsigned int i=0; str[i]; i++)
        hash += str[i];
    return hash % LENGTH;
}

void create_item(char* key, char* value, char* type, ItemPtr* new_item) {

    ItemPtr p_item = (ItemPtr) malloc (sizeof(Item));
    if(p_item != NULL){
        p_item->key = (char*) malloc (strlen(key) + 1);
        p_item->value = (char*) malloc (strlen(value) + 1);
        p_item->type = (char*) malloc (strlen(type) + 1);

        if((p_item->key == NULL) || (p_item->value == NULL || p_item->type == NULL)){
            AllocErr();
            return;
        }
    
    strcpy(p_item->key, key);
    strcpy(p_item->value, value);
    strcpy(p_item->type, type);
    p_item->next = NULL;
    } else {
        AllocErr();
        return;
    }
    *new_item = p_item;
    return;
}

void create_table(int size, Hash_table_ptr *hashTPtr) {

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
            AllocErr();
        }
    } else {
        AllocErr();
    }
    return;
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

void insert(Hash_table_ptr *p_table, char* key, char* value, char* type) {
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
        AllocErr();
    }
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

// for testing
void print_search(Hash_table_ptr* table, char* key, char* type) {
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
        printf("***\n");
    }
    printf("-------------------\n\n");
}


int main() {
    Hash_table_ptr ht = NULL;
    create_table(LENGTH, &ht);
    insert(&ht, "1", "First address", "int");
    insert(&ht, "2", "Second address", "int");
    insert(&ht, "2", "Third address", "char");
    if(ht == NULL){
        printf("table is void");
    }
    print_search(&ht, "1", "int");
    print_search(&ht, "2", "char");
    print_search(&ht, "3", "void");
    //print_table(ht);
    free_table(ht);
    return 0;
}