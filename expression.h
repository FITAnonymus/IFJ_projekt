//
// Created by Peaky Blinders
//

#ifndef IFJ_PROJEKT_EXPRESSION_H
#define IFJ_PROJEKT_EXPRESSION_H

#endif //IFJ_PROJEKT_EXPRESSION_H


typedef enum{
    E_OPEN,		//!< push (<)
    E_CLOSE,	//!< reduce (>)
    E_EQUAL,	//!< equal (=)
    E_EMPTY		//!< nondefined (_)
    E_END       //!<  $<$
} stack_do;

int check_expression(Token_struct token, Syntactic_data_ptr data);

#endif //IFJ_PROJEKT_EXPRESSION_H
    push,		    // (<)
    reduce,	        // (>)
    equal,	        // (=)
    undefined		// (_)
} StackDo;

typedef enum{
    relation,
    term,
    nonterm,
} StackTop;

typedef enum{
    GELE,
    Concatenate,
    MulDiv,
    PlusMinus,
    NotEqual,
    Equal,
    LeftPar,
    RightPar,
    Variable,
    E_$
} Relation;


typedef enum{
    s_int,
    s_float,
    s_string,
    s_var
} TermType;



