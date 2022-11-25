/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief functions for syntactic analyse.
    *
    * @author Jiri Soukup <xsouku17@stud.fit.vutbr.cz>
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    */

#include "expression.h"
#include "error.h"
#include "stdio.h"




StackDo PrecTable[18][18] = {
//
//                  {x}         {/}           {+}         {-}          {.}        {<}         {>}         {<=}       {>=}      {===}      {!==}       {(}         {)}      {int}    {float}   {string}  {$}
/*  {x}  */ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH,PUSH, PUSH, PUSH, REDUCE },
/*  {/}  */ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, PUSH, REDUCE },
/*  {+}  */ { PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH,PUSH,PUSH, PUSH, REDUCE },
/*  {-}  */ { PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, PUSH, REDUCE },
/*  {.}  */ { PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, PUSH, REDUCE },
/*  {<}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, PUSH, REDUCE },
/*  {>}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, PUSH,REDUCE },
/* {<=}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, PUSH, REDUCE },
/* {>=}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, PUSH,REDUCE },
/* {===} */ { PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, PUSH, REDUCE, PUSH, PUSH, PUSH, PUSH,REDUCE },
/* {!==} */ { PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , REDUCE, REDUCE, PUSH, REDUCE, PUSH,PUSH, PUSH, PUSH, REDUCE },
/*  {(}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH, EQUAL, PUSH, PUSH, PUSH, PUSH,REDUCE},
/*  {)}  */ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE,UNDEFINED, REDUCE,UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED, REDUCE},
/* {int}*/ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE,UNDEFINED, REDUCE,UNDEFINED, UNDEFINED,UNDEFINED, UNDEFINED,REDUCE},
/* {float}*/ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE,UNDEFINED, REDUCE,UNDEFINED, UNDEFINED,UNDEFINED, UNDEFINED, REDUCE},
/* {string}*/ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE,UNDEFINED, REDUCE,UNDEFINED, UNDEFINED,UNDEFINED, UNDEFINED, REDUCE},
/* {var_id}*/ { REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE, REDUCE,UNDEFINED, REDUCE,UNDEFINED, UNDEFINED,UNDEFINED, UNDEFINED, REDUCE},
/*  {$}  */ { PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH , PUSH ,PUSH , PUSH, PUSH, PUSH, PUSH, PUSH, END  },
};



//REDUCE or not REDUCE
int relTable(Stack stack, Token_struct token) {
    int top = stack.top->token->type;
    printf("TOP : %d\n",top);
    int curr = token.type;
    printf("CURR : %d\n",curr);

    return PrecTable[top][curr];

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
        case (TYPE_INTEGER):
            break;
        case (TYPE_FLOAT):
            break;
        case (TYPE_STRING):
            break;

        default:
            return ERR_SYNTAX;
    }
    return SYNTAX_OK;
}


//function to REDUCE terms on stack
int check_expParse(Stack stack, Token_struct token, Syntactic_data_ptr data){
    int operation = relTable(stack, token);
    printf("Operation : %d\n", operation);
    switch (operation) {
        case (PUSH):
            if (token.type == TYPE_FLOAT || token.type == TYPE_INTEGER || token.type == TYPE_STRING || token.type == TYPE_VARIABLE_ID) {
                if (stack_push(&stack, &data->buffer.token[data->buffer.length-1], VARIALBLE, 1)) {
                    return ERR_INTERNAL;
                }
            }else{
                if (stack_push(&stack, &data->buffer.token[data->buffer.length-1], NOT_VARIALBLE, 0)) {
                    return ERR_INTERNAL;
                }
            }
            return SYNTAX_OK;

        case (REDUCE):
            while (stack.top->stop != 1){
                if (stack_pop(&stack))
                    return ERR_INTERNAL;
            }
            if (token.type == TYPE_FLOAT || token.type == TYPE_INTEGER || token.type == TYPE_STRING || token.type == TYPE_VARIABLE_ID) {
                if (stack_push(&stack, &data->buffer.token[data->buffer.length-1], VARIALBLE, 1)) {
                    return ERR_INTERNAL;
                }
            }else{
                if (stack_push(&stack, &data->buffer.token[data->buffer.length-1], NOT_VARIALBLE, 0)) {
                    return ERR_INTERNAL;
                }
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
int check_expression(Token_struct token, Syntactic_data_ptr data, int inside_par){   ///ADD NEW TOKEN
    printf("TOKEN : %d\n",token.type);
    Stack stack;
    init_stack(&stack);

    /// Pushing end $ on stack
    Token_struct dollar;
    if (stack_push(&stack, &dollar, E_$, 1))
        return ERR_INTERNAL;


    unsigned long previous = data->buffer.length - 2;

    /// Pushing if previous token was STRING/FLOAT/INTEGER/VAR_ID
    if (data->buffer.token[previous].type == TYPE_STRING || data->buffer.token[previous].type == TYPE_FLOAT || data->buffer.token[previous].type == TYPE_INTEGER || data->buffer.token[previous].type == TYPE_VARIABLE_ID){
        printf("DATA != =\n");
        if (stack_push(&stack, &data->buffer.token[previous], VARIALBLE, 1)) {
            return ERR_INTERNAL;
        }

        if (check_expParse(stack, token, data))
            return ERR_INTERNAL;

    }
    else {
        /// Pushing incoming token on stack - checking
        if (check_valid_char(token)) {
            free_stack(&stack);
            return ERR_SYNTAX;
        }
        if (token.type == TYPE_FLOAT || token.type == TYPE_INTEGER || token.type == TYPE_STRING || token.type == TYPE_VARIABLE_ID) {
            if (stack_push(&stack, &data->buffer.token[data->buffer.length-1], VARIALBLE, 1)) {
                return ERR_INTERNAL;
            }
        }else{
            if (stack_push(&stack, &data->buffer.token[data->buffer.length-1], NOT_VARIALBLE, 0)) {
                return ERR_INTERNAL;
            }
        }
    }

    int par_counter = 0;
    if (inside_par)
        par_counter -=1;

    printf("STACK TOP BEFORE : %d\n",stack.top->token->type);

    token = Get_token(data);

    while (!((stack.top->relation == E_$ || (stack.top->relation == VARIALBLE && stack.top->next->relation == E_$)) && (token.type == TYPE_SEMICOLON || (token.type == TYPE_PAR_RIGHT && par_counter == 0)) )){
        printf("STACK TOP : %d\n",stack.top->token->type);
        if (check_valid_char(token)) {
            free_stack(&stack);
            return ERR_SYNTAX;
        }

        printf("SPRACUVAVAM TOKEN : %d\n", token.type);
        if (token.type == TYPE_PAR_RIGHT)
            par_counter -= 1;
        else if (token.type == TYPE_BRACE_LEFT)
            par_counter += 1;

        if (check_expParse(stack, token, data)) {
            free_stack(&stack);
            return ERR_SYNTAX;
        }

        token = Get_token(data);
        printf("SPRACUVAVAM TOKEN PO VYP: %d\n", token.type);

    }
    // printf("\nNA zasobniku : %d ", stack.top->token->type);
    //   printf("\nNA zasobniku : %d", stack.top->next->relation);
    printf("KONEC");
    free_stack(&stack);
    return SYNTAX_OK;
}


