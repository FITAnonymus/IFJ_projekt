/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief functions for syntactic analyse.
    *
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    * @author Jiri Soukup <xsouku17@stud.fit.vutbr.cz>
    */

#include "expression.h"
#include "error.h"




StackDo PrecTable[18][18] = {
//
//                     {x}     {/}      {+}      {-}      {.}      {<}     {>}     {<=}     {>=}     {===}    {!==}      {(}       {)}     {int}   {float}  {string}  {var_id}    {$}
/*  {x}  */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,PUSH,UNDE,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {/}  */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {+}  */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {-}  */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {.}  */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {<}  */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {>}  */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/* {<=}  */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/* {>=}  */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/* {===} */ {  UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,PUSH,PUSH,PUSH,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/* {!==} */ { UNDE,UNDE,UNDE,UNDE,UNDE,UNDE,PUSH,PUSH,PUSH,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {(}  */ { PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,EQUA,PUSH,PUSH,PUSH,PUSH,UNDE},
/*  {)}  */ { UNDE,UNDE,UNDE,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/* {int}*/  { REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/* {float}*/{ REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/*{string}*/{ REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/*{var_id}*/{ REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/*  {$}  */ { PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,UNDE,PUSH,PUSH,PUSH,PUSH,UNDE},
};



/**
 * @brief Function for choosing operation
 * the function returns operation which will be performed with stack
 *
 * @param Stack input stack, function reads stack top
 * @param token input token, function reads type of token
 * @return Int operation
 */
int relTable(Stack *stack, Token_struct token) {
    int top = stack->top->token->type;
    int curr = token.type;

    return PrecTable[curr][top];

}


/**
 * @brief Function for control of input token
 * the function handles control input token
 * if token is not part of Precedence Table, Syntax error will be occurred
 *
 * @param token token for control
 * @param Syntactic_data_ptr Data set where error code will be writen
 * @return ErrorStatus
 */
int check_valid_char(Token_struct token, Syntactic_data_ptr data) {
    switch (token.type) {
        case (TYPE_MUL):
            return SYNTAX_OK;
        case (TYPE_DIV):
            return SYNTAX_OK;
        case (TYPE_PLUS):
            return SYNTAX_OK;
        case (TYPE_MINUS):
            return SYNTAX_OK;
        case (TYPE_CONCAT):
            return SYNTAX_OK;
        case (TYPE_LOWER):
            return SYNTAX_OK;
        case (TYPE_GREATER):
            return SYNTAX_OK;
        case (TYPE_GREATER_EQ):
            return SYNTAX_OK;
        case (TYPE_LOWER_EQ):
            return SYNTAX_OK;
        case (TYPE_COMPARE):
            return SYNTAX_OK;
        case (TYPE_COMPARE_NEG):
            return SYNTAX_OK;
        case (TYPE_BRACE_LEFT):
            return SYNTAX_OK;
        case (TYPE_BRACE_RIGHT):
            return SYNTAX_OK;
        case (TYPE_VARIABLE_ID):
            return SYNTAX_OK;
        case (TYPE_INTEGER):
            return SYNTAX_OK;
        case (TYPE_FLOAT):
            return SYNTAX_OK;
        case (TYPE_STRING):
            return SYNTAX_OK;

        default:
            break;
    }
    data->error_status = ERR_SYNTAX;
    return ERR_SYNTAX;
}


/**
 * @brief Function for dealing with stack
 * Function take operation from check_valid_char and perform operation over stack
 *
 * @see check_valid_char
 * @param stack Stack for operation
 * @param token token for operation
 * @param Syntactic_data_ptr Data set where error code will be writen
 * @return ErrorStatus
 */
int check_expParse(Stack *stack, Token_struct token, Syntactic_data_ptr data){
    int operation = relTable(stack, token);
    switch (operation) {
        case (PUSH):
            if (token.type == TYPE_FLOAT || token.type == TYPE_INTEGER || token.type == TYPE_STRING || token.type == TYPE_VARIABLE_ID) {
                if (stack_push(stack, data->buffer.token[data->buffer.length-1], VARIALBLE, 1)) {
                    data->error_status = ERR_INTERNAL;
                    return ERR_INTERNAL;
                }
            }else{
                if (stack_push(stack, data->buffer.token[data->buffer.length-1], NOT_VARIALBLE, 0)) {
                    data->error_status = ERR_INTERNAL;
                    return ERR_INTERNAL;
                }
            }
            return SYNTAX_OK;

        case (REDU):
            while (stack->top->stop != 1) {
                if (stack_pop(stack) == NULL) {
                    data->error_status = ERR_INTERNAL;
                    return ERR_INTERNAL;
                }
            }
//            if (token->type == TYPE_FLOAT || token->type == TYPE_INTEGER || token->type == TYPE_STRING || token->type == TYPE_VARIABLE_ID) {
//                if (stack_push(stack, &data->buffer.token[data->buffer.length-1], VARIALBLE, 1)) {
//                    return ERR_INTERNAL;
//                }
//            }else{
//                if (stack_push(stack, &data->buffer.token[data->buffer.length-1], NOT_VARIALBLE, 0)) {
//                    return ERR_INTERNAL;
//                }
//            }
            return SYNTAX_OK;

        case (EQUA):
            if (stack_pop(stack)) {
                data->error_status = ERR_INTERNAL;
                return ERR_INTERNAL;
            }
            return SYNTAX_OK;

        case (UNDE):
            data->error_status = ERR_SYNTAX;
            return ERR_SYNTAX;

        default:
            data->error_status = ERR_INTERNAL;
            return ERR_INTERNAL;

    }
}


/**
 * @brief Main function for handling expressions
 * Function which handles expression
 * Function decides if expression is correct or not
 *
 * @param token Start token -> decide if it's expression or assigment
 * @param Syntactic_data_ptr Data set where error code will be writen
 * @param inside_par decide if end of expression can be ')'
 * @return ErrorStatus
 */
int check_expression(Token_struct token, Syntactic_data_ptr data, int inside_par){
    Stack stack;
    init_stack(&stack);

    /// Pushing end $ on stack
    Token_struct dollar;
    if (stack_push(&stack, &dollar, E_$, 1))
        return ERR_INTERNAL;


    unsigned long previous = data->buffer.length - 2;

    /// Pushing if previous token was STRING/FLOAT/INTEGER/VAR_ID
    if (data->buffer.token[previous]->type == TYPE_STRING || data->buffer.token[previous]->type == TYPE_FLOAT || data->buffer.token[previous]->type == TYPE_INTEGER || data->buffer.token[previous]->type == TYPE_VARIABLE_ID){
        if (stack_push(&stack, data->buffer.token[previous], VARIALBLE, 1)) {
            data->error_status = ERR_INTERNAL;
            return ERR_INTERNAL;
        }

        if (check_expParse(&stack, token, data)) {
            data->error_status = ERR_INTERNAL;
            return ERR_INTERNAL;
        }

    }
    else {
        /// Pushing incoming token on stack - checking
        if (check_valid_char(token, data)) {
            free_stack(&stack);
            data->error_status = ERR_SYNTAX;
            return ERR_SYNTAX;
        }
        if (token.type == TYPE_FLOAT || token.type == TYPE_INTEGER || token.type == TYPE_STRING || token.type == TYPE_VARIABLE_ID) {
            if (stack_push(&stack, data->buffer.token[data->buffer.length-1], VARIALBLE, 1)) {
                data->error_status = ERR_INTERNAL;
                return ERR_INTERNAL;
            }
        }else{
            if (stack_push(&stack, data->buffer.token[data->buffer.length-1], NOT_VARIALBLE, 0)) {
                data->error_status = ERR_INTERNAL;
                return ERR_INTERNAL;
            }
        }
    }

    int par_counter = 0;
    if (inside_par)
        par_counter = -1;


    token = Get_token(data);

    while (!((stack.top->relation == E_$ || (stack.top->relation == VARIALBLE && stack.top->next->relation == E_$)) && (token.type == TYPE_SEMICOLON || (token.type == TYPE_PAR_RIGHT && par_counter + 1 == 0)) )){

        if (check_valid_char(token, data)) {
            free_stack(&stack);
            data->error_status = ERR_SYNTAX;
            return ERR_SYNTAX;
        }

        if (token.type == TYPE_PAR_RIGHT)
            par_counter -= 1;
        else if (token.type == TYPE_BRACE_LEFT)
            par_counter += 1;
        if (check_expParse(&stack, token, data)) {
            free_stack(&stack);
            data->error_status = ERR_SYNTAX;
            return ERR_SYNTAX;
        }
        token = Get_token(data);

    }
    free_stack(&stack);
    return SYNTAX_OK;
}


