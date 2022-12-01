/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of semantics.
    *
    * @author Martin Tomašovič <xtomas36@stud.fit.vutbr.cz>
    */


/*/
#define INT "int"
#define INT_Q "intq"
#define FLOAT "float"
#define FLOAT_Q "floatq"
#define STR "String"
#define STR_Q "Stringq" */

#include "semantics.h"
#include "symtable.h"

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
 *//*
int check_int_Q(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_INTEGER_Q) != NULL){ //KEYWORD_INT_Q
        return 0;
    } else {
        return ERR_SEMANTIC_TYPE;;
    }
}
*/
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
 *//*
int check_float_Q(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_FLOAT_Q) != NULL){
        return 0;
    } else {
        return ERR_SEMANTIC_TYPE;
    }
}*/

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
 *//*
int check_String_Q(char *key, Hash_table_ptr *p_table){
    if(search(p_table, key, TYPE_STRING_Q) != NULL){
        return 0;
    } else {
        return ERR_SEMANTIC_TYPE;
    }
}*/

/**
 * Function checks whether variable of given name exists
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @param pp_table Pointer to parameter table where is the item we are searching for
 * @return Returns true if type is ok, otherwise false
 *//*
int check_var_existence(char *key, Hash_table_ptr *p_table, PHash_table_ptr *pp_table){

    if(name_search(p_table, key) != NULL){
        return 0;
    } else{
        return ERR_SEMANTIC_DEF_VAR;
    }
}
*/

/**
 * Function checks whether there is a function with the same name and return type
 *
 * @param key Identifier
 * @param p_table Pointer to table where is the item we are searching for
 * @param type return type of the function we are now checking
 * @param p_item returns pointer to the memory place where first parameter is stored through parameter
 * @return Returns whether this check succeeded or not 
 *//*
int sem_check_return(PHash_table_ptr *p_table, char *key, int type, PItemPtr *p_item){
    if(psearch(p_table, key, type) != NULL) { 
        return 0;
    } else {
        return ERR_SEMANTIC_DEF_FCE;
    }
}*/
/*
void check_return_type(Syntactic_data_ptr *data){
    
    // find return 
    if((*data)->)

    if((strcmp( buffer_get_keyword, "KEYWORD_INT_Q" ) == 0) && ((what_i_get == TYPE_STRING) || (what_i_get == TYPE_NULL))){ // TODO how to recognize NULL value
 
    }

    else {
        (*data)->error_status = ERR_SEMANTIC_ARG_FCE
    }
}
*/

/**
 * Function evaluates token type and calls check_type_a_exist function
 * to check it if the token was variable or function  whether they were declared
 *
 * @param data Used to access token
 * @param startINdex where control starts
 * @param endingType where to stop expression control
 * @param endIndex to move index variable when called recursively used to handle (5+(5*9)) type of problem
 * @return Teturns type of result of the expression or internal error -1 to propagate higher
 */

