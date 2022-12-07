/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of semantics.
    *
    * @author Martin Tomašovič <xtomas36@stud.fit.vutbr.cz>
    */

#include "semantics.h"
#include "symtable.h"
const int TABLE_SIZE = 97;

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
 * Function converts KEYWORD token types to TYPE token types
 *
 * @param type token type of sources
 * @return Returns token type TYPE_INTEGER/FLOAT/STRING
 */
int keywordToType(int type){
    switch(type){
        case KEYWORD_INT:
            return TYPE_INTEGER;
            break;
        case KEYWORD_FLOAT:
            return TYPE_FLOAT;
            break;
        case KEYWORD_STRING:
            return TYPE_STRING;
            break;
        case KEYWORD_STRING_Q:
            return TYPE_STRING;
            break;
        case KEYWORD_FLOAT_Q:
            return TYPE_FLOAT;
            break;
        case KEYWORD_INT_Q:
            return TYPE_INTEGER;
        default:
            return -1;
            break;
        return 0;
    }
}

/**
 * Function evaluates token type and calls check_type_a_exist function
 * to check it if the token was variable or function  whether they were declared
 *
 * @param data Used to access token
 * @param startINdex where control starts
 * @param endingType where to stop expression control
 * @param endIndex to move index variable when called recursively used to handle (5+(5*9)) type of problem
 * @return Returns type of result of the expression or internal error -1 to propagate higher
 */
int sem_check_expression(Syntactic_data_ptr data, int startIndex, int endingType, int endingType2, int *endIndex){
   
    int i = startIndex;
    int currentType = check_type_a_exist(data, i, &i);
    int resultType = currentType;
    // current type is -1 if there was error in check_type_a_exist
    if(currentType == -1) {
        return -1;
    }
    
    //iterate over all operators and determine type of expression
    while(currentType != endingType && currentType != endingType2){ 
        if(currentType == TYPE_PLUS || currentType == TYPE_MINUS || currentType == TYPE_MUL) {
            int nextTokType = check_type_a_exist(data, i+1, &i);
            //propagate error
            if(nextTokType == -1) {
                return -1;
            }
            if((nextTokType == TYPE_INTEGER || nextTokType == TYPE_VARIABLE_ID || nextTokType == TYPE_FUNCTION_ID) && (resultType == TYPE_INTEGER || resultType == KEYWORD_NULL) ){
                resultType = TYPE_INTEGER;
            } else {
                if(nextTokType == TYPE_FLOAT && ((resultType == TYPE_INTEGER || resultType == KEYWORD_NULL))) {
                    resultType = TYPE_FLOAT;
                }
            }

        } else if(currentType == TYPE_DIV){

            int nextTokType = check_type_a_exist(data, i+1, &i);
            //propagate error
            if(nextTokType == -1) {
                return -1;
            }
            resultType = TYPE_FLOAT;

        } else if(currentType == TYPE_CONCAT){
            int nextTokType = check_type_a_exist(data, i+1, &i);//(*data)->buffer.token[i+1]->type;
            if(nextTokType == TYPE_STRING || nextTokType == TYPE_VARIABLE_ID || nextTokType == TYPE_FUNCTION_ID){
                //propagate error
                if(nextTokType == -1){
                    return -1;
                }
                resultType = TYPE_STRING;
            }
            else {
                (data)->error_status = ERR_SEMANTIC_TYPE;
                return -1; 
            }
        }
        else if (currentType == TYPE_PAR_RIGHT) {
            i++;
        }
        
        currentType = (data)->buffer.token[i]->type;
       
    }
    *endIndex = i; 
    
    return resultType;
}

/**
 * Function checks the integer data type
 *
 * @param data 
 * @param index Pointer to table where is the item we are searching for
 * @return Returns 0 if type is ok, otherwise -1
 */
int assertion(Syntactic_data_ptr data, int index){
    ItemPtr var = name_search(&((data)->used_var), (data)->buffer.token[index]->buf->buf);
        if(var != NULL){
        (data)->error_status = ERR_SEMANTIC_DEF_VAR;
        return -1;
    }
    int varType = var->type;
    int i = index;
    while((data)->buffer.token[i]->type != TYPE_ASSIGN){
        i++;
    }
    i++;
    // now i is index of first token of expression;
    int endingIndex = 0; // here doesnt matter
    //get type of expression
    int rightType = sem_check_expression(data, i, TYPE_SEMICOLON,TYPE_SEMICOLON, &endingIndex);
    if(rightType == -1){
        return -1;
    }
    
    // change type of variable in symtable if different
    if(varType != rightType){
        if(insert(&((data)->used_var), var->key, var->value, rightType) != 0){
            return -1;
        }
    }
    return 0;
}

