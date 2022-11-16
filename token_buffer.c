/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of supportive data structure Token_buffer for syntax analysis
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */
#include "token_buffer.h"

int init_token_buffer(Token_buffer *tok_buf){
    tok_buf->lenght = 0;
    tok_buf->size =0;
    tok_buf->token = NULL;
    return 0;

}

int add_token_buffer(token_struct *token,Token_buffer *tok_buf){

}

int free_token_buffer(Token_buffer *tok_buf){

}