//
// Created by Peaky Blinders
//

#ifndef IFJ_PROJEKT_EXPRESSION_H
#define IFJ_PROJEKT_EXPRESSION_H

#include "scanner.h"
#include "syntactic.h"


int check_expression(Token_struct token, Syntactic_data_ptr data, int inside_par);

typedef enum{
    PUSH,		    // (<)
    REDUCE,	        // (>)
    EQUAL,	        // (=)
    UNDEFINED,		// (_)
    END
} StackDo;

typedef enum{
    RELATION,
    TERM,
    NONTERM,
} StackTop;

typedef enum{
    GELE,
    CONCATENATE,
    MULDIV,
    PLUSMINUS,
    NOTEQUAL,
    LEFTPAR,
    RIGHTPAR,
    VARIALBLE,
    E_$
} Relation;


typedef enum{
    s_int,
    s_float,
    s_string,
    s_var
} TermType;


#endif //IFJ_PROJEKT_EXPRESSION_H