/**
 * Function checks declaration of variable
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param index Pointer to table where is the item we are searching for
 * @return Returns 0 if type is ok, otherwise -1
 */
int var_declaration(Syntactic_data_ptr data, int index, int expectedType, int nullSupport, int *endIndex, int fromFunction){
   
    Hash_table_ptr h_table = NULL;
    if(fromFunction == 1) {
        h_table = data->local_var; 
    } else {
        h_table = data->main_var;
    }
    ItemPtr var = name_search(&(data->used_var), (data)->buffer.token[index]->buf->buf);
    if(var != NULL){
        (data)->error_status = ERR_SEMANTIC_OTHER;
        return -1;
    }

    int i = index;
    // skip assign token
    while((data)->buffer.token[i]->type != TYPE_ASSIGN){
        i++;
    }
    i++;
    int rightType;
    //check wether there is function call on the right side of assignment
    if((data)->buffer.token[i]->type == TYPE_FUNCTION_ID){
        
        rightType = check_function_call(data, i, &i);;
        rightType = keywordToType(rightType);
    } else {
    

    // now i is index of first token of expression
    int endingIndex = 0; // here doesnt matter
    // i is set  to ending index, to follow order of tokens
    rightType = sem_check_expression(data, i, TYPE_SEMICOLON, TYPE_SEMICOLON, &i);
    if(rightType == -1){
        return -1;
    }
    }
    
    // check variable type
    if(nullSupport == 0){
        if(rightType == expectedType){
            if(insert(&(data->used_var), (data)->buffer.token[index]->buf->buf, "0", rightType) != 0){
                (data)->error_status = ERR_INTERNAL;
                return -1;
            }
        }
        else {
            (data)->error_status = ERR_SEMANTIC_OTHER;
            return -1;
        }
    } else {
        if(rightType == expectedType || rightType == KEYWORD_NULL){
            if(insert(&(data->used_var), (data)->buffer.token[index]->buf->buf, "0", rightType) != 0){
                (data)->error_status = ERR_INTERNAL;
                return -1;
            }
        }
        else {
            (data)->error_status = ERR_SEMANTIC_OTHER;
            return -1;
        }
    } 
    
    *endIndex = i;
    return 0;
}

//return 1 if assignment else 0; checks if there is =
int decide_expr_or_assignment(Syntactic_data_ptr data, int index){
    int i = index;
    int type = (data)->buffer.token[i]->type;
    while((data)->buffer.token[i]->type != TYPE_SEMICOLON || (data)->buffer.token[i]->type != TYPE_BRACE_RIGHT){
        if(type == TYPE_ASSIGN){
            return 1;
        }
        i++;
        type = (data)->buffer.token[i]->type;
    }
    return 0;
}

/**
 * Function checks one command - line of code or if, while.
 * It is used mainly to check nested commands
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param index Pointer to table where is the item we are searching for
 * @param endIndex index to last token of checked tokens
 * @param fromFunction integer if == 1 this function checks function boddy
 * @param name string name of function for inserting parameters
 * @param missingReturn check wether function has return
 * @return Returns 0 if type is ok, otherwise -1
 */
