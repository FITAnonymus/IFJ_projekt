/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Code generator implementation.
    *
    *
    */

#include "generator.h"
#include <string.h>
#include <stdio.h>
#include "syntactic.h"


///LABEL STORING BUSINESS
Label* top = NULL; /// initialization of label list //TODO MOVE TO SYNTACTIC DATA

int pop_label() {

    if (top == NULL) {
        return -1; ///stack underflow (err_internal cant be used because of possible conflict with temp_id
    } else {
        struct Label *temp = top;
        int temp_id = top->id;
        top = top->next;
        free(temp);
        return temp_id;
    }
}

int push_label(int value) {
    struct Label *newLabel;
    newLabel = (struct Label *)malloc(sizeof(struct Label));
    if(!newLabel){return ERR_INTERNAL;}
    newLabel->id = value;
    if (top == NULL) {
        newLabel->next = NULL;
    } else {
        newLabel->next = top;
    }
    top = newLabel;
    return 0;
}
///LABEL STORING BUSINESS

int generator(syntactic_data_ptr data){
    ///based on the first type of the token determine which structure to generate
    switch((*data)->buffer.token[0]->type){

        case(KEYWORD_FUNCTION): ///FUNCTION DECLARATION
            break;

        case(TYPE_FUNCTION_ID): ///FUNCTION CALLING
            break;

        case(KEYWORD_WHILE): ///start of while, generate new label,  generate condition
            break;

        case(KEYWORD_IF): ///start of if, generate new label,  generate condition
            break;

        case(KEYWORD_STRING):    ///POSSIBLE STARTS OF EXPRESSIONS
        case(KEYWORD_STRING_Q):
        case(KEYWORD_INT):
        case(KEYWORD_INT_Q):
        case(KEYWORD_FLOAT):
        case(KEYWORD_FLOAT_Q):
        case(TYPE_VARIABLE_ID):


            break;
        case (TYPE_BRACE_LEFT): ///end of if er while => generate end label
            break;
        default:

            break;
    }
}

int gen_if(syntactic_data_ptr data){

}

int gen_else(syntactic_data_ptr data){}

int gen_while(syntactic_data_ptr data){

}

void gen_end_while(syntactic_data_ptr data){

}

int gen_function(syntactic_data_ptr data){

}

int gen_call_function(syntactic_data_ptr data){

}

int generate_label(syntactic_data_ptr data, int index){

}

int generate_condition(syntactic_data_ptr data){

}

void generate_start(){

}

void generate_end(){

}

