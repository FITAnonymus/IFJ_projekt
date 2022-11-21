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
#include "syntactic.h"

#define buffer_get_keyword buff

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
    if(search(p_table, key, TYPE_INTEGER_Q) != NULL){ //KEYWORD_INT_Q
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
 * Function checks whether variable of given name exists
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @param pp_table Pointer to parameter table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 */
int check_var_existence(char *key, Hash_table_ptr *p_table, PHash_table_ptr *pp_table){

    if(name_search(p_table, key) != NULL){
        return 0;
    } else{
        return ERR_SEMANTIC_DEF_VAR;
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
        return ERR_SEMANTIC_DEF_FCE;
    }
}

/**
 * Function checks whether there is a function with the same name and return type 
 *
 * @param item Pointer to the where the parameter type is stored and 
 *             it is updated after this function ends, to point to next
 *             parameter
 * @param type type of the argument of the function we are now checking
 * @return Returns true if type is ok, otherwise false
 */
int sem_check_argument(PItemPtr *item, int type){
    if((*item)->paramType == type) {
        *item = getNextParam(*item);
        return true;
    } else {
        return ERR_SEMANTIC_ARG_FCE;
    }
}


void can_be_null(Syntactic_data_ptr *data, buffer){
   if(!((strcmp( buffer_get_keyword, "KEYWORD_INT_Q" ) == 0) || (strcmp( buffer_get_keyword, "KEYWORD_FLOAT_Q" ) == 0) || (strcmp( buffer_get_keyword, "KEYWORD_STRING_Q" ) == 0))){
         (*data)->error_status  = ERR_SEMANTIC_OTHER;
   }
}

void redefine_function(Syntactic_data_ptr *data, char* key){
    if(name_psearch((*data)->function_var, key) != NULL){   
        (*data)->error_status = ERR_SEMANTIC_DEF_FCE;
    }
}

void check_return_type(Syntactic_data_ptr *data){
    if((strcmp( buffer_get_keyword, "KEYWORD_INT_Q" ) == 0) && ((what_i_get == TYPE_STRING) || (what_i_get == TYPE_NULL))){ // TODO how to recognize NULL value
 
    }

    else {
        (*data)->error_status = ERR_SEMANTIC_ARG_FCE
    }
}

void assertion(Syntactic_data_ptr *data){
    if(right == lValue){
        (*data)->local_var =
    } else {
        get_lValue()
    }
}

check_params(){
    if(-1) {
        bez param;
    }
    else if(-2){

    }
}

void process_buffer_fill_ptabel(Syntactic_data_ptr data){
    int i = 0;
    int len = data->buffer->length;
    // find and store name of function
    char *funName = NULL;
    while(i < len && (strcmp(data->buffer[i], KEYWORD_FUNCTION) != 0)){
        i++;
    }
    i++;
    funName = data->buffer[i]->type;
    // find and store return type of function
    int j = i;
    while(data->buffer[j] != TYPE_PAR_RIGHT){
        j++;
    }
    j++;
    int returnType = data->buffer[j];
    // insert params
    i++;
    while(data->buffer[i] != TYPE_PAR_RIGHT){
        
        pinsert(data->function_var, funName, data->buffer[i], returnType, data->buffer[i]);
        i++;
    }
    // process body
    
}

check_function(Syntactic_data_ptr *data){
    process_buffer_fill_ptabel(data);
    check_return_type();
    check_params();

}

/*
int condition(token_struct_attribute value){
    if(value == "0" || value == 0 || value = ""){
        return false
    } else {

    }
}*/

// TODO when checking function params, insert them to (*data)->local_var

void check_condition(Syntactic_data_ptr data){
    
}

void check_while(){

}

if(strict_types){
    check_function_parameter_types()
    cant_change_type_of_var()
}