int process_one_command(Syntactic_data_ptr data, int index, int *endIndex, int fromFunction, char *name, int *missingReturn){
    
   PItemPtr function = NULL;
   if(data->used_var == data->local_var){
        
        data->used_var = data->local_var;
    } else if(data->used_var == data->main_var){
        
        data->used_var = data->main_var;
    }
    
    // determine type of command
    switch((data)->buffer.token[index]->type){
        case KEYWORD_INT:
                
                if(decide_expr_or_assignment(data, index) == 1){
                    // index + 1 -> points to variable name 
                      if(var_declaration(data, index + 1, TYPE_INTEGER, 0, endIndex, fromFunction) == -1){
                        return -1;
                      }
                      
                }
            break;
        case KEYWORD_INT_Q:
                if(decide_expr_or_assignment(data, index) == 1){
                    if(var_declaration(data, index + 1, TYPE_INTEGER, 1, endIndex, fromFunction) == -1){
                        return -1;
                    }
                }
            break;
        case KEYWORD_FLOAT:
                if(decide_expr_or_assignment(data, index) == 1){
                    // index + 1 -> points to variable name 
                      if(var_declaration(data, index + 1, TYPE_FLOAT, 0, endIndex, fromFunction) == -1){
                        return -1;
                      }
                }
            break;
        case KEYWORD_FLOAT_Q:
                if(decide_expr_or_assignment(data, index) == 1){
                    if(var_declaration(data, index + 1, TYPE_FLOAT, 1, endIndex, fromFunction) == -1){
                        return -1;
                    }
                }
            break;
        case KEYWORD_STRING:
                if(decide_expr_or_assignment(data, index) == 1){
                    // index + 1 -> points to variable name 
                      if(var_declaration(data, index + 1, TYPE_STRING, 0, endIndex, fromFunction) == -1){
                        return -1;
                      }
                }
            break;
        case KEYWORD_STRING_Q:
                if(decide_expr_or_assignment(data, index) == 1){
                    if(var_declaration(data, index + 1, TYPE_STRING, 1, endIndex, fromFunction) == -1){
                        return -1;
                    }
                }
            break;
        case KEYWORD_IF:
            sem_check_if(data, index, endIndex, fromFunction);
            break;
        case KEYWORD_WHILE:
            sem_check_while(data, index, endIndex, fromFunction);
            break;
        case TYPE_VARIABLE_ID:
                if(decide_expr_or_assignment(data, index) == 1){
                    
                    ItemPtr var = name_search(&((data)->used_var), (data)->buffer.token[index]->buf->buf);
                    if(var == NULL){
                        int rightType = sem_check_expression(data, index + 2, TYPE_SEMICOLON, TYPE_SEMICOLON, &index);
                        if(insert(&((data)->used_var), name, "0", rightType) != 0){
                            return -1;
                        }
                        *endIndex = index;

                    } else {
                        int rightType;
                        if((data)->buffer.token[index+2]->type == TYPE_FUNCTION_ID){
                            rightType = check_function_call(data, index+2, endIndex);
                            if(data->error_status != 0) {
                                return -1;
                            }
                        } else{
                            int rightType = sem_check_expression(data, index + 2, TYPE_SEMICOLON, TYPE_SEMICOLON, endIndex);
                            if (var->type != rightType) {
                                var->type = rightType;
                            }
                        }
                        
                    }
                    
                }
            break;
        // these 3 cases can't cause semantic error
        case TYPE_INTEGER:
            break;
        case TYPE_FLOAT:
            break;
        case TYPE_STRING:
            break;
        case TYPE_SEMICOLON:
            index++;
            *endIndex = index;
            break;
        case TYPE_BRACE_LEFT:
            index++;
            *endIndex = index;
            break;
        case KEYWORD_RETURN:
            if(fromFunction){
                index++;
                PItemPtr fun = name_psearch(&(data->function_var), name);
                int returnType = fun->type;
                returnType = keywordToType(returnType);
                int gotType = sem_check_expression(data, index, TYPE_SEMICOLON, TYPE_SEMICOLON, &index);
                
                if(returnType != KEYWORD_VOID){
                    if(returnType != gotType){
                        data->error_status = ERR_SEMANTIC_RETURN;
                        return -1;
                    }
                }
                *missingReturn = 0;
                *endIndex = index;
            }
            break;
        case TYPE_FUNCTION_ID:
            check_function_call(data, index, endIndex);
            if(data->error_status != 0) {
                return -1;
            }
            break;
        
        default:
            
            return -1;
            break;
    }
    return 0;
}

/**
 * Function checks one command - line of code or if, while.
 * It is used mainly to check nested commands
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param index Pointer to table where is the item we are searching for
 * @param endIndex index to last token of checked tokens
 * @param fromFunction integer if == 1 this function checks function boddy
 * @param name string name of function for inserting parameters
 * @param missingReturn check wether function has return
 * @return Returns 0 if type is ok, otherwise -1
 */
