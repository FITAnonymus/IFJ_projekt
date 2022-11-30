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

    Generator_stack *if_stack;
    if_stack->top = NULL;
    Generator_stack *while_stack;
    while_stack->top = NULL;

    generate_start(); ///HEADER
    print_main(data);

    bool in_while;
    bool in_if;
    bool in_fun;

    int i = 0;

    GF = true;
    int check;
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
               in_while = true;
               printf("LABEL %d", generate_label(data, i)); ///Label while (insted of while id -which is unique)
               end();
               generate_condition(data, i);
               end();
               check = stack_push_label(while_stack ,generate_label(data, i));
               if(check){return ERR_INTERNAL;}
               break;

           case(KEYWORD_IF): ///start of if, generate new label,  generate condition
               in_if = true;
               printf("LABEL %d", generate_label(data, i));///Label if (insted of if id -which is unique)
               end();
               generate_condition(data, i);
               end();
               check = stack_push_label(if_stack ,generate_label(data, i));
               if(check){return ERR_INTERNAL;}
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
                   printf("JUMP %d",stack_pop_label(if_stack));
                   end();
                   in_if = false;

               }
               else if(in_while && !in_if){///truly end of while (not end of if in while)
                   printf("JUMP %d",stack_pop_label(while_stack));
                   end();
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

           case(TYPE_PLUS):
           case(TYPE_MINUS):
           case(TYPE_DIV):
           case(TYPE_MUL):
           case(TYPE_CONCAT):
               break;
           default:

               break;
       }
       i++;
    }
   return 0;
 }

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
void generate_condition(Syntactic_data_ptr data, int index){
    int i = index; bool inverse =false;

   printf("DEFVAR ");
   print_frame();
   printf("RESULT");
   end();
    switch ((*data).buffer.token[i+1]->type) {
        case(TYPE_COMPARE_NEG):
           printf("EQ ");
           inverse = true;
        break;
        case(TYPE_COMPARE):
            printf("EQ ");
            break;
        case(TYPE_LOWER):
            printf("LT ");
            break;
        case(TYPE_GREATER):
            printf("GT ");
            break;
        case(TYPE_GREATER_EQ):
            printf("GT ");   ///first for greater
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
            printf("EQ ");  ///continue with equal condition
            break;
        case(TYPE_LOWER_EQ):
            printf("LT ");   ///first for lower
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
            printf("EQ ");  ///continue with equal condition
            break;

        default:
            break;

    }
    print_operand(data, i);
    printf(" ");
    print_operand(data, i+2);
   end();
   printf("JUMPIFNEQ ");
   printf("%d ", index);
    print_frame();
    printf("RESULT");
    printf(" ");
    if(inverse){
        printf("bool@false");
    }else{
        printf("bool@true");
    }
    end();
    return;
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
