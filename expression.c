/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief functions for syntactic analyse.
    *
    * @author Jiri Soukup <xsouku17@stud.fit.vutbr.cz>
    */

#include "expression.h"
#include "syntactic.h"
#include "syntactic_stack.h"
#include "error.h"


int check_expParse(Stack stack, Token_struct token);

const int PTable[16][16] = {
//
//                  {x}       {/}      {+}         {-}          {.}       {<}      {>}         {<=}       {>=}      {===}      {!==}       {(}         {)}      {int}    {float}   {string}  {$}
/*  {x}  */ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH,PUSH, PUSH, REDUCE },
/*  {/}  */ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, REDUCE },
/*  {+}  */ { PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH,PUSH,PUSH, REDUCE },
/*  {-}  */ { PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH,REDUCE },
/*  {.}  */ { PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, REDUCE },
/*  {<}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, REDUCE },
/*  {>}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, REDUCE },
/* {<=}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, REDUCE },
/* {>=}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, REDUCE },
/* {===} */ { PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH,REDUCE },
/* {!==} */ { PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, PUSH, REDUCE, PUSH,PUSH, PUSH,REDUCE },
/*  {(}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH, EQUAL, PUSH, PUSH, PUSH, REDUCE},
/*  {)}  */ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE,UNDEFINED, REDUCE,UNDEFINED, UNDEFINED, UNDEFINED,REDUCE},
/* {int}*/ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE,UNDEFINED, REDUCE,UNDEFINED, UNDEFINED,UNDEFINED,REDUCE},
/* {float}*/ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE,UNDEFINED, REDUCE,UNDEFINED, UNDEFINED,UNDEFINED, REDUCE},
/* {string}*/ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE,UNDEFINED, REDUCE,UNDEFINED, UNDEFINED,UNDEFINED, REDUCE},
/*  {$}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH ,PUSH , PUSH, PUSH, PUSH, PUSH, END  },
};



//REDUCE or not REDUCE
int relTable(Stack stack, Token_struct token) {
    int top = stack.top->token->type;
    int curr = token.type;

    return PTable[top][curr];

}


//function to prepare item
int check_valid_char(Token_struct token) {
    switch (token.type) {
        case (TYPE_MUL):
            break;
        case (TYPE_DIV):
            break;
        case (TYPE_PLUS):
            break;
        case (TYPE_MINUS):
            break;
        case (TYPE_CONCAT):
            break;
        case (TYPE_LOWER):
            break;
        case (TYPE_GREATER):
            break;
        case (TYPE_GREATER_EQ):
            break;
        case (TYPE_LOWER_EQ):
            break;
        case (TYPE_COMPARE):
            break;
        case (TYPE_COMPARE_NEG):
            break;
        case (TYPE_BRACE_LEFT):
            break;
        case (TYPE_BRACE_RIGHT):
            break;
        case (TYPE_VARIABLE_ID):
            break;

        default:
            return ERR_SYNTAX;
    }
    return SYNTAX_OK;
}


//function to REDUCE terms on stack
int check_expParse(Stack stack, Token_struct token){
    int operation = relTable(stack, token);

    switch (operation) {
        case (PUSH):
            if (stack_push(&stack, &token))
                return ERR_INTERNAL;
            if (token.type == TYPE_STRING || token.type == TYPE_INTEGER || token.type == TYPE_FLOAT)
                stack.top->stop = 1;
            return SYNTAX_OK;

        case (REDUCE):
            while (stack.top->stop != 1){
                if (stack_pop(&stack))
                    return ERR_INTERNAL;
            }
            return SYNTAX_OK;

        case (EQUAL):
            if (stack_pop(&stack))
                return ERR_INTERNAL;
            return SYNTAX_OK;

        case (UNDEFINED):
            return ERR_SYNTAX;

        default:
            return ERR_INTERNAL;

    }

}


//main function of expression control
int check_expression(Token_struct token, Syntactic_data_ptr data, int inside_par){
    Stack stack;
    init_stack(&stack);

    Token_struct dollar;
    if (stack_push(&stack, &dollar))
        return ERR_INTERNAL;
    stack.top->relation = E_$;

    if (stack_push(&stack, &token)){
        return ERR_INTERNAL;
    }

    int par_counter;
    if (inside_par)
        par_counter +=1;

    token = Get_token(data);
    Insert_to_buffer(token, data);

    while ((stack.top->relation == E_$ && (token.type == TYPE_SEMICOLON || token.type == TYPE_PAR_RIGHT) && par_counter == 0)){
        if (check_valid_char(token)) {
            free_stack(&stack);
            return ERR_SYNTAX;
        }


        if (token.type == TYPE_PAR_RIGHT)
            par_counter -= 1;
        else if (token.type == TYPE_BRACE_LEFT)
            par_counter += 1;

        if (check_expParse(stack,token)) {
            free_stack(&stack);
            return ERR_SYNTAX;
        }

        token = Get_token(data);
        Insert_to_buffer(token, data);
    }

    free_stack(&stack);
    return SYNTAX_OK;
}


