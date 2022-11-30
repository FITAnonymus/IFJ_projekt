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

int generator(Syntactic_data_ptr data) {

    generate_start();
    print_main(data);
    bool in_while;
    bool in_if;
    bool in_fun;
    ///init while and if stack
    ///
    int i = 0;

    GF = true;

    while(i < (*data).buffer.length){///main generating loop
       ///based on the first type of the token determine which structure to generate
       switch((*data).buffer.token[i]->type){

           case(KEYWORD_FUNCTION): ///FUNCTION DECLARATION
               in_fun= true;
               LF=true; GF=false; TF=false;  ///just for sure
               /// generate label with function name
               printf("LABEL ");
               i++;                     ///skipping keyword
               print_string((*data).buffer.token[i]->buf);
               end();
               if(cmp_string_buffer("main",(*data).buffer.token[i]->buf )){
                   printf("CREATEFRAME");
                   end();
               }
               printf("PUSHFRAME");
               end();
               printf("DEFVAR LF@%%retval1");
               printf("MOVE LF@%%retval1 nil@nil");
               int param_count = 1;
               while((*data).buffer.token[i]->type != TYPE_BRACE_RIGHT) { ///while arguments define them and move them values

                   if((*data).buffer.token[i]->type == TYPE_STRING || (*data).buffer.token[i]->type == TYPE_FLOAT ||(*data).buffer.token[i]->type == TYPE_INTEGER ){
                       printf("DEFVAR ");
                       print_frame();
                       printf("param%d",param_count);
                       end();
                       printf("MOVE ");
                       print_frame();
                       printf("%%%d", param_count);
                       end();
                       param_count++;
                   }
                   else{///brace left, comma
                     ///do nothing
                   }
                   i++;
               }

               end();
               break;

           case(TYPE_FUNCTION_ID): ///FUNCTION CALLING /// y = foo(10, "Hi X!")
               printf("CREATEFRAME");
               end();
               int par_count = 1;
               int start_index = i;
               while((*data).buffer.token[i]->type != TYPE_BRACE_RIGHT) { ///while arguments define them and move them values

                   if((*data).buffer.token[i]->type == TYPE_INTEGER){ ///INTEGER CONSTANT
                       printf("DEFVAR "); ///defining the parameter
                       printf(" ");
                       printf("TF@"); ///not using print frame because we want to store the value of the frame from previous calling in case of variable
                       printf("%%%d", par_count);
                       end();
                       printf("MOVE ");
                       print_frame();            ///parameter name
                       printf("%%%d", par_count);
                       printf(" ");
                       printf("int@");    ///value of the parameter
                       print_string((*data).buffer.token[i]->buf);///value of the int constant
                       end(); ///end of instruction
                       par_count++;
                   }
                   else if((*data).buffer.token[i]->type == TYPE_FLOAT){ ///FLOAT CONSTANT
                       printf("DEFVAR "); ///defining the parameter
                       printf(" ");
                       printf("TF@%%");
                       printf("%%%d", par_count);
                       end();
                       printf("MOVE ");
                       print_frame();            ///parameter name
                       printf("%%%d", par_count);
                       printf(" ");
                       printf("float@");    ///value of the parameter
                       print_string((*data).buffer.token[i]->buf);///value of the float constant
                       end(); ///end of instruction
                       par_count++;
                   }
                   else if((*data).buffer.token[i]->type == TYPE_STRING){ ///STRING CONSTANT
                       printf("DEFVAR "); ///defining the parameter
                       printf(" ");
                       printf("TF@%%");
                       printf("%%%d", par_count);
                       end();
                       printf("MOVE ");
                       print_frame();            ///parameter name
                       printf("%%%d", par_count);
                       printf(" ");
                       printf("string@");    ///value of the parameter
                       print_string((*data).buffer.token[i]->buf);///value of the float constant
                       end(); ///end of instruction
                       par_count++;
                   }
                   else if((*data).buffer.token[i]->type == TYPE_VARIABLE_ID){ ///STRING CONSTANT
                       printf("DEFVAR "); ///defining the parameter
                       printf(" ");
                       printf("TF@%%");
                       printf("%%%d", par_count);
                       end();
                       printf("MOVE ");
                       print_frame();            ///parameter name
                       printf("%%%d", par_count);
                       printf(" ");
                       print_frame(); ///frame@  ///value of the parameter
                       print_string((*data).buffer.token[i]->buf);///value of the float constant
                       end(); ///end of instruction
                       par_count++;
                   }
                   else{///brace left, comma

                   }
                   i++;
               }
               printf("CALL");
               print_string((*data).buffer.token[i]->buf);
               end();
               printf("MOVE ");
               print_frame();
               print_string((*data).buffer.token[start_index -2]->buf);/// Y = fun_id (fun_if = start_index)
               printf(" ");
               printf("TF@%%retval1");
               end();
               break;

           case(KEYWORD_WHILE): ///start of while, generate new label,  generate condition
               //TODO
               in_while = true;
               generate_condition(data, i);
               generate_label(data, i);
               ///print label
               ///add label to list
               break;

           case(KEYWORD_IF): ///start of if, generate new label,  generate condition
               ///TODO
               in_if = true;
               generate_condition(data, i);
               generate_label(data, i);
               ///print label
               ///add label to list
               break;

           case(KEYWORD_STRING):    ///POSSIBLE STARTS OF EXPRESSIONS
           case(KEYWORD_STRING_Q):
           case(KEYWORD_INT):
           case(KEYWORD_INT_Q):
           case(KEYWORD_FLOAT):
           case(KEYWORD_FLOAT_Q):
           case(TYPE_VARIABLE_ID):

               if((*data).buffer.token[i+2]->type != TYPE_FUNCTION_ID){ ///assignment of function return value  Y = fun_id (fun_if = start_index)
                   printf("DEFVAR ");
                   i++; ///skipping keyword
                   ///name of the variable
                   print_frame(); ///frame@
                   print_string((*data).buffer.token[i]->buf); ///name from the buffer
                   end(); ///end of instruction

                   i++; ///skip assign the while loop will continue to the case of function id
               }
              else if((*data).buffer.token[i]->type != TYPE_VARIABLE_ID ){ ///skiping declaration for already defined variable
                   printf("DEFVAR ");
                   i++; ///skipping keyword
                   ///name of the variable
                   print_frame(); ///frame@
                   print_string((*data).buffer.token[i]->buf); ///name from the buffer
                   end(); ///end of instruction
               }else{                                                  ///basic assignment of variable or  value
                   printf("MOVE ");
                   print_frame(); ///frame@
                   print_string((*data).buffer.token[i]->buf); ///name from the buffer
                   i++; //skip =
                   i++; //next arg
                   printf(" "); ///space between arguments
                   print_operand(data, i);

               }

               break;

           case (TYPE_BRACE_RIGHT): ///end of if er while => generate end label
               if(in_if){
                   // gen_else(data); ///end of if begining of else
                   ///if posledni v if listu TODO
                   ///if(if_stack->stack_label->next == NULL)
                   in_if = false;

               }
               else if(in_while && !in_if){///truly end of while (not end of if in while)
                   // gen_end_while(data);
                   ///if posledni v while listu TODO
                   ///if(while_stack->stack_label->next == NULL)
                   in_while = false;
               }
               ///else not needed generator is in the end end of function which was already handled by keyword return

               break;

           case(KEYWORD_RETURN):

               printf("MOVE LF@%%retval1 ");
               print_string((*data).buffer.token[i+1]->buf); ///name ot the return value
               end();
               printf("POPFRAME");
               end();
               printf("RETURN");
               end();
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
void print_operand(Syntactic_data_ptr data, int i){

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
    return;
}
int generate_label(Syntactic_data_ptr data, int index){
    return index;
}
int generate_condition(Syntactic_data_ptr data, int index){

//    GT GF@res GF@a int@0
//    JUMPIFNEQ $main$if$1$else GF@res bool@true
   printf("DEFVAR ");
   print_frame();
   printf("RESULT");
   end();
   ///switcch
    print_operand(data, i);
    printf(" ");
    print_operand(data, i+2);
   end();
   printf("JUMPIFNEQ ");
   printf("%d ", index);
    print_frame();
    printf("RESULT");
    printf(" ");
    printf("bool@true");
    end();

}

void generate_start(){
    printf("#   CILOVY K0D IFJcode22   \n");
    printf(".IFJcode22\n");
    return;
}

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

void print_main(Syntactic_data_ptr data){
    int j =0;
    while (j < (*data).buffer.length);
    {
        if((*data).buffer.token[j]->type == TYPE_FUNCTION_ID){
           if(cmp_string_buffer("main",(*data).buffer.token[j]->buf)==0){
               printf("JUMP ");
               print_string((*data).buffer.token[j]->buf);
               end();
               return;
           }
        }
    }
}


int stack_pop_label(Generator_stack * stack){
    if(stack->top == NULL){
        return -1;
    }

    int result = stack->top->label; ///preparing return value

    Stack_label *to_delete = stack->top; ///deleting first item
    stack->top = stack->top->next; ///keeping the link
    free(to_delete);
    to_delete = NULL;

    return result;
}

int stack_push_label(Generator_stack * stack, int label){

    Stack_label *new = (Stack_label *)malloc(sizeof(Stack_label )); ///allocation of new item
    if(!new){
        return ERR_INTERNAL; ///malloc fail
    }

    new->next = stack->top; ///keeping the links
    stack->top = new;

    new->label = label; ///assigning new value

    return TOKEN_OK;
}

void free_label_stack(Generator_stack * stack){

    if(stack == NULL){
        return;
    }
    while(stack->top != NULL){ ///while stack isn not empty
        Stack_label * to_delete = stack->top; ///prepare item to delete
        stack->top = stack->top->next; ///keep the links
        free(to_delete);  ///delete the item
    }
    stack = NULL; ///deleting finished
    return;
}