int process_block(Syntactic_data_ptr data, int index, int *endIndex, int fromFunction, char *name, int *missingReturn){
    int localIndex = index;
    int type = 0;
    int tokenType = (data)->buffer.token[index]->type;
    // if right brace it means empty block
    if(tokenType == TYPE_BRACE_RIGHT){
        *endIndex = index+1;
    }
    while(tokenType != TYPE_BRACE_RIGHT){
        type = process_one_command(data, localIndex, endIndex, fromFunction, name, missingReturn);
        if(type == -1){
            
            return -1;
        }
        localIndex = *endIndex;
        tokenType = (data)->buffer.token[localIndex]->type;
    } 
    return 0;
}

/**
 * Function checks whether argument of the function is alright 
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param indexInBuffer type of the argument of the function we are now checking
 * @param pitem pointer to table with parameters
 * @return void
 */
void sem_check_argument(Syntactic_data_ptr data, int indexInBuffer, PItemPtr pitem){
    // chceck wheter the variable exists in symtable
    char *var_name =  (data)->buffer.token[indexInBuffer]->buf->buf;
    ItemPtr argument = name_search(&(data)->used_var, var_name);
    if(argument == NULL){
        (data)->error_status = ERR_SEMANTIC_DEF_VAR;
        return -1;
    }
    // check whether type of variable is the same as required parameter type
    if(pitem->paramType != argument->type) {
        (data)->error_status =  ERR_SEMANTIC_ARG_FCE;
        return -1;
    }
}

/**
 * Function checks whether argument of the function is alright 
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param start index to starting index
 * @param endIndex pointer to propagate last check token position
 * @return Returns 0 if type is ok, otherwise -1
 */
int sem_check_arguments(Syntactic_data_ptr data, int start, int *endIndex){
    int i = start;
    int param = -1;
    // find function name
    int type = data->buffer.token[i]->type; 
    if(strcmp(data->buffer.token[i]->buf->buf, "php") == 0) {
        *endIndex = i+1;
        return -1;
    }
    // find function in symtable
    PItemPtr pitem = name_psearch(&((data)->function_var), (data)->buffer.token[i]->buf->buf);
    if(pitem == NULL){
        // function doesn't exist
        data->error_status = ERR_SEMANTIC_DEF_FCE;
        return -1;
    }
    int returnType = pitem->type;
    // handle built in functions with non standard number of params
    // -2 function has 0 params, expects only ()
    if(pitem->paramType == -2){
        i += 2; // skip ()
        *endIndex = i;
        return -1;
    //function (write) has unknown number of params
    } else if(pitem->paramType == -1) {
        
        i+=2; // skip (
        // iterate and check variable existance till token ; is found
        while(data->buffer.token[i]->type != TYPE_SEMICOLON){
            if(data->buffer.token[i]->type == TYPE_VARIABLE_ID){
                if(check_type_a_exist(data, i, &i) == -1){
                    return -1;
                }
            } else {
                i++;
            }
        }
    } else {
    // find term and store its type into termType
    int termType;
    i+=2;
    while((data)->buffer.token[i]->type != TYPE_SEMICOLON){ //TYPE_PAR_RIGHT TYPE_BRACE_RIGHT
        //evaluate expression and get termType
        termType = sem_check_expression(data, i, TYPE_COMMA, TYPE_PAR_RIGHT, &i);
        // different type than expected or too much arguments
        if(pitem == NULL){
            (data)->error_status = ERR_SEMANTIC_ARG_FCE;
            return -1;
        }
        param = keywordToType(pitem->paramType);
        if(param != termType){
            (data)->error_status = ERR_SEMANTIC_ARG_FCE;
            return -1;
        }
        pitem = getNextParam(pitem);
        i++;

    }
    // not enough arguments
    if(pitem != NULL){
        (data)->error_status = ERR_SEMANTIC_ARG_FCE;
        return -1;
    }
    }
    // store last index
    *endIndex = i;
    return returnType;
}

/**
 * Function checks one command - line of code or if, while.
 * It is used mainly to check nested commands
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param endIndex index to last token of checked tokens=
 * @return Returns void
 */
