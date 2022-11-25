#ifndef SEMANTICS_H
#define SEMANTICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>
#include "scanner.h"
#include "syntactic.h"
#include "error.h"

#define buffer_get_keyword buff
#define istypes (currentType == TYPE_INTEGER || currentType == TYPE_FLOAT || currentType == TYPE_STRING)


#define buffer_get_keyword buff
#define istypes (currentType == TYPE_INTEGER || currentType == TYPE_FLOAT || currentType == TYPE_STRING)

int check_int(char *key, Hash_table_ptr *p_table);
int check_float(char *key, Hash_table_ptr *p_table);
int check_String(char *key, Hash_table_ptr *p_table);
int check_var_existence(char *key, Hash_table_ptr *p_table, PHash_table_ptr *pp_table);
int sem_check_return(PHash_table_ptr *p_table, char *key, int type, PItemPtr *p_item);
int sem_check_expression(Syntactic_data_ptr *data, int startIndex, int endingType, int *endIndex);
int assertion(Syntactic_data_ptr *data, int index);
int var_declaration(Syntactic_data_ptr *data, int index, int expectedType, int nullSupport);
int decide_expr_or_assignment(Syntactic_data_ptr *data, int index);
int process_one_command(Syntactic_data_ptr *data, int index, int *endIndex);
int process_block(Syntactic_data_ptr *data, int index, int *endIndex);
void sem_check_argument(Syntactic_data_ptr *data, int indexInBuffer, char *name, PItemPtr pitem);
void sem_check_arguments(Syntactic_data_ptr *data);
void process_buffer_fill_ptabel(Syntactic_data_ptr *data, int *endIndex);
void sem_check_function_definition(Syntactic_data_ptr *data);
void check_function_call(Syntactic_data_ptr *data);
int check_type_a_exist(Syntactic_data_ptr *data, int bufferIndex, int *endIndex);
int sem_check_condition(Syntactic_data_ptr *data, int bufferIndex, int *endInd);
void sem_check_if(Syntactic_data_ptr *data, int startIndex, int* endIndex);
void sem_check_while(Syntactic_data_ptr *data, int startIndex, int* endIndex);

#endif