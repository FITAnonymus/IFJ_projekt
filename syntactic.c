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




Syntactic_data_ptr Init_data(){
    Syntactic_data_ptr data_ptr = (Syntactic_data_ptr) malloc(sizeof(Syntactic_data));
    if (data_ptr == NULL){
        Program_Error(ERR_INTERNAL);
    }

    data_ptr->global_var = NULL;
    data_ptr->main_var = NULL:
    data_ptr->local_var = NULL;
    data_ptr->inside_condition = FALSE;
    data_ptr->inside_function = FALSE;
    data_ptr->inside_loop = FALSE;
    data_ptr->inside_program_closures = FALSE;
    return data_ptr;
}


void Destroy_data(Syntactic_data_ptr to_delete){
    if (to_delete == NULL) {
        return;
    }

    free_table(to_delete->main_var);
    free_table(to_delete->local_var);
    free(to_delete);

}


void Program_Error(int error, Syntactic_data_ptr data){
    Destroy_data(data);
    exit(error);
}




bool Handle_function(Syntactic_data_ptr data){

}

bool Handle_if(Syntactic_data_ptr data){

}

bool Handle_while(Syntactic_data_ptr data){

}


int main(){

    token_struct token;
    token = GET_NEXT_TOKEN();

    if (validate_program(token)){
        return ERR_SYNTAX;
    }

    Syntactic_data_ptr data = Init_data();
    create_table(50, data->main_var);
    token = GET_NEXT_TOKEN();

    while(token.type != TYPE_PROLOG_END) {

        switch (token.type) {
            case (KEYWORD_FUNCTION):
                if (Handle_function(data)) {
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

            default:
                Program_Error(ERR_SYNTAX, data);
        }

        token = get_next_token();
    }

}