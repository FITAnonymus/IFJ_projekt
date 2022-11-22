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


int check_expParse(stack stack, Syntactic_data_ptr data);

const int PTable[17][16] = {
//
//             {x}       {/}      {+}      {-}      {.}      {<}      {>}     {<=}      {>=}    {===}     {!==}     {(}    {)}     {TYPE}  {NONE}    {$}
/*  {x}  */ { equal, equal, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, push, reduce, push, undefined, push },
/*  {/}  */ { equal, equal, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, push, reduce, push, undefined,push },
/*  {+}  */ { push , push , equal, equal, equal, reduce, reduce, reduce, reduce, reduce, reduce, push, reduce, push, undefined,push },
/*  {-}  */ { push , push , equal, equal, equal, reduce, reduce, reduce, reduce, reduce, reduce, push, reduce, push, undefined,push },
/*  {.}  */ { push , push , equal, equal, equal, reduce, reduce, reduce, reduce, reduce, reduce, push, reduce, push, undefined,push },
/*  {<}  */ { push , push , push , push , push , equal, equal, equal, equal, reduce, reduce, push, reduce, push, reduce,push },
/*  {>}  */ { push , push , push , push , push , equal, equal, equal, equal, reduce, reduce, push, reduce, push, reduce,push },
/* {<=}  */ { push , push , push , push , push , equal, equal, equal, equal, reduce, reduce, push, reduce, push, reduce,push },
/* {>=}  */ { push , push , push , push , push , equal, equal, equal, equal, reduce, reduce, push, reduce, push, reduce,push },
/* {===} */ { push , push , push , push , push , push , push , push , push , equal, equal, push, reduce, push, reduce,push },
/* {!==} */ { push , push , push , push , push , push , push , push , push , equal, equal, push, reduce, push, reduce,push },
/*  {(}  */ { push , push , push , push , push , push , push , push , push , push , push , push, equal, push, undefined,undefined},
/*  {)}  */ { reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce,undefined, reduce,undefined, undefined,reduce},
/* {int}*/ { reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce,undefined, reduce,undefined, undefined,reduce},
/* {float}*/ { reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce,undefined, reduce,undefined, undefined,reduce},
/* {string}*/ { reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce, reduce,undefined, reduce,undefined, undefined,reduce},
/* {NONE}*/ { undefined, undefined, undefined, undefined, undefined, push , push , push , push , push , push ,undefined, reduce,undefined, undefined,push },
/*  {$}  */ { push , push , push , push , push , push , push , push , push , push , push ,push , undefined, push, reduce,end  },
};


//main function of expression control
int check_expression(Token_struct token, Syntactic_data_ptr data){
    stack stack;
    init_stack(&stack);
    stack.top->token = E_$;
    if (stack_push(&stack, &token) != 0){
        return ERR_INTERNAL;
    }
    while (stack.top->token != E_$){
        check_expParse(stack, data);
    }

    free_stack(&stack);
    return SYNTAX_OK;
}


//function to reduce terms on stack
int check_expParse(stack stack, Syntactic_data_ptr data){
    stack_item *item = stack_pop(&stack);

    while(item->type == term){
        if ()
    }

}

//reduce or not reduce
int relTable(stack_item item){

    switch (item.relation){
        case ()

    }
}



//function to prepare item
int TypeToTerm(stack_item item) {
    if (item.token->type == TYPE_DIV) {
        item.type = term;
        item.relation = MulDiv;
        return SYNTAX_OK;
    } else if (item.token->type == TYPE_MUL) {
        item.type = term;
        item.relation = MulDiv;
        return SYNTAX_OK;
    } else if (item.token->type == TYPE_MINUS) {
        item.type = term;
        item.relation = PlusMinus;
        return SYNTAX_OK;
    } else if (item.token->type == TYPE_PLUS) {
        item.type = term;
        item.relation = PlusMinus;
        return SYNTAX_OK;
    } else if (item.token->type == TYPE_GREATER || item.token->type == TYPE_LOWER ||
               item.token->type == TYPE_GREATER_EQ || item.token->type == TYPE_LOWER_EQ) {
        item.type = term;
        item.relation = GELE;
        return SYNTAX_OK;
    } else if (item.token->type == TYPE_COMPARE) {
        item.type = term;
        item.relation = equal;
        return SYNTAX_OK;
    } else if (item.token->type == TYPE_COMPARE_NEG) {
        item.type = term;
        item.relation = NotEqual;
        return SYNTAX_OK;
    } else if (item.token->type == TYPE_CONCAT) {
        item.type = term;
        item.relation = Concatenate;
        return SYNTAX_OK;
    }else if (item.token->type == TYPE_PAR_LEFT) {
        item.type = term;
        item.relation = LeftPar;
        return SYNTAX_OK;
    }else if (item.token->type == TYPE_PAR_RIGHT) {
        item.type = term;
        item.relation = RightPar;
        return SYNTAX_OK;
    }else if(item.token->type == TYPE_INTEGER || item.token->type == TYPE_STRING || item.token->type == TYPE_FLOAT){
        item.type = term;
        item.relation = Variable;
        return SYNTAX_OK;
    }else{
        item.relation = E_$;
        return SYNTAX_OK;
    }
}