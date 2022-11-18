/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of semantics.
    *
    * @author Martin Tomašovič <xtomas36@stud.fit.vutbr.cz>
    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.c"
#include<stdbool.h>
#include "scanner.h"

/*/
#define INT "int"
#define INT_Q "intq"
#define FLOAT "float"
#define FLOAT_Q "floatq"
#define STR "String"
#define STR_Q "Stringq" */


/**
 * Function checks the integer data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */

int check_int(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_INTEGER) != NULL){
        return 0;
    } else {

        return ERR_SEMANTIC_TYPE;;
    }
}

/**
 * Function checks the integer? data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */
int check_int_Q(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_INTEGER_Q) != NULL){
        return 0;
    } else {
        return ERR_SEMANTIC_TYPE;;
    }
}

/**
 * Function checks the float data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */

int check_float(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_FLOAT) != NULL){
        return 0;
    } else {
        return ERR_SEMANTIC_TYPE;
    }
}

/**
 * Function checks the float? data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */
int check_float_Q(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_FLOAT_Q) != NULL){
        return 0;
    } else {
        return ERR_SEMANTIC_TYPE;
    }
}

/**
 * Function checks the String data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */

int check_String(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_STRING) != NULL){
        return 0;
    } else {
        return ERR_SEMANTIC_TYPE;
    }
}

/**
 * Function checks the String? data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */
int check_String_Q(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_STRING_Q) != NULL){
        return 0;
    } else {
        return ERR_SEMANTIC_TYPE;
    }
}

/**
 * Function checks whether there is a function with the same name and return type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @param type return type of the function we are now checking
 * @param p_item returns pointer to the memory place where first parameter is stored through parameter
 * @return Returns whether this check succeeded or not 
 */
int sem_check_return(PHash_table_ptr *p_table, char *key, int type, PItemPtr *p_item){
    if(psearch(p_table, key, type) != NULL) { 
        return 0;
    } else {
        return ERR_SEMANTIC_RETURN;
    }
}

/**
 * Function checks whether there is a function with the same name and return type 
 *
 * @param item Pointer to the where the parameter type is stored and 
 *             it is updated after this function ends, to point to next
 *             parameter
 * @param type type of the parameter of the function we are now checking
 * @return Returns true if type is ok, otherwise false
 */
int sem_check_parameter(PItemPtr *item, int type){
    if((*item)->paramType == type) {
        *item = getNextParam(*item);
        return true;
    } else {
        return ERR_SEMANTIC_ARG_FCE;
    }
}