void process_buffer_fill_ptabel(Syntactic_data_ptr data, int *endIndex){
    int i = 0; // start
    //get buffer size
    int len = (data)->buffer.length;
    // find and store name of function
    char *funName = NULL;
    while(i < len && (data->buffer.token[i]->type != TYPE_FUNCTION_ID)){
        i++;
    }
    funName = data->buffer.token[i]->buf->buf;
    // check whether the function was defined
    if(name_psearch(&(data->function_var),funName) != NULL){
        // redefined function
        data->error_status = ERR_SEMANTIC_DEF_FCE;
        return;
    }
    // find and store return type of function
    int j = i;
    while(data->buffer.token[j]->type != TYPE_PAR_RIGHT){
        j++;
    }
    j++;
    int returnType = data->buffer.token[j]->type;
    // insert params
    i++;
    while(data->buffer.token[i]->type != TYPE_PAR_RIGHT){
            //check variables
            if(data->buffer.token[i]->type == TYPE_VARIABLE_ID){
                // insert param to ptable
                pinsert(&(data->function_var), funName, data->buffer.token[i]->buf->buf, returnType, data->buffer.token[i]->type);
            }
        
        i++;
    }
    // store last index to endIndex and propagate higher
    *endIndex = i; 
}

/**
 * Function checks whether function is declared properly
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param startIndex index of first token to be checked
 * @param endIndex index to last token of checked tokens=
 * @return Returns void
 */
void sem_check_function_definition(Syntactic_data_ptr data, int startIndex, int *endIndex){
    
    // get first
    int i = startIndex;
   
    // process body  
    // skip to function body
    
    // get name of function
    char *name = data->buffer.token[i+1]->buf->buf;

    //find function by name
    PItemPtr fun = name_psearch(&(data->function_var), name);
    
    // if normal function with solid number of params
    if(fun->paramType != -2 && fun->paramType != -1){
        
        while(data->buffer.token[i]->type != TYPE_PAR_RIGHT){
            if(data->buffer.token[i]->type == TYPE_VARIABLE_ID){
                if(name_search(&(data->used_var), (data)->buffer.token[i]->buf->buf) != NULL){
                    data->error_status = ERR_SEMANTIC_OTHER;
                    return;
                }
                if(insert(&(data->used_var), (data)->buffer.token[i]->buf->buf, "0", (data)->buffer.token[i-1]->type) != 0) {
                    data->error_status = ERR_INTERNAL;
                    return;
                }
            }
            //increment index
            i++;
        }
    }   
    
    int returnType = fun->type;
    int missingReturn;
    // when function needs return keyword inform caller funciton
    if(returnType == KEYWORD_VOID){
        missingReturn = 0;
    } else {
        missingReturn = 1; 
    }
    
    // calling from function
    int fromFunction = 1;
    while(data->buffer.token[i]->type != TYPE_BRACE_LEFT){
        i++;
    }
    
    //check body of function
    process_block(data, i+1, &i, fromFunction, name, &missingReturn);
    *endIndex = i;
    if(missingReturn == 1){
        data->error_status = ERR_SEMANTIC_RETURN;                   
    }
}

/**
 * Function calls functions to check function call
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param startIndex index of first token to be checked
 * @param endIndex index to last token of checked tokens=
 * @return Returns error if occure
 */
int check_function_call(Syntactic_data_ptr data, int start, int *endIndex){
    
    return sem_check_arguments(data, start, endIndex);
    
}

/**
 * Function checks function params, variable existance 
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param bufferIndex index of first token to be checked
 * @param endIndex index to last token of checked tokens=
 * @return Returns -1 if error or variable type
 */ 