int sem_check_expression(Syntactic_data_ptr data, int startIndex, int endingType, int *endIndex){
   // printf("Checking expression");
    int i = startIndex;
    printf("\nIndex before %d     ", i);
    printf("\n Type in check_expression %d", (data)->buffer.token[i]->type);

    int currentType = check_type_a_exist(data, i, &i);
    
    printf("After type a exist, i = %d", i);
    
    int resultType = currentType;

    if(currentType == -1) {
        //(*data)->error_status = ERR_SEMANTIC_OTHER;
        return -1;
    }
   
    /*if(currentType == TYPE_INTEGER || currentType == TYPE_FLOAT || currentType == TYPE_STRING){
            resultType = currentType;
            prevType = currentType;
            i++;
    } 
    else {
        (*data)->error_status = ERR_SEMANTIC_OTHERS;
    }
    // number of expected left parenthesis to check "if(5+(8*9))""
    int leftParenthesis = 0;
    if(currentType == leftParenthesis){
        leftParenthesis += 1;
    } */

    //currentType = check_type_a_exist(data, i, &i);

    printf("current: %d, ending: %d", currentType, endingType);

    while(currentType != endingType){ //&& leftParenthesis == 0
        /*if(currentType == TYPE_PAR_RIGHT ){
            leftParenthesis++;
            i++;
        } 
        else if(currentType == TYPE_PAR_LEFT){
            leftParenthesis--;
            i++;
        }
        else*/
        if(currentType == TYPE_PLUS || currentType == TYPE_MINUS || currentType == TYPE_MUL) {
            int nextTokType = check_type_a_exist(data, i+1, &i);//(*data)->buffer.token[i+1]->type;
            if(nextTokType == -1) { //if(check_type_a_exist(data, i+1, &i) == -1) { 
                //(*data)->error_status = ERR_SEMANTIC_OTHER;
                return -1;
            }
            //check_type_a_exist(data, i+1, &i); // recursive function call, set index i through parameter
            if((nextTokType == TYPE_INTEGER || nextTokType == TYPE_VARIABLE_ID || nextTokType == TYPE_FUNCTION_ID) && (resultType == TYPE_INTEGER || resultType == KEYWORD_NULL) ){
                resultType = TYPE_INTEGER;
            } else {
                if(nextTokType == TYPE_FLOAT && ((resultType == TYPE_INTEGER || resultType == KEYWORD_NULL))) {
                    resultType = TYPE_FLOAT;
                }
            }
            
            //i += 2;

        } else if(currentType == TYPE_DIV){
            //int nextTokType = (*data)->buffer.token[i+1]->type;
            resultType = TYPE_FLOAT;
            if(check_type_a_exist(data, i+1, &i) == -1) { 
                //(*data)->error_status = ERR_SEMANTIC_OTHER;
                return -1;
            }
            //i += 2;

        } else if(currentType == TYPE_COLON){
            int nextTokType = check_type_a_exist(data, i+1, &i);//(*data)->buffer.token[i+1]->type;
            if(nextTokType == TYPE_STRING || nextTokType == TYPE_VARIABLE_ID || nextTokType == TYPE_FUNCTION_ID){
                if(nextTokType == -1){//if(check_type_a_exist(data, i+1, &i) == -1) { 
                //(*data)->error_status = ERR_SEMANTIC_OTHER;
                    return -1;
                }
                //i += 2;
                resultType = TYPE_STRING;
            } else {
                (data)->error_status = ERR_SEMANTIC_TYPE;
                return -1;
            }
        }
        
        currentType = (data)->buffer.token[i]->type;
    }
    *endIndex = i; 
    printf("returned");
    return resultType;
}

int assertion(Syntactic_data_ptr *data, int index){
    printf("Checking assertion");
    ItemPtr var = name_search(&((*data)->used_var), (*data)->buffer.token[index]->buf->buf);
        if(var != NULL){
        (*data)->error_status = ERR_SEMANTIC_DEF_VAR;
        return -1;
    }
    int varType = var->type;
    printf("\nIn assertion type of var is %d\n", varType);
    int i = index;
    while((*data)->buffer.token[i]->type != TYPE_ASSIGN){
        i++;
    }
    i++;
    // now i is index of first token of expression;
    int endingIndex = 0; // here doesnt matter
    //printf("Assertion here");
    int rightType = sem_check_expression(*data, i, TYPE_SEMICOLON, &endingIndex);
    if(rightType == -1){
        return -1;
    }
    printf("\nleft = %d, right = %d\n",varType, rightType);
    // change type of variable in symtable if different
    if(varType != rightType){
        if(insert(&((*data)->used_var), var->key, var->value, rightType) != 0){
            return -1;
        }
    }
    return 0;
}

