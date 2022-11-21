/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief functions for syntactic analyse.
    *
    * @author Jiri Soukup <xsouku17@stud.fit.vutbr.cz>
    */

#include "syntactic.h"
#include "syntactic.c"
#include "scanner.c"
#include "symtable.c"
#include "scanner.h"
#include "error.h"
#include "symtable.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * @brief Program to control grammatical rules from grammar
 */

int check_data_type (Syntactic_data_ptr data);
int check_f_rest_params(Syntactic_data_ptr data);
int check_function_calling (Syntactic_data_ptr data);
int check_f_statements(Syntactic_data_ptr data);
int check_while (Syntactic_data_ptr data);
int check_assignment (Syntactic_data_ptr data);
int check_condition (Syntactic_data_ptr data);
int check_f_statement (Syntactic_data_ptr data);
int check_return_rest (Syntactic_data_ptr data);
int check_function_calling_rest_params (Syntactic_data_ptr data);



/**
 * @brief Function to control type of function
 * function check if the function is void or any others
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_type_function (Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    add_token_buffer(token, &data->buffer);
    if (token.type == KEYWORD_VOID) {
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
        if (token.type != TYPE_BRACE_LEFT) {
            return ERR_SYNTAX;
        }
        if (check_f_statements(data) != 0) {
            return ERR_SYNTAX;
        }
        return SYNTAX_OK;
    }else if(check_data_type(data) == 0){
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
        if (token.type != TYPE_BRACE_LEFT) {
            return ERR_SYNTAX;
        }
        if (check_f_statements(data) != 0) {
            return ERR_SYNTAX;
        }
        return SYNTAX_OK;
    }

}


/**
 * @brief Function to control parameters of function
 * function check if the function has any parameters
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_f_params(Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type == TYPE_PAR_RIGHT){
        return SYNTAX_OK;
    }else if(check_data_type(data) != 0){
        return ERR_SYNTAX;
    }
    token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type != TYPE_VARIABLE_ID){
        return ERR_SYNTAX;
    }
    return check_f_rest_params(data);
}


/**
 * @brief Function to control following parameters of function
 * function check if the function has more than one parameters
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_f_rest_params(Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type == TYPE_PAR_RIGHT) {
        return SYNTAX_OK;
    }else if(token.type == TYPE_COMMA){
        return SYNTAX_OK;
    }else if(check_data_type(data) != 0){
        return ERR_SYNTAX;
    }
    token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type != TYPE_VARIABLE_ID){
        return ERR_SYNTAX;
    }
    return check_f_rest_params(data);
}



/**
 * @brief Function to control statements in function
 * function checks body of function
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_f_statements (Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    while (token.type != TYPE_BRACE_RIGHT && token.type != KEYWORD_RETURN){
        if (check_f_statement(data) != 0){
            return ERR_SYNTAX;
        }
    }
    if (token.type == TYPE_BRACE_RIGHT){
        return SYNTAX_OK;
    }else if (token.type == KEYWORD_RETURN){
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
        if (token.type == TYPE_SEMICOLON){
            return SYNTAX_OK;
        }else if (token.type == TYPE_FUNCTION_ID){
            if (check_function_calling(data) != 0){
                return ERR_SYNTAX;
            }
        }else if (token.type == expression){ //todo Samuel
            if (check_expression(token, data) != 0){
                return ERR_SYNTAX;
            }
            token = Get_token(data);
            if (add_token_buffer(token, &data->buffer))
                return ERR_INTERNAL;
            if (token.type != TYPE_SEMICOLON){
                return ERR_SYNTAX;
            }
        }
    }
    return SYNTAX_OK;
}


/**
 * @brief Function to control return
 * function check if the function ends with return
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_return (Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type == KEYWORD_RETURN){
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
        if (token.type == TYPE_SEMICOLON){
            return SYNTAX_OK;
        }
    }else if(token.type == TYPE_BRACE_RIGHT){
        return SYNTAX_OK;
    }
    return ERR_SYNTAX;
}


/**
 * @brief Function to control return of main program body
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_main_return (Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type == KEYWORD_RETURN){
        return check_return_rest(data);
    } else {
        if (token.type == EOF){
            return SYNTAX_OK;
        }else if(token.type == TYPE_PROLOG_END){
            token = Get_token(data);
            if (add_token_buffer(token, &data->buffer))
                return ERR_INTERNAL;
            if (token.type == EOF){
                return SYNTAX_OK;
            }
        }
    }
    return ERR_SYNTAX;
}

/**
 * @brief Function to control return and what's after
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_return_rest (Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type == TYPE_FUNCTION_ID){
        if (check_function_calling(data) != 0){
            return ERR_SYNTAX;
        }
    }else if (token.type == expression){ //todo Samuel
        if (check_expression(token, data) != 0){
            return ERR_SYNTAX;
        }
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
        if (token.type != TYPE_SEMICOLON){
            return ERR_SYNTAX;
        }
    }
    return SYNTAX_OK;

}

/**
 * @brief Function to control statement of function
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_f_statement (Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    switch (token.type){
        case (KEYWORD_WHILE):
            if (check_while(data) != 0){
                return ERR_SYNTAX;
            }
        case (TYPE_FUNCTION_ID):
            if (check_function_calling(data) != 0){
                return ERR_SYNTAX;
            }
        case (TYPE_VARIABLE_ID):
            if (check_assignment(data) != 0){
                return ERR_SYNTAX;
            }
        case (KEYWORD_IF):
            if (check_condition(data) != 0) {
                return ERR_SYNTAX;
            }
        case (expression):
            if (check_expression(token, data) != 0) {
                return ERR_SYNTAX;
            }
    }
    return SYNTAX_OK;
}


/**
 * @brief Function to control type of data used
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_data_type (Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    switch (token.type){
        case (KEYWORD_STRING_Q || KEYWORD_INT_Q || KEYWORD_FLOAT_Q || KEYWORD_FLOAT || KEYWORD_INT || KEYWORD_STRING):{
            return SYNTAX_OK;
        }
    }
    return ERR_SYNTAX;
}


/**
 * @brief Function to control what's following after '='
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_after_equal (Syntactic_data_ptr data){
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type == TYPE_FUNCTION_ID){
        if (check_function_calling(data) != 0){
            return ERR_SYNTAX;
        }
    }else if(token.type == expression){
        if (check_expression(token, data) != 0){
            return ERR_SYNTAX;
        }
    }
    return SYNTAX_OK;
}

/**
 * @brief Function to control assignment
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_assignment(Syntactic_data_ptr data) {
    Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type != TYPE_ASSIGN) {
        return ERR_SYNTAX;
    }
    if (check_after_equal(data) != 0) {
        return ERR_SYNTAX;
    }
    token = Get_token(data);
    add_token_buffer(token, &data->buffer);
    if (token.type != TYPE_SEMICOLON) {
        return ERR_SYNTAX;
    }
    return SYNTAX_OK;
}

/**
 * @brief Function to control loop while
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
    int check_while(Syntactic_data_ptr data){

        Token_struct token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    if (token.type != TYPE_PAR_LEFT)
            return ERR_SYNTAX;
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    if (check_expression(token, data) != 0){
            return ERR_SYNTAX;
        }
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    if (token.type != TYPE_PAR_RIGHT) {
            return ERR_SYNTAX;
        }
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    if (token.type != TYPE_BRACE_LEFT) {
            return ERR_SYNTAX;
        }
        if (check_f_statements(data) != 0){
            return ERR_SYNTAX;
        }
        return SYNTAX_OK;
    }

/**
* @brief Function to control definition of function
* @param Syntactic_data_ptr
* @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
*/
    int check_function_definition(Syntactic_data_ptr data) {
        Token_struct token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    if (token.type != TYPE_FUNCTION_ID)
            return ERR_SYNTAX;

        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    if (token.type != TYPE_PAR_LEFT)
            return ERR_SYNTAX;
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    if(check_f_params(data) != 0){
            return ERR_SYNTAX;

        }
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    if (token.type != TYPE_COLON){
            return ERR_SYNTAX;
        }
        return check_type_function(data);
    }


