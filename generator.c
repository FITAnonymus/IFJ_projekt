/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Code generator implementation.
    *
    *
    */

#include "generator.h"
#include <stdbool.h>
#include <stdio.h>

void print_start(){
    printf(".IFJcode22\n");
    return;
}
///handling arithmetic expression with parenthesis and different priotity of operators
void handle_expression(Token_buffer * tok_buf, int index ){

}
/////generating and storing labels
//int generate_label(Token_buffer * tok_buf, int index ){
//
//}
///generating and processing condition of if
int condition_gen_check(Token_buffer * tok_buf, int index){
    if(tok_buf[index+1].token->type == TYPE_COMPARE){
        ///print equal
        print_buffer(tok_buf[index].token->buf); ///first operand
        ///print zbytek operandu
        ///print jump
        ///prejit zpet at se doplni label
    }
    else if(tok_buf[index+1].token->type == TYPE_LOWER){

    }
    else if(tok_buf[index+1].token->type == TYPE_GREATER){

    }
    else if(tok_buf[index+1].token->type == TYPE_COMPARE_NEG){

    }
    else if(){

    }

}

void handle_operation(Token_buffer * tok_buf, int index){
    ///arithmetic operations
    if (tok_buf[index+1].token->type == TYPE_MUL){ ///after first operand is multiplication
        printf("MUL ");
        print_frame(GF, LF, TF);
        printf("%dTMP_VAR ", index); ///
        print_buffer(tok_buf[index]->buf);///first operand of mul
        printf(" ");
        print_buffer(tok_buf[index +3]->buf); ///second operand of mul
        printf("\n"); ///end of instruction
    }
    else if(tok_buf[index+1].token->type == TYPE_DIV){
        printf("DIV ");
        print_frame(GF, LF, TF);
        printf("%dTMP_VAR ", index); ///
        print_buffer(tok_buf[index]->buf);///first operand of div
        printf(" ");
        print_buffer(tok_buf[index +3]->buf); ///second operand of div
        printf("\n"); ///end of instruction
    }
    else if(tok_buf[index+1].token->type == TYPE_PLUS){
        printf("ADD ");
        print_frame(GF, LF, TF);
        printf("%dTMP_VAR ", index); ///
        print_buffer(tok_buf[index]->buf);///first operand of div
        printf(" ");
        print_buffer(tok_buf[index +3]->buf); ///second operand of div
        printf("\n"); ///end of instruction
    }
    else if(tok_buf[index+1].token->type == TYPE_MINUS){
        printf("SUB ");
        print_frame(GF, LF, TF);
        printf("%dTMP_VAR ", index); ///git
        print_buffer(tok_buf[index]->buf);///first operand of sub
        printf(" ");
        print_buffer(tok_buf[index +3]->buf); ///second operand of sub
        printf("\n"); ///end of instruction
    } ///logical operations
    else if(tok_buf[index+1].token->type == TYPE_LOWER){
        printf("LT ");
        print_frame(GF, LF, TF);
        printf("%dTMP_VAR ", index); ///
        print_buffer(tok_buf[index]->buf);///first operand of lower
        printf(" ");
        print_buffer(tok_buf[index +3]->buf); ///second operand of lower
        printf("\n"); ///end of instruction
    }
    else if(tok_buf[index+1].token->type == TYPE_GREATER){
        printf("GT ");
        print_frame(GF, LF, TF);
        printf("%dTMP_VAR ", index); ///
        print_buffer(tok_buf[index]->buf);///first operand of greater
        printf(" ");
        print_buffer(tok_buf[index +3]->buf); ///second operand of greater
        printf("\n"); ///end of instruction
    }
}

void print_frame(bool GF, bool LF, bool TF){
    if (GF){printf("GF");}  ///print frame
    else if(LF){printf("LF");}
    else if(TF){printf("TF");}
    printf("@");
    return;
}
int process_tok_buf(Token_buffer * tok_buf){
    print_start();
    ///frame indicators - to track in which frame mode the code is
    bool LF = false;
    bool GF = true; ///global is default
    bool TF = false;
    long unsigned i;
    for( i=0; i < tok_buf->lenght; i++){

            switch(tok_buf[i].token->type){

                case KEYWORD_INT:   ///for all these keywords we will declare a variable with and possibly define the value
                case KEYWORD_FLOAT:
                case KEYWORD_FLOAT_Q:
                case KEYWORD_INT_Q:
                case KEYWORD_STRING:
                case KEYWORD_STRING_Q:
                    printf("DEFVAR "); i++;

                    print_frame(GF, LF, TF);
                    print_buffer(tok_buf[i].token->buf); ///print name of the variable example

                    if(tok_buf[i+1].token->type == TYPE_ASSIGN){ ///just assigning value
                        printf("\n"); ///end of instruction
                        printf("MOVE ");
                        print_frame(GF, LF, TF);
                        print_buffer(tok_buf[i].token->buf); ///print name of the variable
                        printf(" "); ///space between var and symb
                        print_buffer(tok_buf[i+2].token->buf);///symb
                        printf("\n"); ///end of instruction
                        i=i+3; ///skip assign, value, semicolon
                    }
                    else{
                        i++;///skipping semicolon
                        printf("\n"); ///end of instruction
                    }

                    ///the value after asssign will be skipped automaticaly (see next case)
                    break;

                case(TYPE_VARIABLE_ID): ///assigning
                    printf("MOVE ");
                    print_frame(GF, LF, TF);
                    print_buffer(tok_buf[i].token->buf); ///variable name printed
                    printf(" ");
                    print_buffer(tok_buf[i+2].token->buf); ///variable name printed
                    printf("\n");
                    ///TODO///handle expression
                case (KEYWORD_IF):
                    ///generate label  - label for else - kdyz else + label to skip else
                    ///condition gen + check
                    break;
                case(KEYWORD_WHILE):
                    /// podobne jak if
                    break;
                case(KEYWORD_FUNCTION):
                    ///deklaruj funkci
                    break;
                case(TYPE_FUNCTION_ID):
                    ///zavolej funkci
                default:
                    ///nerob nic a nacitej dal
                  break;
            }

    }

  return 0;
}