int var_declaration(Syntactic_data_ptr *data, int index, int expectedType, int nullSupport){
    printf("Var declaration var name %s \n", (*data)->buffer.token[index]->buf->buf);
    ItemPtr var = name_search(&((*data)->used_var), (*data)->buffer.token[index]->buf->buf);
    if(var != NULL){
        (*data)->error_status = ERR_SEMANTIC_OTHER;
        return -1;
    }

    int i = index;

    while((*data)->buffer.token[i]->type != TYPE_ASSIGN){
        i++;
    }
    i++;
    printf("\n %d type: %d", i, (*data)->buffer.token[i]->type);
    // now i is index of first token of expression
    int endingIndex = 0; // here doesnt matter
    int rightType = sem_check_expression(*data, i, TYPE_SEMICOLON, &endingIndex);
    if(rightType == -1){
        return -1;
    }
    printf("\n\nchecked \n expected: %d, got: %d\n", expectedType, rightType);

    // check variable type
    if(nullSupport == 0){
        if(rightType == expectedType){
            if(insert(&((*data)->used_var), (*data)->buffer.token[index]->buf->buf, "0", rightType) != 0){
                (*data)->error_status = ERR_INTERNAL;
                return -1;
            }
        }
        else {
            (*data)->error_status = ERR_SEMANTIC_OTHER;
            return -1;
        }
    } else {
        if(rightType == expectedType || rightType == KEYWORD_NULL){
            if(insert(&((*data)->used_var), (*data)->buffer.token[index]->buf->buf, "0", rightType) != 0){
                (*data)->error_status = ERR_INTERNAL;
                return -1;
            }
        }
        else {
            (*data)->error_status = ERR_SEMANTIC_OTHER;
            return -1;
        }
    } 
    printf("inserted");
    return 0;
}

//return 1 if assignment else 0; checks if there is =
int decide_expr_or_assignment(Syntactic_data_ptr *data, int index){
    int i = index;
    int type = (*data)->buffer.token[i]->type;
    while((*data)->buffer.token[i]->type != TYPE_SEMICOLON || (*data)->buffer.token[i]->type != TYPE_BRACE_RIGHT){
        if(type == TYPE_ASSIGN){
            return 1;
        }
        i++;
        type = (*data)->buffer.token[i]->type;
    }
    return 0;
}

int process_one_command(Syntactic_data_ptr *data, int index, int *endIndex){
    printf("Type: %d", (*data)->buffer.token[index]->type);
    switch((*data)->buffer.token[index]->type){
        case KEYWORD_INT:
                if(decide_expr_or_assignment(data, index) == 1){
                    // index + 1 -> points to variable name 
                      if(var_declaration(data, index + 1, TYPE_INTEGER, 0) == -1){
                        return -1;
                      }
                      printf("Command processed");
                }
            break;
        case KEYWORD_INT_Q:
                if(decide_expr_or_assignment(data, index) == 1){
                    if(var_declaration(data, index + 1, TYPE_INTEGER, 1) == -1){
                        return -1;
                    }
                }
            break;
        case KEYWORD_FLOAT:
                if(decide_expr_or_assignment(data, index) == 1){
                    // index + 1 -> points to variable name 
                      if(var_declaration(data, index + 1, TYPE_FLOAT, 0) == -1){
                        return -1;
                      }
                }
            break;
        case KEYWORD_FLOAT_Q:
                if(decide_expr_or_assignment(data, index) == 1){
                    if(var_declaration(data, index + 1, TYPE_FLOAT, 1) == -1){
                        return -1;
                    }
                }
            break;
        case KEYWORD_STRING:
                if(decide_expr_or_assignment(data, index) == 1){
                    // index + 1 -> points to variable name 
                      if(var_declaration(data, index + 1, TYPE_STRING, 0) == -1){
                        return -1;
                      }
                }
            break;
        case KEYWORD_STRING_Q:
                if(decide_expr_or_assignment(data, index) == 1){
                    if(var_declaration(data, index + 1, TYPE_STRING, 1) == -1){
                        return -1;
                    }
                }
            break;
        case KEYWORD_IF:
            sem_check_if(data, index, endIndex);
            break;
        case KEYWORD_WHILE:
            sem_check_while(data, index, endIndex);
            break;
        case TYPE_VARIABLE_ID:
                if(decide_expr_or_assignment(data, index) == 1){
                    ItemPtr var = name_search(&((*data)->local_var), (*data)->buffer.token[index]->buf->buf);
                    if(var_declaration(data, index + 1, var->type, 1) == -1){
                        return -1;
                    }
                }
            break;
        // these 3 cases shoulden't cause semantic error
        case TYPE_INTEGER:
            break;
        case TYPE_FLOAT:
            break;
        case TYPE_STRING:
            break;
        default:
            return -1;
            break;
        // this case should't happen syntactic error    
        /*case TYPE_FUNCTION_ID:
            if(decide_expr_or_assignment(data, index) == 1){
                    if(var_declaration(data, index + 1, TYPE_STRING, 1) == -1){
                        return -1;
                    }
                }
            break;*/
    }
    return 0;
}

