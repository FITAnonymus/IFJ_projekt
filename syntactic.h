//
// Created by samuel on 19.10.2022.
//

#ifndef IFJ_PROJEKT_SYNTACTIC_H
#define IFJ_PROJEKT_SYNTACTIC_H

#include <stdbool.h>
#include <symtable.h>
#include <scanner.h>
#include "token_buffer.h"

/**
 * @struct Data for syntactic analyzer
 */

typedef struct syntactic_data{
    int error_status;
    Hash_table_ptr used_var;
    Hash_table_ptr function_var;
    Token_buffer buffer;

    Hash_table_ptr main_var;
    Hash_table_ptr local_var;
}Syntactic_data;

typedef Syntactic_data *Syntactic_data_ptr;
