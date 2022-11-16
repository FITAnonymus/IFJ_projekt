//
// Created by samuel on 19.10.2022.
//


/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of syntactic analasys.
    *
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    */


#include "syntactic.h"
#include "scanner.c"
#include "symtable.c"
#include "scanner.h"
#include "error.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define FALSE 0
#define TRUE 1


void Destroy_data(Syntactic_data_ptr to_delete){
    if (to_delete == NULL) {
        return;
    }

    free_table(to_delete->main_var);
    free_table(to_delete->local_var);
    free_table(to_delete->function_var);
    free(to_delete);

void Program_Error(int error, Syntactic_data_ptr data){
    Destroy_data(data);
    exit(error);
}



Syntactic_data_ptr* Init_data(){
    Syntactic_data_ptr *data_ptr = malloc(sizeof(struct Syntactic_data));
    if (data_ptr == NULL){
        Program_Error(ERR_INTERNAL);
    }

    data_ptr->used_var = NULL;
    data_ptr->main_var = NULL:
    data_ptr->local_var = NULL;
    data_ptr->inside_condition = FALSE;
    data_ptr->inside_function = FALSE;
    data_ptr->inside_loop = FALSE;
    data_ptr->inside_program_closures = FALSE;

    return data_ptr;
}

token_struct Get_token(){
    return token;
}

}


int Handle_function_dec(Syntactic_data_ptr data){
    /// Create local sym_table for function
    create_table(1543, data->local_var);

    /// Start of grammar check
    if (check_function_definition(data) != TRUE)
        return SYNTAX_ERR;


    /// Delete sources clean up
    free_table(data->local_var);
    data->used_var = data->main_var;
    return SYNTAX_OK;

}

bool Handle_if(Syntactic_data_ptr data){


}

bool Handle_while(Syntactic_data_ptr data){

}

int main(){
    token_struct token = get_next_token();

    if (validate_program(token)){
        Program_Error(ERR_SYNTAX, data);;
    }

    Syntactic_data_ptr* data = Init_data();
    create_table(1543, data->main_var);
    create_table(1543, data->function_var);
    parser();

    return 0;
}

int parser(Syntactic_data_ptr data){

    token_struct token = get_next_token();

    while(token.type != TYPE_PROLOG_END || token.type != TYPE_EOF) {
        switch (token.type) {
            case (KEYWORD_FUNCTION):
                if (Handle_function_dec(data)) {
                    Program_Error(ERR_SYNTAX, data);
                }
                break;
            case (KEYWORD_IF):
                if (Handle_if(data)) {
                    Program_Error(ERR_SYNTAX, data);
                }
                break;

            case (KEYWORD_WHILE):
                if (Handle_while(data)) {
                    Program_Error(ERR_SYNTAX, data);
                }
                break;

            case (KEYWORD_INT || KEYWORD_FLOAT || KEYWORD_STRING):
                break;

            case (TYPE_BRACE_RIGHT):
                if (data->inside_function || data->inside_loop || data->inside_condition)
                    return SYNTAX_OK;

            default:
                Program_Error(ERR_SYNTAX, data);
        }

        token = get_next_token();
    }

}
