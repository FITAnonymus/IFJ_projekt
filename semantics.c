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

#define INT "int"
#define INT_Q "intq"
#define FLOAT "float"
#define FLOAT_Q "floatq"
#define STR "String"
#define STR_Q "Stringq"


/**
 * Function checks the integer data type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */

bool check_int(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, INT) != NULL){
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
    if(search(p_table, key, INT_Q) != NULL){
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
    if(search(p_table, key, FLOAT) != NULL){
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
    if(search(p_table, key, FLOAT_Q) != NULL){
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
    if(search(p_table, key, STR) != NULL){
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
    if(search(p_table, key, STR_Q) != NULL){
        return true;
    } else {
        return false;
    }
}