int check_type_a_exist(Syntactic_data_ptr data, int bufferIndex, int *endIndex){
    
    // get first token type
    int type = (data)->buffer.token[bufferIndex]->type;
   
    ItemPtr variable = NULL;
    PItemPtr function = NULL;

   
    switch(type){ // vyrazy a bez operatoru
            case TYPE_VARIABLE_ID:
                *endIndex = bufferIndex + 1;
                // save var type
                variable = name_search(&(data->used_var), (data)->buffer.token[bufferIndex]->buf->buf);
                if(variable == NULL){
                    (data)->error_status = ERR_SEMANTIC_DEF_VAR;
                    return -1;
                } else {
                    return variable->type;
                }
                break;
            case TYPE_FUNCTION_ID:
                *endIndex = bufferIndex + 1;
                // save fun return type
                function = name_psearch(&((data)->function_var), (data)->buffer.token[bufferIndex]->buf->buf);
                if(function == NULL){
                    (data)->error_status = ERR_SEMANTIC_DEF_FCE;
                    return -1;
                }else {
                    if(function->type == KEYWORD_VOID){
                        return KEYWORD_NULL;
                    }
                    return function->type;
                }

                break;
            // just increment last index variable
            case TYPE_INTEGER:
                *endIndex = bufferIndex + 1;
                return TYPE_INTEGER;
                break;

            case TYPE_FLOAT:
                *endIndex = bufferIndex + 1;
                return TYPE_FLOAT;
                break;

            case TYPE_STRING:
                *endIndex = bufferIndex + 1;
                return TYPE_STRING;
                break;

            case KEYWORD_NULL:
                *endIndex = bufferIndex + 1;
                return KEYWORD_NULL;
                break;

            case TYPE_BRACE_LEFT:
                //recursive way of handling () in expression
                if(sem_check_expression(data, bufferIndex, TYPE_BRACE_RIGHT, TYPE_BRACE_RIGHT, endIndex)  == -1){
                    return -1;
                }
                break;

            case TYPE_PAR_LEFT:
                //recursive way of handling () in expression
                return sem_check_expression(data, bufferIndex+1, TYPE_PAR_RIGHT, TYPE_PAR_RIGHT, endIndex);
                break;

            default:
                return -1;
                break;
    }
    return 0;
}

/**
 * Function checks condition of if and while
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param bufferIndex index to starting index
 * @param endInd pointer to propagate last check token position
 * @param fromFunctioninteger if == 1 this function checks function boddy
 * @return Returns 1 if we dont know the output, 0 if the result will be false
 */
int sem_check_condition(Syntactic_data_ptr data, int bufferIndex, int *endInd, int fromFunction){
    // determine < > === !==  token position and existance
    int index = bufferIndex;
    int typeData = data->buffer.token[index]->type;
    while(typeData != TYPE_BRACE_LEFT){
        if(typeData == TYPE_VARIABLE_ID){
            int variable = name_search(&(data->used_var), (data)->buffer.token[index]->buf->buf);
            if(variable == NULL){
                (data)->error_status = ERR_SEMANTIC_DEF_VAR;
                return -1;
            }
        }
        
        // move to next token
        index++;
        typeData = data->buffer.token[index]->type;
    }

    // save last index
    *endInd = index; 
    
   return 0;
}

/**
 * Function checks if condition and both blocks
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param startIndex Pointer to table where is the item we are searching for
 * @param endIndex index to last token of checked tokens
 * @param fromFunction integer if == 1 this function checks function boddy
 * @return Returns nothing
 */
void sem_check_if(Syntactic_data_ptr data, int startIndex, int* endIndex, int fromFunction){
    int i = startIndex;
    
    //skip to (
    while(data->buffer.token[i]->type != TYPE_PAR_LEFT){
        i++;
    }
    i++;
    // now inside () of if
    if(sem_check_condition(data, i, &i, fromFunction) == -1){
        return;
    }
    i++; //skip ) and {
    int k;
    //check if block
    process_block(data, i, endIndex, fromFunction, "", &k);
    i = *endIndex; // now index at }
    i += 2; // skip else and {
    //check else block
    process_block(data, i, &i, fromFunction, "", &k);
   
    // store last token index and propagate higher
    *endIndex = i;
}

/**
 * Function checks while condition and block
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param startIndex Pointer to table where is the item we are searching for
 * @param endIndex index to last token of checked tokens
 * @param fromFunction integer if == 1 this function checks function boddy
 * @return Returns void
 */
void sem_check_while(Syntactic_data_ptr data, int startIndex, int* endIndex, int fromFunction){
    //get first index
    int i = startIndex;
    
    // skip to (
    while(data->buffer.token[i]->type != TYPE_PAR_LEFT){
        i++;
    }
    i++; // now i is index of next token after left paranethesis
    
    // check condition of while
    if(sem_check_condition(data, i, &i, fromFunction) == -1){
        // if error occures propagate higher
        return; 
    }
    i++; // move beyond the left brace
    int k;
    
    // check while lock
    process_block(data, i, endIndex, fromFunction, "", &k);
   
}


