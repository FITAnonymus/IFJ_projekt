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

int check_expression(token_struct token, Syntactic_data_ptr data){
    return 0;
}

int check_asignment(Syntactic_data_ptr data){
    return 0;
}


int check_while(Syntactic_data_ptr data){
    return 0;
}

int check_function_definition(Syntactic_data_ptr data){
    token_struct token = get_next_token();
    if (token.type != KEYWORD_FUNCTION)
        return ERR_SYNTAX;
    token = get_next_token();
    if (token.type != TYPE_FUNCTION_ID)
        return ERR_SYNTAX;
    token = get_next_token();
    if (token.type != TYPE_PAR_LEFT)
        return ERR_SYNTAX;
    token = get_next_token();
    switch (token.type){
        case ()
    }
    return ERR_SYNTAX;
}

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
            return check_asignment(data);
        case (TYPE_VALUE): //ask Daniel
            return check_expression(token, data);
    }
    return ERR_SYNTAX;
}

bool check_compare(token_struct token){
    switch (token.type){
        case (TYPE_FUNCTION_ID):
            check_function_calling(data);
    }
}

int check_condition (Syntactic_data_ptr data){ //verify condition of while and if
    token_struct token = get_next_token();
    if (token.type != TYPE_PAR_LEFT){
        return ERR_SYNTAX;
    }
    token = get_next_token();
    while (token.type == ) {
        switch (token.type) {
            case (TYPE_FUNCTION_ID) :
                check_function_calling(data);
                break;
            case (TYPE_VALUE): //ask Daniel

        }
        token = get_next_token();
    }
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
            token = get_next_token();
            return check_function_calling_rest_params (token, data);
    }
}

int check_function_calling_rest_params (token_struct token, Syntactic_data_ptr data){//done
    switch (token.type){
        case (TYPE_COMMA):
            token = get_next_token();
            if (token.type != TYPE_VARIABLE_ID){
                return ERR_SYNTAX;
            }else{
                return check_function_calling_rest_params (token, data);
            }
        case (TYPE_PAR_RIGHT):
            return SYNTAX_OK;
    }
    return ERR_SYNTAX;
}