int process_block(Syntactic_data_ptr *data, int index, int *endIndex){
    int localIndex = index;
    int type = 0;
    int tokenType = (*data)->buffer.token[index]->type;
    while(tokenType != TYPE_BRACE_RIGHT){
        printf("Calling process one command");
        type = process_one_command(data, localIndex, endIndex);
        if(type == -1){
            printf("error");
            return -1;
        }
        tokenType = (*data)->buffer.token[localIndex]->type;
    } 
    //switch()
    return 0;
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
void sem_check_argument(Syntactic_data_ptr *data, int indexInBuffer, PItemPtr pitem){
    //PItem name_search((*data)->used_var;
    // chceck wheter the variable exists in symtable
    char *var_name =  (*data)->buffer.token[indexInBuffer]->buf->buf;
    ItemPtr argument = name_search(&(*data)->used_var, var_name);
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

void sem_check_arguments(Syntactic_data_ptr data, int start, int *endIndex){
    int i = start;
    printf("In sem check args, %d", i);
    printf("\n in check arguments %d\n", data->buffer.token[0]->type);
    // find function name
    int type = data->buffer.token[i]->type; 
    printf("Type : %d", type);
    while(type != TYPE_FUNCTION_ID){
        printf("\ntype : %d", data->buffer.token[i]->type);
        i++;
        type = (data)->buffer.token[i]->type;
    }
    printf("\nHere");
    PItemPtr pitem = name_psearch(&((data)->function_var), (data)->buffer.token[i]->buf->buf);
    if(pitem == NULL){
        data->error_status = ERR_SEMANTIC_DEF_FCE;
        return;
    }
    // handle built in functions with non standard numberr of params
    if(pitem->paramType == -2){
        i += 2; // skip ()
        printf("\ntype : %d", data->buffer.token[i]->type);
        *endIndex = i;
        printf("Out");
        return;
    } else if(pitem->paramType == -1) {
        printf("got to write");
        i++; // skip (
        int leftParCount = 1;
        int type = data->buffer.token[i]->type;
        while(leftParCount > 0 && type != TYPE_PAR_RIGHT){
            i++;
            type = data->buffer.token[i]->type;
            if(type == TYPE_PAR_RIGHT){
                leftParCount--;
            } else if (type == TYPE_PAR_LEFT){
                leftParCount++;
            }
        }
    }
    /*while((data)->buffer.token[i]->type != TYPE_BRACE_LEFT){
        i++;
    }*/
    i++;
    while((data)->buffer.token[i]->type != TYPE_BRACE_RIGHT){
        if((data)->buffer.token[i]->type == TYPE_VARIABLE_ID){
            // too much arguments
            if(pitem == NULL){
                (data)->error_status = ERR_SEMANTIC_ARG_FCE;
                return;
            }
            // check var existance and type
            sem_check_argument(&data, i, pitem);
            pitem = getNextParam(pitem);
        } else {
            switch((data)->buffer.token[i]->type){
                // if comma nothing to do
                case TYPE_COMMA:
                    break;
                // compare constant type with parameter type and move pitem to next parameter
                case TYPE_INTEGER:
                    if(pitem->paramType != TYPE_INTEGER){
                        (data)->error_status = ERR_SEMANTIC_ARG_FCE;
                        return;
                    }
                     pitem = getNextParam(pitem);
                    break;
                case TYPE_FLOAT:
                    pitem = getNextParam(pitem);
                    if(pitem->paramType != TYPE_FLOAT){
                        (data)->error_status = ERR_SEMANTIC_ARG_FCE;
                        return;
                    }
                    break;
                case TYPE_STRING:
                    if(pitem->paramType != TYPE_STRING){
                        (data)->error_status = ERR_SEMANTIC_ARG_FCE;
                        return;
                    }
                     pitem = getNextParam(pitem);
                    break;
                default:
                    (data)->error_status = ERR_SEMANTIC_ARG_FCE;
                        return;
                    break;
            }
        }
        i++;
    }
    // not enough arguments
    if(pitem != NULL){
        (data)->error_status = ERR_SEMANTIC_ARG_FCE;
        return;
    }
    *endIndex = i;
}
/*
void can_be_null(Syntactic_data_ptr *data, buffer){
   if(!((strcmp( buffer_get_keyword, "KEYWORD_INT_Q" ) == 0) || (strcmp( buffer_get_keyword, "KEYWORD_FLOAT_Q" ) == 0) || (strcmp( buffer_get_keyword, "KEYWORD_STRING_Q" ) == 0))){
         (*data)->error_status  = ERR_SEMANTIC_OTHER;
   }
}



check_params(){
    if(-1) {
        bez param;
    }
    else if(-2){

    }
}
*/
/*
void redefine_function(Syntactic_data_ptr *data, char* key){
    if(name_psearch((*data)->function_var, key) != NULL){   
        (*data)->error_status = ERR_SEMANTIC_DEF_FCE;
    }
}*/

void process_funBody(){ // -> process_block
    //TODO
}

void process_buffer_fill_ptabel(Syntactic_data_ptr *data, int *endIndex){
    int i = 0;
    printf("here");
    //data->buffer.token[i]->type;
    int len = (*data)->buffer.length;
    // find and store name of function
    char *funName = NULL;
    while(i < len && ((*data)->buffer.token[i]->type != TYPE_FUNCTION_ID)){
        i++;
    }
    funName = (*data)->buffer.token[i]->buf->buf;
    // check whether the function was defined
    if(name_psearch(&((*data)->function_var),funName) != NULL){
        // redefined function
        (*data)->error_status = ERR_SEMANTIC_DEF_FCE;
        return;
    }
    // find and store return type of function
    int j = i;
    while((*data)->buffer.token[j]->type != TYPE_PAR_RIGHT){
        j++;
    }
    j++;
    int returnType = (*data)->buffer.token[j]->type;
    // insert params
    i++;
    while((*data)->buffer.token[i]->type != TYPE_PAR_RIGHT){
        //if((*data)->buffer.token[i]->type != TYPE_COMMA){
            if((*data)->buffer.token[i]->type == TYPE_VARIABLE_ID){
                // insert param to ptable
                pinsert(&((*data)->function_var), funName, (*data)->buffer.token[i]->buf->buf, returnType, (*data)->buffer.token[i]->type);
            }
        //}
        
        i++;
    }
    *endIndex = i; 
}


void sem_check_function_definition(Syntactic_data_ptr *data){
    printf("function sem check");
    int i = 0;
    process_buffer_fill_ptabel(data, &i);
    if((*data)->error_status != 0){
        return;
    }
    // process body
    //process_funBody();
    
    process_block(data, i, &i);
    printf("function sem ok");
}

void check_function_call(Syntactic_data_ptr *data, int start, int *endIndex){
    printf("\n in check function call %d\n", (*data)->buffer.token[0]->type);
    sem_check_arguments(*data, start, endIndex);
    printf("Out of Sem");
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
// returns -1 if error
int check_type_a_exist(Syntactic_data_ptr data, int bufferIndex, int *endIndex){
    
    printf("%d", bufferIndex);
    int type = (data)->buffer.token[bufferIndex]->type;
    printf("\n%d type", type);
    //printf("\ntype : %d\n", type);
    /*for(int i = bufferIndex; i<10; i++){
        type = (*data)->buffer.token[i]->type;
        printf("\ntype : %d\n", type);
    }*/
    //printf("HERE");
    ItemPtr variable = NULL;
    PItemPtr function = NULL;

    printf("\nObsah buf %s\n",(data)->buffer.token[bufferIndex]->buf->buf);

    if(&(data->used_var) == NULL) printf("Hash table je null");

    switch(type){ // vyrazy a bez operatoru
            case TYPE_VARIABLE_ID:
                *endIndex = bufferIndex + 1;
                // save var type
                //printf("KEY name: %s", (*data)->buffer.token[bufferIndex]->buf->buf);
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
                if(&((data)->function_var) == NULL) printf("Je to NULL ");
                function = name_psearch(&((data)->function_var), (data)->buffer.token[bufferIndex]->buf->buf);
                if(function == NULL){
                    (data)->error_status = ERR_SEMANTIC_DEF_VAR;
                    return -1;
                }else {
                    if(function->type == KEYWORD_VOID){
                        return KEYWORD_NULL;
                    }
                    return function->type;
                }
                
                break;
            case TYPE_INTEGER:
                *endIndex = bufferIndex + 1;
                printf("\nreturn int endIndex: %d \n", *endIndex);
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
                if(sem_check_expression(data, bufferIndex, TYPE_BRACE_RIGHT, endIndex)  == -1){
                    return -1;
                }
                break;
            default:
                return -1;
                break;
    }
    return 0;
}

// return 1 if we dont know the output, 0 if the result will be false
int sem_check_condition(Syntactic_data_ptr *data, int bufferIndex, int *endInd){
    // determine < > === !==  token
    int relationIndex = bufferIndex;
    int relationType = (*data)->buffer.token[relationIndex]->type;
    int parenthesisCount = 0;
    int continueCycle = 1;
    printf("go to condition");
    while(continueCycle && ( relationType != TYPE_COMPARE || relationType != TYPE_COMPARE_NEG || relationType != TYPE_GREATER || relationType != TYPE_LOWER || relationType != TYPE_GREATER_EQ || relationType != TYPE_LOWER_EQ)){

        if(relationType == TYPE_PAR_RIGHT) {
            printf("In while type right par, %d", parenthesisCount);
            parenthesisCount--;
            if(parenthesisCount <= 0) {
                relationType = TYPE_PAR_RIGHT;
                continueCycle = 0;
                printf("finish cycle");
                //printf("\n%d", relationType);
            } else {
                relationIndex++;
                relationType = (*data)->buffer.token[relationIndex]->type;
            }
        } else if(relationType == TYPE_PAR_LEFT){
            relationIndex++;
            parenthesisCount++;
            relationType = (*data)->buffer.token[relationIndex]->type;
        } else {
            relationIndex++;
            relationType = (*data)->buffer.token[relationIndex]->type;
        }
        
        printf("In while");
    }
    printf("After cycle");
    // now we have relationIndex and relationType set to right values
    if(relationType == TYPE_PAR_RIGHT) {
        int endingIndex;
        printf("Go to expression");
        int type = sem_check_expression(*data, bufferIndex, relationType, &endingIndex);
        *endInd = endingIndex;
        return type;
    } else {
         printf("Two sides");
        int endingIndex; // here doesnt matter
        int leftType = sem_check_expression(*data, bufferIndex, relationType, &endingIndex);
        int rightType = sem_check_expression(*data, (relationIndex+1), TYPE_PAR_RIGHT, &endingIndex);
        if(leftType == -1 || rightType == -1){
            return -1;
        }

        /*if((*data)->buffer.token[bufferIndex]->type == TYPE_PAR_RIGHT){ // the condition looks like ()
        (*data)->error_status = ERR_SEMANTIC_OTHER;
        return;
        } else{ */
        if(leftType != rightType){
            return 0;
        } else {
            return 1;
        }
        *endInd = endingIndex;
    }    
   // }
}

// call with 0 if you call check if from syntactic
void sem_check_if(Syntactic_data_ptr *data, int startIndex, int* endIndex){
    int i = startIndex;
    //name_psearch(NULL, NULL);
    printf("In check if semantics");
    while((*data)->buffer.token[i]->type != TYPE_PAR_LEFT){
        i++;
    }
    i++;
    sem_check_condition(data, i, &i);
    printf("Started if block processing");
    process_block(data, i, endIndex);

    printf("Left if processing");
}

void sem_check_while(Syntactic_data_ptr *data, int startIndex, int* endIndex){
    int i = startIndex;
    while((*data)->buffer.token[i]->type != TYPE_PAR_LEFT){
        i++;
    }
    i++; // now i is index of next token after left paranethesis
    sem_check_condition(data, i, &i);
    i += 2; // move beyond the left brace
    process_block(data, i, endIndex);
    printf("While checked");
}

/*
if(strict_types){
    check_function_parameter_types()
    cant_change_type_of_var()
}
*/