/**
 * Function used to move start index to propperly start in token buffer
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param index Pointer to table where is the item we are searching for
 * @return Returns void
 */
void skip_prolog(Syntactic_data_ptr data, long unsigned int *index) {
    
    if(data->buffer.token[*index]->type == TYPE_PROLOG_START){
       *index++;
    }

    *index = 7; // got from actual state of buffer
    return; 
}

/**
 * Function constrolling semantic checks, iterate over token buffer and propagate error
 *
 * @param data  pointer to symbol tables, way to propagate error code
 * @param index Pointer to table where is the item we are searching for
 * @return Returns 0 if everything ok
 */
int semantics_main(Syntactic_data_ptr data){
    // iterate over whole buffer and store function declarations
   if(find_functions(data) != 0 ) {
        return -1;
    }
    
    // iterate over buffer and check the rest

    // find start
    unsigned long int i = 0; 
    
    // go over whole buffer
    while(i < data->buffer.length){
        // determine what is going to be checked
        switch(data->buffer.token[i]->type){
            // set symtable
            case KEYWORD_INT:
                data->used_var = data->main_var;
                if(decide_expr_or_assignment(data, i) == 1){
                    if(var_declaration(data, i + 1, TYPE_INTEGER, 0, &i, 0) == -1){
                        return -1;
                    }
                }
                break;
            case KEYWORD_INT_Q:
                // set symtable
                data->used_var = data->main_var;
                if(decide_expr_or_assignment(data, i) == 1){
                    if(var_declaration(data, i + 1, TYPE_INTEGER, 1, &i, 0) == -1){
                        return -1;
                    }
                }
            break;
        case KEYWORD_FLOAT:
            // set symtable
            data->used_var = data->main_var;
            if(decide_expr_or_assignment(data, i) == 1){ 
                if(var_declaration(data, i + 1, TYPE_FLOAT, 0, &i, 0) == -1){
                    return -1;
                }
            }
            break;
        case KEYWORD_FLOAT_Q:
            // set symtable
            data->used_var = data->main_var;
                if(decide_expr_or_assignment(data, i) == 1){
                    if(var_declaration(data, i + 1, TYPE_FLOAT, 1, &i, 0) == -1){
                        return -1;
                    }
                }
            break;
        case KEYWORD_STRING:
            // set symtable
            data->used_var = data->main_var;
                if(decide_expr_or_assignment(data, i) == 1){
                      if(var_declaration(data, i + 1, TYPE_STRING, 0, &i, 0) == -1){
                        return -1;
                      }
                }
            break;
        case KEYWORD_STRING_Q:
            // set symtable
            data->used_var = data->main_var;
                if(decide_expr_or_assignment(data, i) == 1){
                    if(var_declaration(data, i + 1, TYPE_STRING, 1, &i, 0) == -1){
                        return -1;
                    }
                }
            break;
        case KEYWORD_IF:
           // set symtable
            data->used_var = data->main_var;
            sem_check_if(data, i, &i, 0); //0 because not called from function

            // if error propagate
            if(data->error_status != 0) return -1;
            break;
        case KEYWORD_WHILE:
            // set symtable
            data->used_var = data->main_var;
            sem_check_while(data, i, &i, 0); //0 because not called from function
            if(data->error_status != 0){
                return -1;
            }
            break;
        case TYPE_VARIABLE_ID:
            // set symtable
            data->used_var = data->main_var;
                if(decide_expr_or_assignment(data, i) == 1){
                    char *name =(data)->buffer.token[i]->buf->buf;
                    ItemPtr var = name_search(&((data)->used_var), name);
                    if(var == NULL){
                        int rightType;
                        if((data)->buffer.token[i+2]->type == TYPE_FUNCTION_ID){
                            rightType = check_function_call(data, i+2, &i);
                            if(data->error_status != 0) {
                                return -1;
                            }
                        } else {
                            rightType = sem_check_expression(data, i + 2, TYPE_SEMICOLON, TYPE_SEMICOLON, &i);
                        }
                        if(insert(&((data)->used_var), name, "0", rightType) != 0){
                                return -1;
                            } 
                    } else {
                        int rightType;
                        if((data)->buffer.token[i+2]->type == TYPE_FUNCTION_ID){
                            rightType = check_function_call(data, i+2, &i);
                            if(data->error_status != 0) {
                                return -1;
                            }
                        } else {
                            rightType = sem_check_expression(data, i + 2, TYPE_SEMICOLON, TYPE_SEMICOLON, &i);
                            if (var->type != rightType) {
                                var->type = rightType;
                            }
                        }
                        
                    }
                }
            break;
        // these 3 cases shoulden't cause semantic error
        case TYPE_INTEGER:
            data->used_var = data->main_var;
            if(sem_check_expression(data, i, TYPE_SEMICOLON, TYPE_SEMICOLON, &i) == -1){
                return -1;
            }
            break;
        case TYPE_FLOAT:
            data->used_var = data->main_var;
            if(sem_check_expression(data, i, TYPE_SEMICOLON, TYPE_SEMICOLON, &i) == -1){
                return -1;
            }
            break;
        case TYPE_STRING:
            data->used_var = data->main_var;
            if(sem_check_expression(data, i, TYPE_SEMICOLON, TYPE_SEMICOLON, &i) == -1){
                return -1;
            }
            break;   
        case TYPE_FUNCTION_ID:
            data->used_var = data->main_var;
            check_function_call(data, i, &i);
            if(data->error_status != 0) {
                return -1;
            }
            break;
        case KEYWORD_FUNCTION:
            // create local symtable for current functiont, set symtable
            if(create_table(TABLE_SIZE, &(data->local_var)) == ERR_INTERNAL) {
                data->error_status = ERR_INTERNAL;
            } else {
                data->used_var = data->local_var;
            }
        
            sem_check_function_definition(data, i, &i);
            
            if(data->error_status != 0){
                return -1;
            }
            //free_table(data->local_var);
            data->used_var = data->main_var;
            break;

        default:
            i++; // skip semicolon
            
            break; 
        }
    }    

return 0;
}