/*
int check_main_statements (Syntactic_data_ptr data){
    token_struct token = get_next_token();
    switch (token.type){
        case (TYPE_EOF):
            return SYNTAX_OK;
        case (KEYWORD_WHILE):
            return check_while(data);
        case (TYPE_FUNCTION_ID):
            return check_function_calling(data);
        case (KEYWORD_FUNCTION):
            return check_function_definition(data);
        case (TYPE_VARIABLE_ID):
            return check_assignment(data);
        case (TYPE_VALUE):                          //ask Daniel
            return check_expression(token, data);
    }
    return ERR_SYNTAX;
}
 */


/**
 * @brief Function to control condition if
 * @param Syntactic_data_ptr
 * @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
 */
int check_condition (Syntactic_data_ptr data){
        Token_struct token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type != TYPE_PAR_LEFT){
            return ERR_SYNTAX;
        }
        token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (check_expression(token, data) != 0){
            return ERR_SYNTAX;
        }
        token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type != TYPE_PAR_RIGHT){
            return ERR_SYNTAX;
        }
    token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type != TYPE_BRACE_LEFT){
            return ERR_SYNTAX;
        }
        if (check_f_statements(data) != 0){
            return ERR_SYNTAX;
        }
    token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type != KEYWORD_ELSE){
            return ERR_SYNTAX;
        }
    token = Get_token(data);
    if (add_token_buffer(token, &data->buffer))
        return ERR_INTERNAL;
    if (token.type != TYPE_BRACE_LEFT){
            return ERR_SYNTAX;
        }
        if (check_f_statements(data) != 0){
            return ERR_SYNTAX;
        }
        return SYNTAX_OK;
    }


/**
* @brief Function to control calling of function
* @param Syntactic_data_ptr
* @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
*/
    int check_function_calling (Syntactic_data_ptr data){

        Token_struct token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    if (token.type != TYPE_PAR_LEFT){
            return ERR_SYNTAX;
        }
        token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;
    switch (token.type) {
            case (TYPE_PAR_RIGHT) :
                return SYNTAX_OK;

            case (TYPE_VARIABLE_ID):
                return check_function_calling_rest_params (data);

        }
        return ERR_SYNTAX;
    }


/**
* @brief function to control params of called function (if there is more than one)
* @param Syntactic_data_ptr
* @return ERR_SYNTAX in case of any problem or SYNTAX_OK if grammar is okay
*/
    int check_function_calling_rest_params (Syntactic_data_ptr data){
        Token_struct token = Get_token(data);
        if (add_token_buffer(token, &data->buffer))
            return ERR_INTERNAL;

    switch (token.type){
            case (TYPE_COMMA):
                token = Get_token(data);
                if (add_token_buffer(token, &data->buffer))
                    return ERR_INTERNAL;
            if (token.type != TYPE_VARIABLE_ID){
                    return ERR_SYNTAX;
                }else{

                    return check_function_calling_rest_params (data);

                }
            case (TYPE_PAR_RIGHT):
                return SYNTAX_OK;
        }
        return ERR_SYNTAX;
    }
