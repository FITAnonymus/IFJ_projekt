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
#include <stdbool.h>



///LABEL STORING BUSINESS
//Label* top = NULL; /// initialization of label list //TODO MOVE TO SYNTACTIC DATA
//
//int pop_label() {
//
//    if (top == NULL) {
//        return -1; ///stack underflow (err_internal cant be used because of possible conflict with temp_id
//    } else {
//        struct Label *temp = top;
//        int temp_id = top->id;
//        top = top->next;
//        free(temp);
//        return temp_id;
//    }
//}
//
//int push_label(int value) {
//    struct Label *newLabel;
//    newLabel = (struct Label *)malloc(sizeof(struct Label));
//    if(!newLabel){return ERR_INTERNAL;}
//    newLabel->id = value;
//    if (top == NULL) {
//        newLabel->next = NULL;
//    } else {
//        newLabel->next = top;
//    }
//    top = newLabel;
//    return 0;
//}
/////LABEL STORING BUSINESS

int generator(Syntactic_data_ptr data) {
    generate_start();
    bool in_while;
    bool in_if;
    bool in_fun;
    int i = 0;

    GF = true;

    while(i < (*data).buffer.length){///main generating loop
       ///based on the first type of the token determine which structure to generate
       switch((*data).buffer.token[i]->type){

           case(KEYWORD_FUNCTION): ///FUNCTION DECLARATION
               /// generate label with function name
               printf("LABEL ");
               i++; ///skipping keyword
               print_string((*data).buffer.token[i]->buf);
               in_fun= true;
               LF=true; GF=false; TF=false;  ///just for sure
               ///pracovat parametry
               end();
               break;

           case(TYPE_FUNCTION_ID): ///FUNCTION CALLING
               ///CREATEFRAME
               ///PUSH PARAMS
               printf("budu generovat volani fce");
               break;

           case(KEYWORD_WHILE): ///start of while, generate new label,  generate condition
               /// CREATEFRAME
               in_while = true;  //label handling
               break;

           case(KEYWORD_IF): ///start of if, generate new label,  generate condition
               in_if = true;
               break;

           case(KEYWORD_STRING):    ///POSSIBLE STARTS OF EXPRESSIONS
           case(KEYWORD_STRING_Q):
           case(KEYWORD_INT):
           case(KEYWORD_INT_Q):
           case(KEYWORD_FLOAT):
           case(KEYWORD_FLOAT_Q):
           case(TYPE_VARIABLE_ID):
               if((*data).buffer.token[i]->type != TYPE_VARIABLE_ID ){ ///skiping declaration for already defined variable
                   printf("DEFVAR ");
                   i++; ///skipping keyword
                   ///name of the variable
                   print_frame(); ///frame@
                   print_string((*data).buffer.token[i]->buf); ///name from the buffer
                   end(); ///end of instruction
               }
//               ///this if is for case when a keyword is used to define return type of function
//               if((*data).buffer.token[i+2]->type != TYPE_VARIABLE_ID){ break; }   ///this case must handle function definition

               printf("MOVE ");
               print_frame(); ///frame@
               print_string((*data).buffer.token[i]->buf); ///name from the buffer
               i++; //skip =
               i++; //next arg
               printf(" "); ///space between arguments
               if((*data).buffer.token[i]->type == TYPE_INTEGER){ ///INTEGER CONSTANT
                   printf("int@");
                   print_string((*data).buffer.token[i]->buf);///value of the int constant
                   end(); ///end of instruction
               }
               else if((*data).buffer.token[i]->type == TYPE_FLOAT){ ///FLOAT CONSTANT
                   printf("float@");
                   print_float((*data).buffer.token[i]->buf);///value of the float constant
                   end(); ///end of instruction
               }
               else if((*data).buffer.token[i]->type == TYPE_STRING){ ///STRING CONSTANT
                   printf("string@");
                   print_float((*data).buffer.token[i]->buf);///value of the string constant
                   end(); ///end of instruction
               }
               else if((*data).buffer.token[i]->type == TYPE_VARIABLE_ID){ ///STRING CONSTANT
                   print_frame(); ///frame@
                   print_string((*data).buffer.token[i]->buf); ///name from the buffer
                   end(); ///end of instruction
               }
               ///HANDLING AN ARITHMETIC OPERATION AFTER DECLARATION
               if((*data).buffer.token[i+1]->type == TYPE_MUL || (*data).buffer.token[i+1]->type == TYPE_MINUS || (*data).buffer.token[i+1]->type == TYPE_PLUS || (*data).buffer.token[i+1]->type == TYPE_DIV ){
                   if((*data).buffer.token[i+1]->type == TYPE_MUL){
                   }
                   else if((*data).buffer.token[i+1]->type == TYPE_MINUS){

                   }
                   else if((*data).buffer.token[i+1]->type == TYPE_PLUS){

                   }
                   else if((*data).buffer.token[i+1]->type == TYPE_DIV){

                   }
               }
               break;

           case (TYPE_BRACE_RIGHT): ///end of if er while => generate end label
               if(in_if){
                   // gen_else(data); ///end of if begining of else
                   ///if posledni v if listu TODO
                   in_if = false;

               }
               if(in_while && !in_if){///truly end of while (not end of if in while)
                   // gen_end_while(data);
                   ///if posledni v while listu TODO
                   in_while = false;
               }
               if(in_fun && !in_while && !in_if){
                    ///print return = schluss vic nic je jedno jestli je vnoren anebo ne proste printni return a chod do
               }

               break;

           default:

               break;
       }
       i++;
    }
   return 0;
 }

//int gen_if(Syntactic_data_ptr data){
//
//}
//
//int gen_else(Syntactic_data_ptr data){
//
//}
//
//int gen_while(Syntactic_data_ptr data){
//
//}
//
//void gen_end_while(Syntactic_data_ptr data){
//
//}
//
//int gen_function(Syntactic_data_ptr data){
//   label = function name, at the end of the function print return
//}
//
//int gen_call_function(Syntactic_data_ptr data){
// NAPUSHUUJN PARAMETRY jump lALBEL, MOVE RETVAL FROM TF;
//}
//
//int generate_label(Syntactic_data_ptr data, int index){
//
//}
//
//int generate_condition(Syntactic_data_ptr data){
//
//}
//
void generate_start(){
    ///.IFJcode22
    printf("#   CILOVY K0D IFJcode22   \n");
    printf(".IFJcode22\n");
    return;
}
//
//void generate_end(){ ///probably superfluous function
//    ///EXIT ⟨symb⟩ -- not needed purpose of this is error-handling
//}
//
//void print_string(){
//
//}

void print_frame(){
    if(GF){printf("GF");}
    else if(LF){printf("LF");}
    else if(TF){printf("TF");}

    printf("@");
    return;
}

void end(){
    printf("\n");
}

void print_string(Buffer *buf){
    for(int i =0; buf->buf[i] != '\0'; i++){
        printf("%c", buf->buf[i]);
    }
    return;
}
void print_float(Buffer *buf){
    for(int i =0; buf->buf[i] != '\0'; i++){
        printf("%c", buf->buf[i]);
    }
    return;
}