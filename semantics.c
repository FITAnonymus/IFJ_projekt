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

bool check_int(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_INTEGER) != NULL){
        return true;
    } else {
        return false;
    }
}

/**
 * Function checks the integer? data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */
bool check_int_Q(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_INTEGER_Q) != NULL){
        return true;
    } else {
        return false;
    }
}

/**
 * Function checks the float data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */

bool check_float(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_FLOAT) != NULL){
        return true;
    } else {
        return false;
    }
}

/**
 * Function checks the float? data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */
bool check_float_Q(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_FLOAT_Q) != NULL){
        return true;
    } else {
        return false;
    }
}

/**
 * Function checks the String data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */

bool check_String(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_STRING) != NULL){
        return true;
    } else {
        return false;
    }
}

/**
 * Function checks the String? data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */
bool check_String_Q(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_STRING_Q) != NULL){
        return true;
    } else {
        return false;
    }
}

/**
 * Function checks whether there is a function with the same name and return type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @param type return type of the function we are now checking
 * @param ok returns whether this check succeeded or not through parameter
 * @return Returns pointer to the memory place where first parameter is stored
 */
PItemPtr sem_check_return(PHash_table_ptr *p_table, char *key, int type, bool *ok){
    if(psearch(p_table, key, type) != NULL) { 
        return true;
    } else {
        return false;
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
bool sem_check_parameter(PItemPtr *item, int type){
    if((*item)->paramType == type) {
        *item = getNextParam(*item);
        return true;
    } else {
        return false;
    }
}

