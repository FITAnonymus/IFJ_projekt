/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *

    * @brief Implementation of supportive data structure Token_buffer for syntactic analysis

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

int add_token_buffer(token_struct token,Token_buffer *tok_buf){
    if(tok_buf->lenght +1 >= tok_buf->size) {

        unsigned int size_to_alloc = (tok_buf->lenght + sizeof(token_struct));///one more cell
        //printf("new size\n");//todo
        tok_buf->token = (token_struct *) realloc((void * )tok_buf->token, size_to_alloc); /// try to alloc the cell
        //printf("realloc ok\n");//todo
        if (tok_buf->token == NULL) { return ERR_INTERNAL; }/// check if allocation was successful

        tok_buf->size = size_to_alloc;///new size of buffer
    }

    tok_buf->lenght++;
    tok_buf->token[tok_buf->lenght - 1] = token; ///new token added to token array
    return 0;
}

void free_token_buffer(Token_buffer *tok_buf){
   free(tok_buf);

}