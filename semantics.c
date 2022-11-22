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
#include <stdbool.h>
#include "scanner.h"
#include "syntactic.h"
#include "error.h"

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

void check_return_type(Syntactic_data_ptr *data){
    
    // find return 
    if((*data)->)

    if((strcmp( buffer_get_keyword, "KEYWORD_INT_Q" ) == 0) && ((what_i_get == TYPE_STRING) || (what_i_get == TYPE_NULL))){ // TODO how to recognize NULL value
 
    }

    else {
        (*data)->error_status = ERR_SEMANTIC_ARG_FCE
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
void sem_check_argument(Syntactic_data_ptr *data, int indexInBuffer, char *name, PItemPtr pitem){
    //PItem name_search((*data)->used_var;
    // chceck wheter the variable exists in symtable
    char *var_name =  (*data)->buffer.token[indexInBuffer].buf;
    ItemPtr argument = name_search((*data)->used_var, var_name);
    if(argument == NULL){
        (*data)->error_status = ERR_SEMANTIC_DEF_VAR;
        return;
    }
    // check whether type of variable is the same as required parameter type
    if(pitem->paramType != argument->type) {
        (*data)->error_status =  ERR_SEMANTIC_ARG_FCE;
        return;
    }
}

void sem_check_arguments(Syntactic_data_ptr *data){
    int i = 0;
    // find function name
    while((*data)->buffer.token[i].type != TYPE_FUNCTION_ID){
        i++;
    }
    PItemPtr pitem = name_psearch((*data)->function_var, (*data)->buffer.token[i].buf);
    while((*data)->buffer.token[i].type != TYPE_BRACE_LEFT){
        i++;
    }
    i++;
    while((*data)->buffer.token[i].type != TYPE_BRACE_RIGHT){
        if((*data)->buffer.token[i].type == TYPE_VARIABLE_ID){
            // too much arguments
            if(pitem == NULL){
                (*data)->error_status = ERR_SEMANTIC_ARG_FCE;
                return;
            }
            // check var existance and type
            sem_check_argument(data, i, (*data)->buffer.token[i].buf, pitem);
            pitem = getNextParam(pitem);
        } else {
            switch((*data)->buffer.token[i].type){
                // if comma nothing to do
                case TYPE_COMMA:
                    break;
                // compare constant type with parameter type and move pitem to next parameter
                case TYPE_INTEGER:
                    if(pitem->paramType != TYPE_INTEGER){
                        (*data)->error_status = ERR_SEMANTIC_ARG_FCE;
                        return;
                    }
                     pitem = getNextParam(pitem);
                    break;
                case TYPE_FLOAT:
                    pitem = getNextParam(pitem);
                    if(pitem->paramType != TYPE_FLOAT){
                        (*data)->error_status = ERR_SEMANTIC_ARG_FCE;
                        return;
                    }
                    break;
                case TYPE_STRING:
                    if(pitem->paramType != TYPE_STRING){
                        (*data)->error_status = ERR_SEMANTIC_ARG_FCE;
                        return;
                    }
                     pitem = getNextParam(pitem);
                    break;
            }
        }
        i++;
    }
    // not enough arguments
    if(pitem != NULL){
        (*data)->error_status = ERR_SEMANTIC_ARG_FCE;
        return;
    }
}


void can_be_null(Syntactic_data_ptr *data, buffer){
   if(!((strcmp( buffer_get_keyword, "KEYWORD_INT_Q" ) == 0) || (strcmp( buffer_get_keyword, "KEYWORD_FLOAT_Q" ) == 0) || (strcmp( buffer_get_keyword, "KEYWORD_STRING_Q" ) == 0))){
         (*data)->error_status  = ERR_SEMANTIC_OTHER;
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

/*
void redefine_function(Syntactic_data_ptr *data, char* key){
    if(name_psearch((*data)->function_var, key) != NULL){   
        (*data)->error_status = ERR_SEMANTIC_DEF_FCE;
    }
}*/

void process_funBody(){
    //TODO
}

void process_buffer_fill_ptabel(Syntactic_data_ptr *data){
    int i = 0;
    //data->buffer.token[i].type;
    int len = (*data)->buffer.lenght;
    // find and store name of function
    char *funName = NULL;
    while(i < len && ((*data)->buffer.token[i].type != TYPE_FUNCTION_ID)){
        i++;
    }
    funName = (*data)->buffer.token[i].buf;
    // check whether the function was defined
    if(name_psearch((*data)->function_var,funName) != NULL){
        // redefined function
        (*data)->error_status = ERR_SEMANTIC_DEF_FCE;
        return;
    }
    // find and store return type of function
    int j = i;
    while((*data)->buffer.token[j].type != TYPE_PAR_RIGHT){
        j++;
    }
    j++;
    int returnType = (*data)->buffer.token[j].type;
    // insert params
    i++;
    while((*data)->buffer.token[i].type != TYPE_PAR_RIGHT){
        //if((*data)->buffer.token[i].type != TYPE_COMMA){
            if((*data)->buffer.token[i].type == TYPE_VARIABLE_ID){
                // insert param to ptable
                pinsert((*data)->function_var, funName, (*data)->buffer.token[i].buf, returnType, (*data)->buffer.token[i].type); 
            }
        //}
        
        i++;
    }
}

check_function_definition(Syntactic_data_ptr *data){
    process_buffer_fill_ptabel(data);
    if((*data)->error_status != 0){
        return;
    }
    // process body
    process_funBody();
}

check_function_call(Syntactic_data_ptr *data){
    sem_check_arguments(data);
    //TODO check_return_type(); // check if in assertion
}

/*
int condition(token_struct_attribute value){
    if(value == "0" || value == 0 || value = ""){
        return false
    } else {

    }
}*/

// TODO when checking function params, insert them to (*data)->local_var
int check_type(int type, Syntactic_data_ptr *data){
    switch(type){
            case TYPE_VARIABLE_ID:
                // save var type
                ItemPtr variable = name_search((*data)->used_var, (*data)->buffer.token[bufferIndex].buf);
                return variable->type;
                break;
            case TYPE_FUNCTION_ID:
                // save fun return type
                PItemPtr function = name_psearch((*data)->function_var, (*data)->buffer.token[bufferIndex].buf);
                return function->type;
                break;
            case TYPE_INTEGER:
                return TYPE_INTEGER;
                break;
            case TYPE_FLOAT:
                return TYPE_FLOAT;
                break;
            case TYPE_STRING:
                return TYPE_STRING;
                break;
            default:
                return -1;
                break;
        }
}


// return 1 if we dont know the output, 0 if the result will be false
int check_condition(Syntactic_data_ptr *data, int bufferIndex){
    int leftType;
    int rightType;
    if((*data)->buffer.token[bufferIndex].type == TYPE_PAR_RIGHT){ // the condition looks like ()
        (*data)->error_status = ERR_SEMANTIC_OTHER;
        return;
    } else{
        int nowCheckingTokenType = (*data)->buffer.token[bufferIndex].type;
        if(check_type(nowCheckingTokenType, data) == -1) {
            (*data)->error_status = ERR_SEMANTIC_OTHER;
            return;
        }
        else {
            leftType = nowCheckingTokenType;
        }
        nowCheckingTokenType = (*data)->buffer.token[bufferIndex + 2].type;
        if(check_type(nowCheckingTokenType, data) == -1) {
            (*data)->error_status = ERR_SEMANTIC_OTHER;
            return;
        }
        else {
            if(leftType != nowCheckingTokenType){
                return 0;
            } else {
                return 1;
            }
        }
    }
}

void check_if(Syntactic_data_ptr *data){
    int i = 0;
    while((*data)->buffer.token[i].type != TYPE_PAR_LEFT){
        i++;
    }
    i++;
    check_condition(data, i);
}

void check_while(Syntactic_data_ptr *data){
    int i = 0;
    while((*data)->buffer.token[i].type != TYPE_PAR_LEFT){
        i++;
    }
    i++; // now i is index of next token after left paranethesis
    check_condition(data, i);
}

/*
if(strict_types){
    check_function_parameter_types()
    cant_change_type_of_var()
}
*/