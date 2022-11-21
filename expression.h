//
// Created by Peaky Blinders
//

#ifndef IFJ_PROJEKT_EXPRESSION_H
#define IFJ_PROJEKT_EXPRESSION_H



typedef enum{
    E_OPEN,		//!< push (<)
    E_CLOSE,	//!< reduce (>)
    E_EQUAL,	//!< equal (=)
    E_EMPTY		//!< nondefined (_)
} stack_do;

int check_expression(Token_struct token, Syntactic_data_ptr data);

#endif //IFJ_PROJEKT_EXPRESSION_H