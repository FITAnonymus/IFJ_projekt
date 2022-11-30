/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief functions for syntactic analyse.
    *
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    */

#include "expression.h"
#include "error.h"
#include <stdio.h>



/**
 * @brief PrecTable
 * Table for defining function
 *
 * @author Jiri Soukup
 */
StackDo PrecTable[18][18] = {
//
//                     {x}     {/}      {+}      {-}      {.}      {<}     {>}     {<=}     {>=}     {===}    {!==}      {(}       {)}     {int}   {float}  {string}  {var_id}    {$}
/*  {x}  */ {  REDU,UNDE,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {/}  */ {  UNDE,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {+}  */ {  PUSH,PUSH,REDU,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {-}  */ {  PUSH,PUSH,UNDE,REDU,UNDE,REDU,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {.}  */ {  PUSH,PUSH,UNDE,UNDE,REDU,REDU,REDU,REDU,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {<}  */ {  PUSH,PUSH,PUSH,PUSH,PUSH,REDU,UNDE,UNDE,UNDE,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {>}  */ {  PUSH,PUSH,PUSH,PUSH,PUSH,UNDE,REDU,UNDE,UNDE,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/* {<=}  */ {  PUSH,PUSH,PUSH,PUSH,PUSH,UNDE,UNDE,REDU,UNDE,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/* {>=}  */ {  PUSH,PUSH,PUSH,PUSH,PUSH,UNDE,UNDE,UNDE,REDU,REDU,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/* {===} */ {  PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,REDU,UNDE,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/* {!==} */ { PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,UNDE,REDU,PUSH,REDU,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {(}  */ { PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,EQUA,PUSH,PUSH,PUSH,PUSH,REDU},
/*  {)}  */ { REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/* {int}*/  { REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/* {float}*/{ REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/*{string}*/{ REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/*{var_id}*/{ REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,REDU,UNDE,REDU,UNDE,UNDE,UNDE,UNDE,REDU},
/*  {$}  */ { PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,PUSH,UNDE},
};



/**
 * @brief Function for choosing operation
 * the function returns operation which will be performed with stack
 *
 * @param Stack input stack, function reads stack top
 * @param token input token, function reads type of token
 * @return Int operation
 */
int relTable(Stack *stack, Token_struct token, int par_counter) {
    int top = stack->top->token->type;
    int curr = token.type;

    if (stack->top->relation == E_$)
        return PrecTable[17][curr];

    if (token.type == TYPE_SEMICOLON || (token.type == TYPE_PAR_RIGHT && par_counter <= -1))
        return PrecTable[top][17];

    if (stack->top->relation == EXPR) {
        top = stack->top->next->token->type;
        if (stack->top->next->relation == E_$){
            return PrecTable[17][curr];
        }
    }


    return PrecTable[top][curr];

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
        case (TYPE_PAR_LEFT):
            return SYNTAX_OK;
        case (TYPE_PAR_RIGHT):
            return SYNTAX_OK;
        case (TYPE_VARIABLE_ID):
            return SYNTAX_OK;
        case (TYPE_INTEGER):
            return SYNTAX_OK;
        case (TYPE_FLOAT):
            return SYNTAX_OK;
        case (TYPE_STRING):
            return SYNTAX_OK;
        case (TYPE_SEMICOLON):
            return SYNTAX_OK;

        default:
            break;
    }
    data->error_status = ERR_SYNTAX;
    return ERR_SYNTAX;
}

void choose_rule(Stack * stack){

    /// E -> i
    if (stack->top->relation == VARIALBLE){
        stack->top->relation = EXPR;

        return;
    }

    /// E -> E * E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_MUL && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

    /// E -> E / E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_DIV && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

    /// E -> E + E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_PLUS && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

    /// E -> E - E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_MINUS && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

    /// E -> (E)
    if (stack->top->token->type == TYPE_PAR_RIGHT && stack->top->next->relation == EXPR && stack->top->next->next->token->type == TYPE_PAR_LEFT){
        stack_pop(stack);
        stack->top->next->token = stack->top->token;
        stack->top->next->relation = EXPR;
        stack->top->next->stop = 1;
        stack_pop(stack);
        return;
    }

    /// E -> E === E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_COMPARE && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

    /// E -> E !== E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_COMPARE_NEG && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

    /// E -> E < E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_LOWER && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

    /// E -> E <= E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_LOWER_EQ && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

    /// E -> E > E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_GREATER && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

    /// E -> E >= E
    if (stack->top->relation == EXPR && stack->top->next->token->type == TYPE_GREATER_EQ && stack->top->next->next->relation == EXPR){
        stack_pop(stack);
        stack_pop(stack);
        return;
    }

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
int check_expParse(Stack *stack, Token_struct *token, Syntactic_data_ptr data, int * par_counter){
    int operation = relTable(stack, *token, *par_counter);
    switch (operation) {
        case (PUSH):
            if (token->type == TYPE_FLOAT || token->type == TYPE_INTEGER || token->type == TYPE_STRING || token->type == TYPE_VARIABLE_ID) {
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

            *token = Get_token(data);

            if (token->type == TYPE_PAR_RIGHT)
                *par_counter -= 1;
            else if (token->type == TYPE_PAR_LEFT)
                *par_counter += 1;

            return SYNTAX_OK;

        case (REDU):
            if (stack->top->stop == 1){
                choose_rule(stack);
            }
            else{
                data->error_status = ERR_SYNTAX;
                return ERR_SYNTAX;
            }
            return SYNTAX_OK;

        case (EQUA):
            if (stack_push(stack, data->buffer.token[data->buffer.length-1], NOT_VARIALBLE, 1)) {
                data->error_status = ERR_INTERNAL;
                return ERR_INTERNAL;
            }

            *token = Get_token(data);

            if (token->type == TYPE_PAR_RIGHT)
                *par_counter -= 1;
            else if (token->type == TYPE_PAR_LEFT)
                *par_counter += 1;

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

    int par_counter = 0;
    if (inside_par)
        par_counter = -1;


    unsigned long previous = data->buffer.length - 2;

    /// Pushing if previous token was STRING/FLOAT/INTEGER/VAR_ID
    if (data->buffer.token[previous]->type == TYPE_STRING || data->buffer.token[previous]->type == TYPE_FLOAT || data->buffer.token[previous]->type == TYPE_INTEGER || data->buffer.token[previous]->type == TYPE_VARIABLE_ID){
        if (stack_push(&stack, data->buffer.token[previous], VARIALBLE, 1)) {
            data->error_status = ERR_INTERNAL;
            return ERR_INTERNAL;
        }

        if (check_expParse(&stack, &token, data, &par_counter)) {
            data->error_status = ERR_SYNTAX;
            return ERR_SYNTAX;
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
        token = Get_token(data);
    }


    while((stack.top->next->relation != E_$ || stack.top->relation != EXPR) || (token.type != TYPE_SEMICOLON  && token.type != TYPE_PAR_RIGHT )) {
        if (check_valid_char(token, data)) {
            free_stack(&stack);
            data->error_status = ERR_SYNTAX;
            return ERR_SYNTAX;
        }

        if (check_expParse(&stack, &token, data, &par_counter)) {
            free_stack(&stack);
            data->error_status = ERR_SYNTAX;
            return ERR_SYNTAX;
        }

    }
    free_stack(&stack);
    printf("Expression OK\n");
    return SYNTAX_OK;
}


