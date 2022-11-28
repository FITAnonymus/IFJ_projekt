//
// Created by samuel on 19.10.2022.
//

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


Token_struct Get_token(Syntactic_data_ptr data);

void Insert_to_buffer(Token_struct * token, Syntactic_data_ptr data);

#endif