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

/*
 * this program controls grammar rules, which are described in grammar file
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




int check_type_function (Syntactic_data_ptr data){
/*
 * function check if the function is void or any others
 * return ERR_SYNTAX in ase of any problem or SYNTAX_OK if grammar is okay
 */
    token_struct token = get_next_token();
    if (token.type == KEYWORD_VOID) {
        token = get_next_token();
        if (token.type != TYPE_BRACE_LEFT) {
            return ERR_SYNTAX;
        }
        if (check_f_statements(data) != 0) {
            return ERR_SYNTAX;
        }
        return SYNTAX_OK;
    }else if(check_data_type(data) == 0){
        token = get_next_token();
        if (token.type != TYPE_BRACE_LEFT) {
            return ERR_SYNTAX;
        }
        if (check_f_statements(data) != 0) {
            return ERR_SYNTAX;
        }
        return SYNTAX_OK;
    }

}

int check_f_params(Syntactic_data_ptr data){
    /*
     *  check if the params of function are grammatically right
     *  return SYNTAX_OK if everything okay, in other case return ERR_SYNTAX
     */
    token_struct token = get_next_token();
    if (token.type == TYPE_PAR_RIGHT){
        return SYNTAX_OK;
    }else if(check_data_type(data) != 0){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (token.type != TYPE_VARIABLE_ID){
        return ERR_SYNTAX;
    }
    return check_f_rest_params(data);
}

int check_f_rest_params(Syntactic_data_ptr data){
    /*
     * in case of more than one params, this function is used
     * return SYNTAX_OK if everything okay, in other case return ERR_SYNTAX
     */
    token_struct token = get_next_token();
    if (token.type == TYPE_PAR_RIGHT) {
        return SYNTAX_OK;
    }else if(token.type == TYPE_COMMA){
        return SYNTAX_OK;
    }else if(check_data_type(data) != 0){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (token.type != TYPE_VARIABLE_ID){
        return ERR_SYNTAX;
    }
    return check_f_rest_params(data);
}


int check_f_statements (Syntactic_data_ptr data){
    /*
     * function to control body of function
     * return SYNTAX_OK if everything okay, in other case return ERR_SYNTAX
     */
    token_struct token = get_next_token();
    while (token.type != TYPE_BRACE_RIGHT && token.type != KEYWORD_RETURN){
        if (check_f_statement(data) != 0){
            return ERR_SYNTAX;
        }
    }
    if (token.type == TYPE_BRACE_RIGHT){
        return SYNTAX_OK;
    }else if (token.type == KEYWORD_RETURN){
        token = get_next_token();
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
            token = get_next_token();
            if (token.type != TYPE_SEMICOLON){
                return ERR_SYNTAX;
            }
        }
    }
    return SYNTAX_OK;
}

int check_return (Syntactic_data_ptr data){
    token_struct token = get_next_token();
    if (token.type == KEYWORD_RETURN){
        token = get_next_token();
        if (token.type == TYPE_SEMICOLON){
            return SYNTAX_OK;
        }
    }else if(token.type == TYPE_BRACE_RIGHT){
        return SYNTAX_OK;
    }
    return ERR_SYNTAX;
}

int check_main_return (Syntactic_data_ptr data){
    token_struct token = get_next_token();
    if (token.type == KEYWORD_RETURN){
        return check_return_rest(data);
    } else {
        if (token.type == EOF){
            return SYNTAX_OK;
        }else if(token.type == TYPE_PROLOG_END){
            token = get_next_token();
            if (token.type == EOF){
                return SYNTAX_OK;
            }
        }
    }
    return ERR_SYNTAX;
}


int check_return_rest (Syntactic_data_ptr data){
    token_struct token = get_next_token();
    if (token.type == TYPE_FUNCTION_ID){
        if (check_function_calling(data) != 0){
            return ERR_SYNTAX;
        }
    }else if (token.type == expression){ //todo Samuel
        if (check_expression(token, data) != 0){
            return ERR_SYNTAX;
        }
        token = get_next_token();
        if (token.type != TYPE_SEMICOLON){
            return ERR_SYNTAX;
        }
    }
    return SYNTAX_OK;

}

int check_f_statement (Syntactic_data_ptr data){
    token_struct token = get_next_token();
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

int check_data_type (Syntactic_data_ptr data){
    token_struct token = get_next_token();
    switch (token.type){
        case (KEYWORD_STRING_Q || KEYWORD_INT_Q || KEYWORD_FLOAT_Q || KEYWORD_FLOAT || KEYWORD_INT || KEYWORD_STRING):{
            return SYNTAX_OK;
        }
    }
    return ERR_SYNTAX;
}

int check_after_equal (Syntactic_data_ptr data){
    token_struct token = get_next_token();
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


int check_assignment(Syntactic_data_ptr data){
    token_struct token = get_next_token();
    if (token.type != TYPE_ASSIGN){
        return ERR_SYNTAX;
    }
    if (check_after_equal(data) != 0){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (token.type != TYPE_SEMICOLON){
        return ERR_SYNTAX;
    }
    return SYNTAX_OK;
}


int check_while(Syntactic_data_ptr data){
    token_struct token = get_next_token();
    if (token.type != TYPE_PAR_LEFT)
        return ERR_SYNTAX;
    token = get_next_token();
    if (check_expression(token, data) != 0){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (token.type != TYPE_PAR_RIGHT) {
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (token.type != TYPE_BRACE_LEFT) {
        return ERR_SYNTAX;
    }
    if (check_f_statements(data) != 0){
        return ERR_SYNTAX;
    }
    return SYNTAX_OK;
}

int check_function_definition(Syntactic_data_ptr data) {
    token_struct token = get_next_token();
    if (token.type != TYPE_FUNCTION_ID)
        return ERR_SYNTAX;
    create_item();//todo doplnit data->function_var
    token = get_next_token();
    if (token.type != TYPE_PAR_LEFT)
        return ERR_SYNTAX;
    token = get_next_token();
    if(check_f_params(data) != 0){
        return ERR_SYNTAX;
    }
    token = get_next_token();
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

int check_condition (Syntactic_data_ptr data){ //verify condition of if
    token_struct token = get_next_token();
    if (token.type != TYPE_PAR_LEFT){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (check_expression(token, data) != 0){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (token.type != TYPE_PAR_RIGHT){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (token.type != TYPE_BRACE_LEFT){
        return ERR_SYNTAX;
    }
    if (check_f_statements(data) != 0){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (token.type != KEYWORD_ELSE){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    if (token.type != TYPE_BRACE_LEFT){
        return ERR_SYNTAX;
    }
    if (check_f_statements(data) != 0){
        return ERR_SYNTAX;
    }
    return SYNTAX_OK;
}

int check_function_calling (Syntactic_data_ptr data){
    token_struct token = get_next_token();
    if (token.type != TYPE_PAR_LEFT){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    switch (token.type) {
        case (TYPE_PAR_RIGHT) :
                return SYNTAX_OK;
        case (TYPE_VARIABLE_ID): //how to check the right number of params?
            return check_function_calling_rest_params (data);
    }
    return ERR_SYNTAX;
}

int check_function_calling_rest_params (Syntactic_data_ptr data){//done
    token_struct token = get_next_token();
    switch (token.type){
        case (TYPE_COMMA):
            token = get_next_token();
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