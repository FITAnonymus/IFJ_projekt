/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Code generator implementation.
    *
    *
    */

#include "generator.h"
#include <stdbool.h>
#include "token_buffer.h"

void print_start(){
    printf(".IFJcode22\n");
    return;
}
int process_tok_buf(Token_buffer * tok_buf){
    print_start();
    ///frame indicators - to track in which frame mode the code is
    bool LF;
    bool GF;
    bool TF;

    for(int i=0; i < tok_buf->lenght; i ++){

        switch(tok_buf[i].token->type){

            case(KEYWORD_INT): ///declaration of int
                printf("DEFVAR"); i++;
                print_buffer(tok_buf[i].token->buf); i++; ///print name of the variable
                printf("\n"); ///end of instruction
                break;
            case():
                break;
        }

    }

    return 0;
}