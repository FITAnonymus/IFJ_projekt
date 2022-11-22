//
// Created by gorge on 21.11.22.
//

#include "expression.h"
#include "syntactic.h"
#include "syntactic_stack.h"

int check_expParse(stack stack, Syntactic_data_ptr data);

const int PTable[16][16] = {
//
//             {x}       {/}      {+}      {-}      {.}      {<}      {>}     {<=}      {>=}    {===}     {!==}     {(}    {)}     {TYPE}  {NONE}    {$}
/*  {x}  */ { E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_EMPTY, E_OPEN },
/*  {/}  */ { E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_EMPTY,E_OPEN },
/*  {+}  */ { E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_EMPTY,E_OPEN },
/*  {-}  */ { E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_EMPTY,E_OPEN },
/*  {.}  */ { E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_EMPTY,E_OPEN },
/*  {<}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_CLOSE,E_OPEN },
/*  {>}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_CLOSE,E_OPEN },
/* {<=}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_CLOSE,E_OPEN },
/* {>=}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_CLOSE,E_OPEN },
/* {===} */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_OPEN, E_CLOSE, E_OPEN, E_CLOSE,E_OPEN },
/* {!==} */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_OPEN, E_CLOSE, E_OPEN, E_CLOSE,E_OPEN },
/*  {(}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN, E_EQUAL, E_OPEN, E_EMPTY,E_EMPTY},
/*  {)}  */ { E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE,E_EMPTY, E_CLOSE,E_EMPTY, E_EMPTY,E_CLOSE},
/* {TYPE}*/ { E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE,E_EMPTY, E_CLOSE,E_EMPTY, E_EMPTY,E_CLOSE},
/* {NONE}*/ { E_EMPTY, E_EMPTY, E_EMPTY, E_EMPTY, E_EMPTY, E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN ,E_EMPTY, E_CLOSE,E_EMPTY, E_EMPTY,E_OPEN },
/*  {$}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN ,E_OPEN , E_EMPTY, E_OPEN, E_CLOSE,E_END  },
};

int check_valid_char(Token_struct token){
    switch(token.type){
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

        default: return 1
    }
    return 0;

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
    stack_item item = stack_pop(&stack);

    while(item.type == term){
        if ()
    }

}


int expression_definition(Syntactic_data_ptr data){

}

int check_expression(Token_struct token, Syntactic_data_ptr data){
    Token_struct token2 = Get_token(data);
    add_token_buffer(token2, data->buffer);

    if (token2.type == TYPE_ASSIGN){
        expression_definition(data);
    }
    else{
        if (check_valid_char(token2))
            return ERR_SYNTAX;
    }


    return SYNTAX_OK;
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