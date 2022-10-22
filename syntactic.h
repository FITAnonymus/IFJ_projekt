//
// Created by samuel on 19.10.2022.
//

#ifndef IFJ_PROJEKT_SYNTACTIC_H
#define IFJ_PROJEKT_SYNTACTIC_H

#endif //IFJ_PROJEKT_SYNTACTIC_H

#include <stdbool.h>
#include <symtable.h>


/**
 * @struct Data for syntactic analyzer
 */

typedef struct syntactic_data{
    bool inside_program_closures;
    bool inside_function;
    bool inside_condition;
    bool inside_loop;


    Hash_table main_var;
    Hash_table local_var;



}Syntactic_data;

typedef Syntactic_data *Syntactic_data_ptr;