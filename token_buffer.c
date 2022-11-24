/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *

    * @brief Implementation of supportive data structure Token_buffer for syntactic analysis

    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include <stdlib.h>
#include "error.h"
#include "buffer.h"
#include "expression.h"
//#include <stdio.h>

Token_buffer* init_token_buffer(){
    Token_buffer * tok_buf = malloc(sizeof(Token_buffer));
    tok_buf->token = NULL;
    tok_buf->length = 0;
    tok_buf->size = sizeof(Token_buffer * );  ///change
    return tok_buf;
}

int add_token_buffer(Token_struct token,Token_buffer *tok_buf){
    if( tok_buf == NULL){
        if(tok_buf->length + 1 >= tok_buf->size) {

            unsigned int size_to_alloc = (tok_buf->size + sizeof(Token_struct));///one more cell

            tok_buf->token = (Token_struct *) realloc((Token_struct *)tok_buf->token, size_to_alloc); /// try to alloc the cell

            if (tok_buf->token == NULL) { return ERR_INTERNAL; }/// check if allocation was successful

            tok_buf->size = size_to_alloc;///new size of buffer
        }

        tok_buf->token[tok_buf->length] = token; ///new token added to token array
        tok_buf->length++;
        return 0;
    }
    //printf("preco mi davate null do tok_buf?(add_token_buffer)\n");
    return ERR_INTERNAL;

}

void free_token_buffer(Token_buffer *tok_buf) {
    free(tok_buf->token);
    tok_buf = NULL;

}
