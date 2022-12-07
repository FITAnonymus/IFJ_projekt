/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    * @file syntactic.h
    * @brief Implementation of syntactic analysand.
    *
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    */

#ifndef SYNTACTIC_H
#define SYNTACTIC_H



#include "scanner.h"
#include "symtable.h"
#include "token_buffer.h"


/**
 * @struct Data for syntactic analyzer
 */

typedef struct syntactic_data{
    int inside_function;
    int error_status;

    Hash_table_ptr used_var;
    PHash_table_ptr function_var;
    Token_buffer buffer;
    Hash_table_ptr main_var;
    Hash_table_ptr local_var;
}Syntactic_data;

typedef Syntactic_data *Syntactic_data_ptr;

void Program_Error(int error, Syntactic_data_ptr data);

Token_struct Get_token(Syntactic_data_ptr data);

void Insert_to_buffer(Token_struct * token, Syntactic_data_ptr data);

#endif