/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    * @file expression.h
    * @brief Library for lexical analysis.
    *
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    */

#ifndef IFJ_PROJEKT_EXPRESSION_H
#define IFJ_PROJEKT_EXPRESSION_H

#include "scanner.h"
#include "syntactic.h"
#include "syntactic_stack.h"

int check_valid_char(Token_struct token, Syntactic_data_ptr data);

//int relTable(Stack stack, Token_struct token);

int check_expression(Token_struct token, Syntactic_data_ptr data, int inside_par);



typedef enum {
    PUSH,		    // (<)
    REDU,	        // (>)
    EQUA,	        // (=)
    UNDE,		// (_)
    END
} StackDo;


typedef enum{
    VARIALBLE,
    EXPR,
    NOT_VARIALBLE,
    E_$
} Relation;


typedef enum{
    s_int,
    s_float,
    s_string,
    s_var
} TermType;


#endif //IFJ_PROJEKT_EXPRESSION_H

