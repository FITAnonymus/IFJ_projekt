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
    if (to_delete == NULL){
        return;
    }

    free(to_delete);

}


void Program_Error(int error, Syntactic_data_ptr data){
    Destroy_data(data);
    exit(error);
}



int main(){

    token_struct token;
    token = GET_NEXT_TOKEN()

    if (validate_program(token)){
        return ERR_SYNTAX;
    }

}