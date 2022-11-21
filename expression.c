//
// Created by gorge on 21.11.22.
//

#include "expression.h"
#include "syntactic.h"


const int PTable[][] = {
//
//             {x}       {/}      {+}      {-}      {.}      {<}      {>}     {<=}      {>=}    {===}     {!==}     {(}    {)}     {TYPE}    {$}
/*  {x}  */ { E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/*  {/}  */ { E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/*  {+}  */ { E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/*  {-}  */ { E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/*  {.}  */ { E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/*  {<}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/*  {>}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/* {<=}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/* {>=}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_EQUAL, E_EQUAL, E_CLOSE, E_CLOSE, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/* {===} */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/* {!==} */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_EQUAL, E_EQUAL, E_OPEN, E_CLOSE, E_OPEN, E_OPEN },
/*  {(}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN, E_EQUAL, E_OPEN, E_EMPTY},
/*  {)}  */ { E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE,E_EMPTY, E_CLOSE,E_EMPTY, E_CLOSE},
/* {TYPE}*/ { E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE, E_CLOSE,E_EMPTY, E_CLOSE,E_EMPTY, E_CLOSE},
/*  {$}  */ { E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN , E_OPEN ,E_OPEN , E_EMPTY, E_OPEN, E_END  },
};

int check_expression(Token_struct token, Syntactic_data_ptr data){
    return 0;
}