/**
 * Function checks function head
 * @param data  pointer to symbol tables, way to propagate error code
 * @param startIndex index of first token to be checked
 * @param endIndex index to last token of checked tokens=
 * @return Returns -1 if error occures
 */
int process_function_head(Syntactic_data_ptr data, int startIndex, int *endIndex){
    int i = startIndex + 1; // now points at name of function
    // store name of function
    char *funName = data->buffer.token[i]->buf->buf;
    // check whether the function was defined
    if(name_psearch(&(data->function_var), funName) != NULL){
        // redefined function
        data->error_status = ERR_SEMANTIC_DEF_FCE;
        return -1;
    }
    // find and store return type of function
    int j = i;
    while(data->buffer.token[j]->type != TYPE_PAR_RIGHT){
        j++;
    }
    j+=2;
    int returnType = data->buffer.token[j]->type;
    // insert params
    i+=2;
    
    // if function has 0 params
    if(data->buffer.token[i]->type == TYPE_PAR_RIGHT){
        char *value = (char*) malloc(sizeof(char) * 2);
        if(value == NULL) {
            data->error_status = ERR_INTERNAL;
            return -1;
        }
        strcpy(value, "5");
        pinsert(&(data->function_var), funName, value, returnType, -1);
        *endIndex = i; 
        return 0;
    } else {
        i--;
    }
    // iterate over params
    while(data->buffer.token[i]->type != TYPE_PAR_RIGHT){
            // insert variable
            if(data->buffer.token[i]->type == TYPE_VARIABLE_ID){
                // insert param to ptable
                if(pinsert(&(data->function_var), funName, data->buffer.token[i]->buf->buf, returnType, data->buffer.token[i-1]->type) != 0) {
                    return -1;
                }
                PItemPtr p = name_psearch(&(data->function_var), funName);
            }
        i++;
    }
    *endIndex = i; 
    return 0;
}


/**
 * Function finds functions in token buffer and calls process_function_head to check them 
 * @param data  pointer to symbol tables, way to propagate error code
 * @return Returns -1 if error occures
 */
int find_functions(Syntactic_data_ptr data){
    int i = 0;
    int end = data->buffer.length;
    while(i != end){
        if(data->buffer.token[i]->type == KEYWORD_FUNCTION){
            if( process_function_head(data, i, &i) != 0 ){
                return -1;
            }
        } else {
            i++;
        }
    }
    // all functions found and checked
    return 0;
}
