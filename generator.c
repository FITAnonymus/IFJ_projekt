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

    printf("kontrola bufferu:\n");
    for(int i =0; i < (*data).buffer.length; i++){

        printf("token : %d \n", (*data).buffer.token[i]->type);
    }
    Generator_stack stack_for_if;
    Generator_stack *if_stack = &stack_for_if;
    if_stack->top = NULL;

    Generator_stack stack_for_while;
    Generator_stack *while_stack = &stack_for_while ;
    while_stack->top = NULL;

    Generator_stack stack_for_else;
    Generator_stack *else_stack = &stack_for_else ;
    else_stack->top = NULL;

     generate_start(); ///HEADER
     //print_main(data);

    ///TODO IF ELSE
    ///TODO COMPLEX TESTING

    bool in_while= false;
    bool in_if= false;
    bool in_else =false;
    long unsigned  i = 0;
    GF = true;
    int check;
    int skip;

    while(i < (*data).buffer.length){///main generating loop
       ///based on the first type of the token determine which structure to generate
       //printf("typ tokenu: %d, i: %d ", (*data).buffer.token[i]->type, i);
       switch((*data).buffer.token[i]->type){

           case(KEYWORD_FUNCTION): ///FUNCTION DECLARATION
               printf("#///FUNCTION DECLAration\n");
              // in_fun= true;
               LF=true; GF=false; TF=false;  ///just for sure

               printf("LABEL ");                     ///LABEL
               i++;                     ///skipping keyword
               print_string((*data).buffer.token[i]->buf);
               end();

               if(cmp_string_buffer("main",(*data).buffer.token[i]->buf )==0){
                   printf("CREATEFRAME");
                   end();
               }
               printf("PUSHFRAME");
               end();
               printf("DEFVAR LF@%%retval1");
               end();
               printf("MOVE LF@%%retval1 nil@nil");
               end();
               i++; //skip brace left
               int param_count = 0;
               while((*data).buffer.token[i]->type != TYPE_PAR_RIGHT) { ///while arguments define them and move them values
                      if((*data).buffer.token[i]->type != TYPE_VARIABLE_ID &&(*data).buffer.token[i]->type != TYPE_COMMA && (*data).buffer.token[i]->type != KEYWORD_FLOAT && (*data).buffer.token[i]->type !=  KEYWORD_INT && (*data).buffer.token[i]->type != KEYWORD_STRING )
                      { param_count++;
                          printf("DEFVAR ");
                          printf("LF@");
                          printf("param%d",param_count);
                          end();
                          printf("MOVE ");
                          printf("LF@");
                          printf("param%d",param_count);
                          printf(" ");
                          printf("TF@");
                          printf("%%%d", param_count);
                          end();
                         }
                   i++;
               }

               i++;//skip par right
               i++;//skip semicolon
               i++; //slkip return type so the declaration wont be confused
               ///skipping function id which used only for calling the function
               ///continue generating program when hitting the return keyword the generator wil generate return value
               break;

           case(TYPE_FUNCTION_ID): ///FUNCTION CALLING /// y = foo(10, "Hi X!")
               printf("#///FUNCTION CALLING\n");
               printf("CREATEFRAME");
               end();
               int par_count = 1;
               int start_index = i;
               while((*data).buffer.token[i]->type != TYPE_PAR_RIGHT) { ///while arguments define them and move them values

                   if((*data).buffer.token[i]->type == TYPE_INTEGER){ ///INTEGER CONSTANT
                       printf("DEFVAR "); ///defining the parameter
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
                       printf("%d", par_count);
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
                       printf("TF@");         ///parameter name
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
                       printf("%d", par_count);
                       end();
                       printf("MOVE ");
                       printf("TF@");         ///parameter name
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
               printf("CALL ");
               print_string((*data).buffer.token[start_index]->buf);
               end();
               printf("MOVE ");
               print_frame();
               print_string((*data).buffer.token[start_index -2]->buf);/// Y = fun_id (fun_if = start_index)
               printf(" ");
               printf("TF@%%retval1");
               end();
               break;

           case(KEYWORD_WHILE): ///start of while, generate new label,  generate condition
               printf("#///begin while  \n");
               in_while = true;
               printf("LABEL %d", generate_label( i)); ///Label while (insted of while id -which is unique)
               end();
               generate_condition(data, i, while_stack);
               end();
               check = stack_push_label(while_stack ,generate_label( i));
               if(check){return ERR_INTERNAL;}
               break;

           case(KEYWORD_IF): ///start of if, generate new label,  generate condition
               printf("#begin if \n");
               in_if = true;
               //printf("LABEL IF:%d", generate_label( i));///Label if (insted of if id -which is unique)
              // end();
               i++; //skip if
               i++;//skip par left

               generate_condition(data, i, if_stack);
               end();


               break;

           case(KEYWORD_STRING):    ///POSSIBLE STARTS OF EXPRESSIONS
           case(KEYWORD_STRING_Q):
           case(KEYWORD_INT):
           case(KEYWORD_INT_Q):
           case(KEYWORD_FLOAT):
           case(KEYWORD_FLOAT_Q):

               printf("#///VARIABLE DEFINITION\n");
               printf("DEFVAR "); ///DECLARATION
               print_frame();
               i++; //skip keyword
               print_string((*data).buffer.token[i]->buf); ///name from the buffer
               end(); ///end of instruction

               skip = i+2;  ///check where is the variable assigned from
               if((*data).buffer.token[skip]->type == TYPE_FUNCTION_ID) { ///IF THE VALUE IS ASSIGNED FORM FUNCTION - MOVE TO CASE FUNCTION ID
                   i++;
                   i++;///skip to the function id the case will handle it
                   break;
               }else{
                  /// /ASSIGN THE VALUE DIRECTLY FROM CONSTANT OR VARIABLE
                   printf("MOVE ");
                   print_frame(); ///frame@
                   print_string((*data).buffer.token[i]->buf); ///name from the buffer
                   i++; //skip =
                   i++; //next arg

                   printf(" "); ///space between arguments
                   print_operand(data, i);
                   end();
                   break;
               }

            case(TYPE_VARIABLE_ID):
               if((*data).buffer.token[i+2]->type == TYPE_FUNCTION_ID) {
                   printf("VAR ID");
                  ///already defined
                  i++; ///skip to the function id the case will handle it
                  break;
               }
                   printf("MOVE ");
                   print_frame(); ///frame@
                   print_string((*data).buffer.token[i]->buf); ///name from the buffer
                   i++; //skip =
                   i++; //next arg
                   printf(" "); ///space between arguments
                   print_operand(data, i);
               break;

               case (TYPE_BRACE_RIGHT): ///end of if er while => generate end label
               if(in_if){


                   if((*data).buffer.token[i+1]->type == KEYWORD_ELSE){
                       printf("JUMP END_ELSE:%lu", i);
                       end();
                       in_else = true;
                       stack_push_label(else_stack, i);
                   }
                   printf(" LABEL ENDIF:%d",stack_pop_label(if_stack)); ///END OF IF
                   end();
                   in_if = false;
                   break;
               }
               else if(in_while && !in_if && !in_else){///truly end of while (not end of if in while)
                   printf("JUMP %d",stack_pop_label(while_stack));
                   end();
                   in_while = false;
               }
               else if(in_else){
                   printf("LABEL END_ELSE:%d", stack_pop_label(else_stack));
                   end();
                   in_else = false;
               }
               ///else not needed generator is in the end end of function which was already handled by keyword return

               break;

             case(KEYWORD_RETURN): ///todo handle when returning function retval
                 printf("#///RETURN \n");
               LF = false; GF = true;
               printf("MOVE LF@%%retval1 ");
               printf("LF@");
               print_string((*data).buffer.token[i+1]->buf); ///name ot the return value
               printf("%d", param_count);
               end();
               printf("POPFRAME");
               end();
               printf("RETURN");
               end();
               i++;
               break;

               case(TYPE_PLUS):
               case(TYPE_MINUS):
               case(TYPE_DIV):
               case(TYPE_MUL):
               case(TYPE_CONCAT):
               break;
           default:

               break ;
       }
       i++;
    }

   return 0;
 }

void print_operand(Syntactic_data_ptr data, int i){

    if((*data).buffer.token[i]->type == TYPE_INTEGER){ ///INTEGER CONSTANT
        printf("int@");
        print_string((*data).buffer.token[i]->buf);///value of the int constant

    }
    else if((*data).buffer.token[i]->type == TYPE_FLOAT){ ///FLOAT CONSTANT
        printf("float@");
        print_float((*data).buffer.token[i]->buf);///value of the float constant

    }
    else if((*data).buffer.token[i]->type == TYPE_STRING){ ///STRING CONSTANT
        printf("string@");
        print_float((*data).buffer.token[i]->buf);///value of the string constant

    }
    else if((*data).buffer.token[i]->type == TYPE_VARIABLE_ID){ ///STRING CONSTANT
        print_frame(); ///frame@
        print_string((*data).buffer.token[i]->buf); ///name from the buffer

    }
    return;
}
int generate_label( int index){
    return index;
}
void generate_condition(Syntactic_data_ptr data, int index, Generator_stack *stack){
    int i = index; ///index of the first operand
    bool inverse = false;
   // printf("prvni token v condition : %d \n", (*data).buffer.token[i]->type);//check

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
            printf(" ");
            print_frame();
            printf("RESULT");
            printf(" ");
            print_operand(data, i);
            printf(" ");
            print_operand(data, i+2);
            end();//fixed bool values added debug comments which can stay as comments in final code
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
            printf("LT "); ///first for lower
            printf(" ");
            print_frame();
            printf("RESULT");
            printf(" ");
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
    printf(" ");
    print_frame();
    printf("RESULT");
    printf(" ");
    print_operand(data, i);
    printf(" ");
    print_operand(data, i+2);
   end();

   printf("JUMPIFNEQ ");
   printf("ENDIF:%d ", index);
    stack_push_label(stack, index);
    print_frame();
    printf("RESULT");
    printf(" ");
    if(inverse){
        printf("bool@false");
    }else{
        printf("bool@true");
    }
    end();

    printf("#pushing label num:%d\n", i);
    int check = stack_push_label(stack ,generate_label(i)); ///we want to store if for generating end of if or else
    if(check){return ERR_INTERNAL;}

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

    print_buffer(buf);

    return;
}
void print_float(Buffer *buf){
    for(int i =0; buf->buf[i] != '\0'; i++){
        printf("%c", buf->buf[i]);
    }
    return;
}

void print_main(Syntactic_data_ptr data){   ///MAKES ERRORS REMAke
    long unsigned  j =0;
    while (j < (*data).buffer.length)
    {
        if((*data).buffer.token[j]->type == TYPE_FUNCTION_ID){
           if(cmp_string_buffer("main",(*data).buffer.token[j]->buf)==0){  ///TODO ADJUST OT ONLY CONTAIN MAIN
               printf("JUMP ");
               print_string((*data).buffer.token[j]->buf);
               end();
               return;
           }
        }
        j++;
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

void end(){
    printf("\n");
}

