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
#include <stdlib.h>

int generator(Syntactic_data_ptr data) {

//    printf("kontrola bufferu:\n");                           ///testing buffer input
//    for(int i =0; i < (*data).buffer.length; i++){
//
//        printf("token i typ : %d \n", (*data).buffer.token[i]->type);
//    }
    generate_start(); ///HEADER
   /// print_main(data); ///
    printf("JUMP $main\n");
    generate_build_in();
    printf("LABEL $main\n");
    Generator_stack stack_for_if;
    Generator_stack *if_stack = &stack_for_if;
    if_stack->top = NULL;

    Generator_stack stack_for_while;
    Generator_stack *while_stack = &stack_for_while ;
    while_stack->top = NULL;

    Generator_stack stack_for_else;
    Generator_stack *else_stack = &stack_for_else ;
    else_stack->top = NULL;

    Gen_stack_var stack_for_var;
    Gen_stack_var *var_stack = &stack_for_var;
    var_stack->top = NULL;

     //print_main(data);

//     for(int i =0; i <5; i++){                           ///testing stack
//         stack_push_label(while_stack, i);
//         printf("%d\n", i);
//     }
//    for(int i =0; i <5; i++){
//        int j = stack_pop_label(while_stack);
//        printf("%d\n", j);
//    }
//    return 0;


    bool in_while= false;
    bool in_if= false;
    bool in_else =false;
    long unsigned  i = 0; ///starting from index 7 TODO

//    long unsigned end_buffer;
//    if((*data).buffer.token[(*data).buffer.length-1]->type == TYPE_EOF){
//        end_buffer = (*data).buffer.length-2;
//        if((*data).buffer.token[(*data).buffer.length-2]->type == TYPE_PROLOG_END){
//            end_buffer = (*data).buffer.length -2;
//        }
//    }
    GF = true;
    int check;
    int skip;
    int par_count;
    int start_index;

    while(i < (*data).buffer.length -1 ){///main generating loop ///todo
       ///based on the first type of the token determine which structure to generate
       //printf("typ tokenu: %d, i: %d ", (*data).buffer.token[i]->type, i);
       switch((*data).buffer.token[i]->type){

           case(KEYWORD_FUNCTION): ///FUNCTION DECLARATION
              // printf("#///FUNCTION DECLAration\n");
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
              // printf("#///FUNCTION CALLING\n");


               par_count = 1;
               start_index = i;
               ///special case for calling write
               if(cmp_string_buffer("write",(*data).buffer.token[i]->buf)==0) {
                   i++; ///skip left par
                   i++;

                   while ((*data).buffer.token[i]->type != TYPE_PAR_RIGHT) {

                          if((*data).buffer.token[i]->type == TYPE_VARIABLE_ID || (*data).buffer.token[i]->type == TYPE_STRING || (*data).buffer.token[i]->type == TYPE_FLOAT || (*data).buffer.token[i]->type == TYPE_INTEGER || (*data).buffer.token[i]->type == KEYWORD_NULL){//skipping comma
                              printf("CREATEFRAME"); end();
                              printf("DEFVAR TF@%%1\n");
                              printf("MOVE  TF@%%1 ");
                              print_operand(data,i);
                              end();
                              printf("CALL write");
                             // printf(" %d", par_count);
                              end();
                              par_count++;
                          }
                          //printf("%d\n",(*data).buffer.token[i]->type);
                       i++;
                   }
                   break;

               }else {  ///other function with limited amount of parameters

                  if (i < (*data).buffer.length-1 ){i++;}
                  else {break; }///skip left par
                   //printf("%d\n",(*data).buffer.token[i]->type);
                   if ((*data).buffer.token[i]->type == TYPE_FUNCTION_ID ){printf("CREATEFRAME"); end();}

                   while ((*data).buffer.token[i]->type != TYPE_PAR_RIGHT) { ///while arguments define them and move them values


                           if ((*data).buffer.token[i]->type == TYPE_INTEGER) { ///INTEGER CONSTANT
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
                           } else if ((*data).buffer.token[i]->type == TYPE_FLOAT) { ///FLOAT CONSTANT
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
                           } else if ((*data).buffer.token[i]->type == TYPE_STRING) { ///STRING CONSTANT
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
                           } else if ((*data).buffer.token[i]->type == TYPE_VARIABLE_ID) { ///STRING CONSTANT
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
                           i++;


                   }

                   printf("CALL ");
                   print_string((*data).buffer.token[start_index]->buf);
                   end();
                   if ((*data).buffer.token[start_index - 2]->type ==
                       TYPE_VARIABLE_ID) { ///moving return value to variable
                       printf("MOVE ");
                       print_frame();
                       print_string((*data).buffer.token[start_index - 2]->buf);/// Y = fun_id (fun_if = start_index)
                       printf(" ");
                       printf("TF@%%retval1");
                       end();
                   }



               }
               break;

           case(KEYWORD_WHILE): ///start of while, generate new label,  generate condition
              // printf("#///begin while  \n");
               in_while = true;
               printf("DEFVAR ");
               print_frame();
               printf("RESULT%lu", i+2);
               end();
               printf("LABEL WHILE_%d", generate_label( i)); ///Label while (insted of while id -which is unique)
               end();
              // printf("#pushing label WHILE_%d\n", i);
               check = stack_push_label(while_stack, i);
               if(check != 0){return ERR_INTERNAL;}
               i++; //skip while
               i++;//skip par left
               ///defining variable for condition above the if so i wont be redefined

               generate_condition(data, i, while_stack, in_while);
               end();

               break;

           case(KEYWORD_IF): ///start of if, generate new label,  generate condition
               printf("#begin if \n");
               in_if = true;

               i++; //skip if
               i++;//skip par left

               generate_condition(data, i, if_stack, in_while);
               end();


               break;

           case(KEYWORD_STRING):    ///POSSIBLE STARTS OF declaration
           case(KEYWORD_STRING_Q):
           case(KEYWORD_INT):
           case(KEYWORD_INT_Q):
           case(KEYWORD_FLOAT):
           case(KEYWORD_FLOAT_Q):
               i++; //skip keyword

               if(!declared(var_stack, (*data).buffer.token[i]->buf)){///undeclared
                   printf("DEFVAR "); ///DECLARATION
                   print_frame();
                   print_string((*data).buffer.token[i]->buf);
                   end();
                   if(add_var(var_stack, (*data).buffer.token[i]->buf)!= 0){return ERR_INTERNAL;}
               }

               skip = i+2;  ///check where is the variable assigned from
               if((*data).buffer.token[skip]->type == TYPE_FUNCTION_ID) { ///IF THE VALUE IS ASSIGNED FORM FUNCTION - MOVE TO CASE FUNCTION ID
                   i++;///skip to the function id the case will handle it
                   break;
               }
               if((*data).buffer.token[i+2]->type != TYPE_SEMICOLON){   ///ASSIGNING ARITHMETIC OPERATION

                   if((*data).buffer.token[i+2]->type == TYPE_DIV|| (*data).buffer.token[i+2]->type == TYPE_PLUS||(*data).buffer.token[i+2]->type == TYPE_MINUS||(*data).buffer.token[i+2]->type == TYPE_MUL||(*data).buffer.token[i+2]->type == TYPE_CONCAT){

                       i++;
                       i++;
                       break;
                   }

               }
               if(((*data).buffer.token[i+1]->type != TYPE_SEMICOLON)&&!((*data).buffer.token[i+2]->type == TYPE_DIV|| (*data).buffer.token[i+2]->type == TYPE_PLUS||(*data).buffer.token[i+2]->type == TYPE_MINUS||(*data).buffer.token[i+2]->type == TYPE_MUL||(*data).buffer.token[i+2]->type == TYPE_CONCAT)){

                   /// /ASSIGN THE VALUE DIRECTLY FROM CONSTANT OR VARIABLE
                   printf("MOVE ");
                   print_frame(); ///frame@
                   print_string((*data).buffer.token[i]->buf); ///name from the buffer
                   i++; //skip =
                   i++; //next arg

                   printf(" "); ///space between arguments
                   print_operand(data, i);
                   end();
               }

                   break;

           case(TYPE_VARIABLE_ID):

               if(!declared(var_stack, (*data).buffer.token[i]->buf)){ ///undeclared

                   printf("DEFVAR "); ///DECLARATION
                   print_frame();
                   print_string((*data).buffer.token[i]->buf);
                   end();
                   if(add_var(var_stack, (*data).buffer.token[i]->buf)!= 0){return ERR_INTERNAL;}
               }


               if((*data).buffer.token[i+2]->type == TYPE_FUNCTION_ID) {
                  // printf("VAR ID");
                  ///already defined
                  i++; ///skip to the function id the case will handle it
                  end();
                  break;
               }
               if((*data).buffer.token[i+3]->type != TYPE_SEMICOLON) {   ///ASSIGNING ARITHMETIC OPERATION

                   if ((*data).buffer.token[i + 3]->type == TYPE_DIV ||
                       (*data).buffer.token[i + 3]->type == TYPE_PLUS ||
                       (*data).buffer.token[i + 3]->type == TYPE_MINUS ||
                       (*data).buffer.token[i + 3]->type == TYPE_MUL ||
                       (*data).buffer.token[i + 3]->type == TYPE_CONCAT) {

                       i++;///skip to the first operand of arithmetic expression
                       i++;
                       break;
                   }
               }
                   printf("MOVE ");
                   print_frame(); ///frame@
                   print_string((*data).buffer.token[i]->buf); ///name from the buffer
                   i++; //skip =
                   i++; //next arg
                   printf(" "); ///space between arguments
                   print_operand(data, i);
                   end();

               break;

           case (TYPE_BRACE_RIGHT): ///end of if er while => generate end label
               if(in_if){

                   if((*data).buffer.token[i+1]->type == KEYWORD_ELSE){
                       printf("JUMP END_ELSE_%lu", i);
                       end();
                       in_else = true;
                       stack_push_label(else_stack, i);
                   }
                   printf("LABEL ENDIF_%d",stack_pop_label(if_stack)); ///END OF IF
                   end();
                   in_if = false;

               }
               else if(in_while && !in_else){///truly end of while (not end of else in while)
                   skip = stack_pop_label(while_stack);///temporarily storing end of while
                   printf("JUMP WHILE_%d", stack_pop_label(while_stack));
                   end();
                   in_while = false;
                   printf("LABEL END_WHILE_%d",skip);
                   end();
               }
               else if(in_else){
                   printf("LABEL END_ELSE_%d", stack_pop_label(else_stack));
                   end();
                   in_else = false;
               }
               ///else not needed generator is in the end end of function which was already handled by keyword return

               break;
           case(KEYWORD_RETURN): ///todo handle when returning function retval
                 printf("#///RETURN \n");
               LF = false; GF = true;
               printf("MOVE LF@%%retval1 ");
               if((*data).buffer.token[i+1]->type != TYPE_SEMICOLON){
                   printf("LF@");
                   print_string((*data).buffer.token[i+1]->buf); ///name ot the return value
                   printf("%d", param_count);

               }else{
                  printf("nil@nil"); // returning void
               }
               end();
               printf("POPFRAME");
               end();
               printf("RETURN");
               end();
               i++;

               break;

               case(TYPE_PLUS):

                   printf("ADD ");         ///i => first operand
                   print_operand(data, (i-3)); ///y = a+b  y => i-2
                   printf(" ");
                   print_operand(data, (i-1)); ///i => first operand
                   printf(" ");
                   print_operand(data, (i+1));///i+2 => second operand
                   end();
                   break;
               case(TYPE_MINUS):
                   printf("SUB ");
               print_operand(data, (i-3)); ///y = a+b  y => i-2
               printf(" ");
               print_operand(data, (i-1)); ///i => first operand
               printf(" ");
               print_operand(data, (i+1));///i+2 => second operand
               end();
                   break;
               case(TYPE_DIV):
                   printf("DIV ");
               print_operand(data, (i-3)); ///y = a+b  y => i-2
               printf(" ");
               print_operand(data, (i-1)); ///i => first operand
               printf(" ");
               print_operand(data, (i+1));///i+2 => second operand
               end();
                   break;
               case(TYPE_MUL):
                   printf("MUL ");
               print_operand(data, (i-3)); ///y = a+b  y => i-2
               printf(" ");
               print_operand(data, (i-1)); ///i => first operand
               printf(" ");
               print_operand(data, (i+1));///i+2 => second operand
               end();
                   break;
               case(TYPE_CONCAT):
                   printf("CONCAT ");
               print_operand(data, (i-3)); ///y = a+b  y => i-2
               printf(" ");
               print_operand(data, (i-1)); ///i => first operand
               printf(" ");
               print_operand(data, (i+1));///i+2 => second operand
               end();
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
        print_string((*data).buffer.token[i]->buf);///value of the string constant

    }
    else if((*data).buffer.token[i]->type == TYPE_VARIABLE_ID){ ///STRING CONSTANT
        print_frame(); ///frame@
        print_string((*data).buffer.token[i]->buf); ///name from the buffer

    }
    else if((*data).buffer.token[i]->type == KEYWORD_NULL){ ///INTEGER CONSTANT
        printf("nil@nil");
       // print_string((*data).buffer.token[i]->buf);///value of the int constant

    }
    return;
}
int generate_label( int index){
    return index;
}
void generate_condition(Syntactic_data_ptr data, int index, Generator_stack *stack, bool in_while){
    int i = index; ///index of the first operand
    bool inverse = false;
  //  printf("prvni token v condition : %d \n", (*data).buffer.token[i]->type);//check
    if(!in_while){
        printf("DEFVAR ");
        print_frame();
        printf("RESULT%d", index);
        end();
    }
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
            printf("RESULT%d", index);
            printf(" ");
            print_operand(data, i);
            printf(" ");
            print_operand(data, i+2);
            end();//fixed bool values added debug comments which can stay as comments in final code
            printf("JUMPIFNEQ ");
            if(in_while){
                printf("END_WHILE_%d ", index);
            }
            else{printf("ENDIF_%d ", index);}

            stack_push_label(stack, index);
            print_frame();
            printf("RESULT%d", index);
            printf(" ");
            printf("bool@true");
            end();
            printf("EQ ");  ///continue with equal condition
            break;
        case(TYPE_LOWER_EQ):
            printf("LT "); ///first for lower
            printf(" ");
            print_frame();
            printf("RESULT%d", index);
            printf(" ");
            print_operand(data, i);
            printf(" ");
            print_operand(data, i+2);
            end();
            printf("JUMPIFNEQ ");
            if(in_while){
                printf("END_WHILE_%d ", index);
            }
            else{printf("ENDIF_%d ", index);}

            stack_push_label(stack, index);
            print_frame();
            printf("RESULT");
            printf(" ");
            printf("bool@true");
            end();
            printf("EQ ");  ///continue with equal condition
            break;
        case(TYPE_PAR_RIGHT):  ///condition is number
             if(cmp_string_buffer("0",(*data).buffer.token[i-1]->buf)){ ///always false
                 printf("JUMP "); ///unconditional jump
                 if(in_while){
                     printf("END_WHILE_%d ", index);
                 }
                 else{printf("ENDIF_%d ", index);}

                 int check = stack_push_label(stack ,generate_label(i));
                 return;
             }
             if(cmp_string_buffer("1",(*data).buffer.token[i-1]->buf)){ ///always true
                 ///we will push the label so else has something to pop but the label will be never used
                 int check = stack_push_label(stack ,generate_label(i));
                 return;
             }
             break;
        default:

            break;

    }
    printf(" ");
    print_frame();
    printf("RESULT%d", index);
    printf(" ");
    print_operand(data, i);
    printf(" ");
    print_operand(data, i+2);
   end();

   printf("JUMPIFNEQ ");
   if(in_while){
       printf("END_WHILE_%d ", index);
   }
   else{printf("ENDIF_%d ", index);}

    print_frame();
    printf("RESULT%d", index);
    printf(" ");
    if(inverse){
        printf("bool@false");
    }else{
        printf("bool@true");
    }
    end();

//    if(in_while){printf("#pushing label end_WHILE:%d\n", i);}
//    else{
//        printf("#pushing label END_IF_%d\n", i);
//        }

    int check = stack_push_label(stack ,generate_label(i)); ///we want to store if for generating end of if or else
    if(check){return ERR_INTERNAL;}

    return;
}

void generate_start(){
   // printf("#   CILOVY K0D IFJcode22   \n");
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
    if(cmp_string_buffer("null", buf)==0)    ///converting null to nil
    {
        printf("nil");
        return;
    }
    for(int i =0; buf->buf[i] != '\0'; i++){
        char c = buf->buf[i];
        if(c < 32 || c == 35 || c == 92){
            printf("\\%0.3d",buf->buf[i]); ///special characters
        }
        printf("%c", buf->buf[i]);      ///normal characters
    }
    return;

}
void print_float(Buffer *buf){
    float num = atof(buf->buf);
    printf("%a", num);
    return;
}

void print_main(Syntactic_data_ptr data){
    int j = 0;
    while (j < (*data).buffer.length) ///search in the buffer
    {
        if((*data).buffer.token[j]->type == TYPE_FUNCTION_ID){
           if(cmp_string_buffer("main",(*data).buffer.token[j]->buf)>=0){   ///can contain more chars than just main main$ etc.
               printf("JUMP ");
               print_string((*data).buffer.token[j]->buf); ///print the label containing main
               end();
               return;
           }
        }
        //printf("%d\n", j);
        j++;
    }
}

void end(){
    printf("\n");
}

///generating arithmetic expression ///THIS IS FOR GENERAL EXPRESSION SO FAR ON THE PURPOSE OF TESTING WE DONT USE IT
///
void generate_expression(Syntactic_data_ptr data, int index){
    int end_of_exp = find_end();
}

int find_end(Syntactic_data_ptr data, int index){  ///searching end of expression

    while((*data).buffer.token[index]->type != TYPE_SEMICOLON){
        index++;
    }
    return index;
}

void generate_build_in(){

    ///WRITE - WE HAVE INFINITE NUMBER OF OPERANDS, S0 WE WILL CREATE THE FUNCTION FOR ONE OPERAND AND CALL IT MULTIPLE TIMES
    printf ("#build in function write\n");
    printf ("LABEL write\n");
    // printf("CREATEFRAME\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@param1\n");
    printf ("MOVE LF@param1 LF@%%1\n");
    printf ("WRITE LF@param1\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    ///readi

    printf ("#build in function readi\n");
    printf ("LABEL readi\n");
    printf ("CREATEFRAME\n");
    printf ("DEFVAR LF@param1\n");
    printf ("READ LF@param1 int\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    ///readf

    printf ("#build in function readf\n");
    printf ("LABEL readf\n");
    printf ("CREATEFRAME\n");
    printf ("DEFVAR LF@param1\n");
    printf ("READ LF@param1 float\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    ///reads

    printf ("build in function reads\n");
    printf ("LABEL reads\n");
    printf ("CREATEFRAME\n");
    printf ("DEFVAR LF@param1\n");
    printf ("READ LF@param1 string\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    ///floatval

    printf ("build in function floatval\n");
    printf ("LABEL floatval\n");
    printf ("CREATEFRAME\n");
    printf ("DEFVAR LF@result\n");
    printf ("DEFVAR LF@result2\n");
    printf ("DEFVAR FLOATVAL_RET\n");
    printf ("TYPE LF@result LF@%%1\n");
    printf ("EQ LF@result2 LF@result string@int\n");
    printf ("JUMPIFNQ itisint LF@result2 bool@false\n");
    printf ("EQ LF@result2 LF@result string@float\n");
    printf ("JUMPIFNQ itisfloat LF@result2 bool@false\n");

        //// TODO : STRING;
    printf("JUMP END_FLOATVAL\n");

    printf ("LABEL itisint\n");
    printf ("INT2FLOAT FLOATVAL_RET LF@%%1");
    printf ("JUMP END_FLOATVAL\n");

    printf ("LABEL itisfloat\n");
    printf ("MOVE FLOATVAL_RET LF@%%1");
    printf ("JUMP END_FLOATVAL\n");

    printf("LABEL END_FLOATVAL\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n")


    ///intval
    printf ("build in function intval\n");
    printf ("LABEL intval\n");
    printf ("CREATEFRAME\n");
    printf ("DEFVAR LF@result_i\n");
    printf ("DEFVAR LF@result_i2\n");
    printf ("DEFVAR INTVAL_RET\n");
    printf ("TYPE LF@result_i LF@%%1\n");
    printf ("EQ LF@result_i2 LF@result_i string@int\n");
    printf ("JUMPIFNQ itisint_i LF@result_i2 bool@false\n");
    printf ("EQ LF@result_i2 LF@result_i string@float\n");
    printf ("JUMPIFNQ itisfloat_i LF@result_i2 bool@false\n");

    //// TODO : STRING;
    printf("JUMP END_INTVAL\n");

    printf ("LABEL itisint_i\n");
    printf ("MOVE INTVAL_RET LF@%%1\n");
    printf ("JUMP END_INTVAL\n");

    printf ("LABEL itisfloat_i\n");
    printf ("FLOAT2INT INTVAL_RET LF@%%1\n");
    printf ("JUMP END_FLOATVAL\n");

    printf ("LABEL END_INTVAL\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n")



    return;
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

int add_var(Gen_stack_var *stack, Buffer *buf){

    Stack_var *new = (Stack_var *)malloc(sizeof(Stack_var )); ///allocation of new item
    if(!new){
        return ERR_INTERNAL; ///malloc fail
    }

    new->next = stack->top; ///keeping the links
    stack->top = new;

    new->buf = buf; ///assigning new value
    return 0;
}

bool declared(Gen_stack_var *stack, Buffer *buf){
    Stack_var *active = stack->top;
    while(active != NULL){ ///till the last item
        if(strcmp(active->buf->buf, buf->buf)==0){ ///if match
            return true;  ///declared
        }
        active = active->next; ///iterate
    }
    return false;///no match found
}

void free_var_stack(Gen_stack_var *stack){
    if(stack == NULL){
        return;
    }
    while(stack->top != NULL){ ///while stack isn not empty
        Stack_var * to_delete = stack->top; ///prepare item to delete
        stack->top = stack->top->next; ///keep the links
        free(to_delete);  ///delete the item
    }
    stack = NULL; ///deleting finished
    return;
}