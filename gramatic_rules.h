//
// Created by samuel on 22.11.2022.
//

#ifndef IFJ_PROJEKT_GRAMATIC_RULES_H
#define IFJ_PROJEKT_GRAMATIC_RULES_H

#include "syntactic.h"
#include "error.h"
#include "token_buffer.h"
#include "expression.h"


int check_function_definition(Syntactic_data_ptr data);

int check_data_type (Token_struct token);

int check_f_rest_params(Syntactic_data_ptr data);

int check_function_calling (Syntactic_data_ptr data);

int check_f_statements(Syntactic_data_ptr data);

int check_f_void_statements(Syntactic_data_ptr data);

int check_while (Syntactic_data_ptr data);

int check_assignment (Syntactic_data_ptr data);

int check_condition (Syntactic_data_ptr data);

int check_f_statement (Token_struct token, Syntactic_data_ptr data);

int check_return (Token_struct token, Syntactic_data_ptr data);

int check_f_void_statement (Syntactic_data_ptr data);

int check_return_rest (Syntactic_data_ptr data);

int check_function_calling_rest_params (Syntactic_data_ptr data);

#endif //IFJ_PROJEKT_GRAMATIC_RULES_H
