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

//TODO Popis jazyka - done
//todo interpret ok
//


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
    printf("jsem, v genratoru\n");
    bool in_while = false;
    bool in_if = false;
    int i;
    for (i = 0; i < (*data).buffer.length; i++) {
        printf("token %d\n", (*data).buffer.token[i]->type);
        printf("i: %d\n", i);
    }
    printf("after for\n");
    return;
}
//   while((*data).buffer.token[i]->type != TYPE_EOF){///main generating loop
//       printf("smycka %d", i);
//       ///based on the first type of the token determine which structure to generate
//       switch((*data).buffer.token[i]->type){
//
//           case(KEYWORD_FUNCTION): ///FUNCTION DECLARATION
//               /// generate label with function name
//               printf("budu generovat volani fce");
//               break;
//           case(TYPE_PROLOG_START): ///FUNCTION DECLARATION
//               printf("prolog ti generovat nebudu vole\n");
//               break;
//
//           case(TYPE_FUNCTION_ID): ///FUNCTION CALLING
//               ///CREATEFRAME
//               printf("budu generovat volani fce");
//               break;
//
//           case(KEYWORD_WHILE): ///start of while, generate new label,  generate condition
//               /// CREATEFRAME
//               in_while = true;  //label handling
//               break;
//
//           case(KEYWORD_IF): ///start of if, generate new label,  generate condition
//               in_if = true;
//               break;
//
//           case(KEYWORD_STRING):    ///POSSIBLE STARTS OF EXPRESSIONS
//           case(KEYWORD_STRING_Q):
//           case(KEYWORD_INT):
//           case(KEYWORD_INT_Q):
//           case(KEYWORD_FLOAT):
//           case(KEYWORD_FLOAT_Q):
//           case(TYPE_VARIABLE_ID):
//
//
//               break;
//           case (TYPE_BRACE_RIGHT): ///end of if er while => generate end label
//               if(in_if){
//                   // gen_else(data); ///end of if begining of else
//                   ///if posledni v if listu TODO
//                   in_if = false;
//
//               }
//               if(in_while && !in_if){///truly end of while (not end of if in while)
//                   // gen_end_while(data);
//                   ///if posledni v while listu TODO
//                   in_while = false;
//               }
//                  if(in_fun && !in_while && !in_if){
//                    ///print return = schluss vic nic je jedno jestli je vnoren anebo ne proste printni return a chod do
//                 }
////
//               break;
//           default:
//             printf("samo nedojebal\n");
//               break;
//       }
//      i++;
//    }
//   printf("za  smyckou\n");
//}
//
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
//
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
//void generate_start(){
//    ///.IFJcode22
//    ///CLEARS
//
//}
//
//void generate_end(){
//    ///EXIT ⟨symb⟩
//}
//
//void print_string(){
//
//}
//
