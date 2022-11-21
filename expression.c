//
// Created by gorge on 21.11.22.
//

#include "expression.h"
#include "syntactic.h"
#include "error.h"


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

