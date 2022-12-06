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
    //printf("CREATEFRAME\n");
    //printf("PUSHFRAME\n");
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
    bool in_fun = false;
    long unsigned  i = 0;

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
    int fun_cnt =0;
    int label;
    while(i < (*data).buffer.length -1 ){///main generating loop ///todo
        ///based on the first type of the token determine which structure to generate
        //printf("typ tokenu: %d, i: %d ", (*data).buffer.token[i]->type, i);
        switch((*data).buffer.token[i]->type){

            case(KEYWORD_FUNCTION): ///FUNCTION DECLARATION
                // printf("#///FUNCTION DECLAration\n");
                in_fun= true;
                LF=true; GF=false; TF=false;  ///just for sure
                fun_cnt++;
                printf("JUMP SKIP_FUN_%lu", i);
                end();
                skip = i;
                printf("LABEL ");                     ///LABEL
                i++;                     ///skipping keyword
                print_string((*data).buffer.token[i]->buf);
                end();
                //printf("CREATEFRAME");
                end();

                printf("PUSHFRAME");
                end();
                printf("DEFVAR LF@%%retval%d", fun_cnt);
                end();
                printf("MOVE LF@%%retval%d nil@nil", fun_cnt );
                end();
                i++; //skip fin id
                i++; //skip brace left
                int param_count = 0;
                //printf("token %d\n",(*data).buffer.token[i]->type );
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
                        printf("LF@");
                        printf("%%%d", param_count);
                        end();
                    }
                    i++;
                }

                i++;//skip par right
                i++;//skip semicolon
                i++; //slkip return type so the declaration wont be confused
                end();


                ///skipping function id which used only for calling the function
                ///continue generating program when hitting the return keyword the generator wil generate return value
                break;

            case(TYPE_FUNCTION_ID): ///FUNCTION CALLING /// y = foo(10, "Hi X!")
                // printf("#///FUNCTION CALLING\n");
                // printf("CREATEFRAME"); end();

                par_count = 1;
                start_index = i;
                ///special case for calling write
                if(cmp_string_buffer("write",(*data).buffer.token[i]->buf)==0) {
                    i++; ///skip left par
                    i++; ///first operand

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
                    ///another special case for build in functions
                }else if(cmp_string_buffer("readi",(*data).buffer.token[i]->buf)==0 || cmp_string_buffer("readf",(*data).buffer.token[i]->buf)==0 || cmp_string_buffer("reads",(*data).buffer.token[i]->buf)==0){
                    printf("CREATEFRAME"); end();
                    printf("CALL ");                           ///CALL build in function
                    print_buffer((*data).buffer.token[i]->buf);
                    end();
                    printf("MOVE ");
                    print_operand(data, i -2); ///y = readi (redi = i) y = i-2
                    printf(" TF@retval1");
                    end();

                }else {  ///other function with limited amount of parameters

                    printf("CREATEFRAME"); end();
                    end();
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

                if((*data).buffer.token[i+2]->type == TYPE_FUNCTION_ID) { ///IF THE VALUE IS ASSIGNED FORM FUNCTION - MOVE TO CASE FUNCTION ID
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
                    int check = stack_pop_label(if_stack);
                    if(check != -1){ printf("LABEL ENDIF_%d",check); ///END OF IF
                        end();
                    }

                    in_if = false;

                }
                else if(in_while && !in_else && !in_if){///truly end of while (not end of else in while)
                    label = stack_pop_label(while_stack);///temporarily storing end of while
                    printf("JUMP WHILE_%d", stack_pop_label(while_stack));
                    end();
                    in_while = false;
                    printf("LABEL END_WHILE_%d",label );
                    end();
                }
                else if(in_else && !in_while &&!in_if){
                    printf("LABEL END_ELSE_%d", stack_pop_label(else_stack));
                    end();
                    in_else = false;
                }
                else if(in_fun && !in_else && !in_while &&!in_if){
                    ///there wasnt obviously keyword return
                    printf("MOVE LF@%%retval1 ");
                    printf("nil@nil"); // returning void
                    end();
                    printf("POPFRAME");
                    end();
                    printf("RETURN");
                    end();
                    printf("LABEL SKIP_FUN_%d", skip);
                    end();
                    i++;
                }


                break;
            case(KEYWORD_RETURN): ///todo handle when returning function retval
                printf("#///RETURN \n");
                LF = false; GF = true;
                if(i == 0 ){ ///global return
                    printf("CREATEFRAME\n");
                    //printf("PUSHFRAME\n");
                    printf("DEFVAR GF@%%retval1");
                    end();
                    printf("MOVE GF@%%retval1 ");
                    if((*data).buffer.token[i+1]->type == TYPE_SEMICOLON){
                        printf("nil@nil"); // returning void
                    }
                    else{
                        print_operand(data, i+1);
                    }

                    end();
                    printf("POPFRAME");
                    end();
                    printf("RETURN");
                    end();
                    return;
                }
                else if((*data).buffer.token[i+1]->type == TYPE_SEMICOLON){
                    printf("MOVE LF@%%retval1 ");
                    printf("nil@nil"); // returning void
                }else if((*data).buffer.token[i + 2]->type == TYPE_DIV ||
                         (*data).buffer.token[i + 2]->type == TYPE_PLUS ||
                         (*data).buffer.token[i + 2]->type == TYPE_MINUS ||
                         (*data).buffer.token[i + 2]->type == TYPE_MUL ||
                         (*data).buffer.token[i + 2]->type == TYPE_CONCAT){

                    print_op(data, i+2); ///add
                    printf("LF@%%retval%d ", fun_cnt);
                    printf(" ");
                    print_operand(data, i+1);  /// prvni operand
                    printf(" ");
                    print_operand(data, i+3); ///druhy operand
                    end();



                }else{
                    printf("MOVE LF@%%retval1 ");
                    print_operand(data, i+1);

                }
                end();
                printf("POPFRAME");
                end();
                printf("RETURN");
                end();
                printf("LABEL SKIP_FUN_%d", skip);
                end();
                i++;
                in_fun = false;
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

    if((*data).buffer.token[i]->type == TYPE_PAR_RIGHT){ /// if()
        printf("JUMP "); ///unconditional jump
        if(in_while){
            printf("END_WHILE_%d ", index);
        }
        else{printf("ENDIF_%d ", index);}

        int check = stack_push_label(stack ,generate_label(i));
        return;
    }
    else if((*data).buffer.token[i]->type == TYPE_STRING){ /// if(string)
        if((*data).buffer.token[i]->buf->lenght != 0 && cmp_string_buffer("0", (*data).buffer.token[i]->buf) != 0){
            int check = stack_push_label(stack ,generate_label(-1));
            return;
        }

        printf("JUMP "); ///unconditional jump
        if(in_while){
            printf("END_WHILE_%d ", index);
        }
        else{printf("ENDIF_%d ", index);}

        int check = stack_push_label(stack ,generate_label(i));
        return;
    }
    else if((*data).buffer.token[i]->type == TYPE_INTEGER || (*data).buffer.token[i]->type == TYPE_FLOAT){ /// if(string)
        if(cmp_string_buffer("0", (*data).buffer.token[i]->buf) ==0 || cmp_string_buffer("0.0", (*data).buffer.token[i]->buf)==0){
            printf("JUMP "); ///unconditional jump
            if(in_while){
                printf("END_WHILE_%d ", index);
            }
            else{printf("ENDIF_%d ", index);}

            int check = stack_push_label(stack ,generate_label(i));
            return;
        }

        int check = stack_push_label(stack ,generate_label(-1));
        return;
    }
    else if((*data).buffer.token[i]->type == KEYWORD_NULL){
        printf("JUMP "); ///unconditional jump
        if(in_while){
            printf("END_WHILE_%d ", index);
        }
        else{printf("ENDIF_%d ", index);}

        int check = stack_push_label(stack ,generate_label(i));
        return;
    }
    else if((*data).buffer.token[i]->type == TYPE_VARIABLE_ID){
//        if(cmp_string_buffer("0",(*data).buffer.token[i]->buf)==0 ||cmp_string_buffer("",(*data).buffer.token[i]->buf)==0){
//            printf("JUMP "); ///unconditional jump
//            if(in_while){
//                printf("END_WHILE_%d ", index);
//            }
//            else{printf("ENDIF_%d ", index);}
//
//            int check = stack_push_label(stack ,generate_label(i));
//            return;
//        }
        int check = stack_push_label(stack ,generate_label(-1));
        return;

    }
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
        if(c <= 32 || c == 35 || c == 92){
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

    //  printf("CREATEFRAME\n");

    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@param1\n");
    printf ("MOVE LF@param1 LF@%%1\n");
    printf ("WRITE LF@param1\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    ///readi

    printf ("#build in function readi\n");
    printf ("LABEL readi\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("READ LF@retval1 int\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    ///readf

    printf ("#build in function readf\n");
    printf ("LABEL readf\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("READ LF@retval1 float\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    ///reads

    printf ("#build in function reads\n");
    printf ("LABEL reads\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("READ LF@retval1 string\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");


    ///floatval

    printf ("#build in function floatval\n");
    printf ("LABEL floatval\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@result\n");
    printf ("DEFVAR LF@result2\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("TYPE LF@result LF@%%1\n");
    printf ("EQ LF@result2 LF@result string@int\n");
    printf ("JUMPIFNEQ itisint LF@result2 bool@false\n");
    printf ("EQ LF@result2 LF@result string@float\n");
    printf ("JUMPIFNEQ itisfloat LF@result2 bool@false\n");

    /// STRNUM
//    printf ("DEFVAR LF@counter_floatval\n");
//    printf ("DEFVAR LF@cycle_floatval\n");
//    printf ("DEFVAR LF@current_floatval\n");
//    printf ("DEFVAR LF@conversion_floatval\n");
//    printf ("STRLEN LF@counter_floatval LF@%%1\n");
//    printf ("MOVE LF@cycle_floatval int@0\n");
//    printf ("LABEL WHILE_FLOATVAL\n");
//    printf ("JUMPIFEQ END_FLOATVAL LF@cycle_floatval LF@counter_floatval\n");
//    printf ("STR2INT LF@current_floatval LF@%%1 LF@cycle_floatval\n");
//    printf ("SETCHAR LF@conversion_floatval LF@cycle_floatval LF@current_floatval\n");
//    printf ("JUMP WHILE_FLOATVAL\n");
//    printf ("LABEL END_WHILE_FLOATVAL\n");
//    printf ("MOVE LF@retval1 LF@conversion_floatval\n");
//    printf ("JUMP END_FLOATVAL\n");

    printf ("LABEL itisint\n");
    printf ("INT2FLOAT LF@retval1 LF@%%1\n");
    printf ("JUMP END_FLOATVAL\n");

    printf ("LABEL itisfloat\n");
    printf ("MOVE LF@retval1 LF@%%1\n");
    printf ("JUMP END_FLOATVAL\n");

    printf ("LABEL END_FLOATVAL\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");


    ///intval
    printf ("#build in function intval\n");
    printf ("LABEL intval\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@result_i\n");
    printf ("DEFVAR LF@result_i2\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("TYPE LF@result_i LF@%%1\n");
    printf ("EQ LF@result_i2 LF@result_i string@int\n");
    printf ("JUMPIFNEQ itisint_i LF@result_i2 bool@false\n");
    printf ("EQ LF@result_i2 LF@result_i string@float\n");
    printf ("JUMPIFNEQ itisfloat_i LF@result_i2 bool@false\n");

    //// TODO : STRING;
    printf("JUMP END_INTVAL\n");

    printf ("LABEL itisint_i\n");
    printf ("MOVE LF@retval1 LF@%%1\n");
    printf ("JUMP END_INTVAL\n");

    printf ("LABEL itisfloat_i\n");
    printf ("FLOAT2INT LF@retval1 LF@%%1\n");
    printf ("JUMP END_FLOATVAL\n");

    printf ("LABEL END_INTVAL\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");


    ///strval
    printf("#build in function strval\n");
    printf ("LABEL strval\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@result_s\n");
    printf ("DEFVAR LF@result_s2\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("TYPE LF@result_s LF@%%1\n");
    printf ("EQ LF@result_s2 LF@result_s string@int\n");
    printf ("JUMPIFNEQ itisint_s LF@result_s2 bool@false\n");
    printf ("EQ LF@result_s2 LF@result_s string@float\n");
    printf ("JUMPIFNEQ itisfloat_s LF@result_s2 bool@false\n");
    printf ("MOVE LF@retval1 LF@%%1\n");
    printf("JUMP END_STRVAL\n");

    printf ("LABEL itisint_s\n");
    /// TODO : INT TO STR
    printf ("JUMP END_STRVAL\n");

    printf ("LABEL itisfloat_s\n");
    /// TODO : FLOAT TO STR
    printf ("JUMP END_STRVAL\n");

    printf ("LABEL END_STRVAL\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");



    /// STRLEN
    printf ("#build in function strlen\n");
    printf ("LABEL strlen\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("STRLEN LF@retval1 LF@%%1\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    /// SUBSTRING
    printf ("#build in function substring\n");
    printf ("LABEL substring\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@strlen_substring\n");
    printf ("DEFVAR LF@cmp_substring\n");
    printf ("DEFVAR LF@position_substring\n");
    printf ("MOVE LF@position_substring LF@%%2\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("STRLEN LF@strlen_substring LF@%%1\n");
    printf ("LT LF@cmp_substring LF@%%2 int@0\n");
    printf ("JUMPIFNEQ substring_error LF@cmp_substring bool@false\n");
    printf ("LT LF@cmp_substring LF@%%3 int@0\n");
    printf ("JUMPIFNEQ substring_error LF@cmp_substring bool@false\n");
    printf ("GT LF@cmp_substring LF@%%2 LF@%%3\n");
    printf ("JUMPIFNEQ substring_error LF@cmp_substring bool@false\n");
    printf ("GT LF@cmp_substring LF@%%3 LF@strlen_substring\n");
    printf ("JUMPIFNEQ substring_error LF@cmp_substring bool@false\n");
    printf ("ADD LF@strlen_substring LF@strlen_substring int@1\n");
    printf ("GT LF@cmp_substring LF@%%2 LF@strlen_substring\n");
    printf ("JUMPIFNEQ substring_error LF@cmp_substring bool@false\n");

    printf ("LABEL do_while_substring\n");
    printf ("SETCHAR LF@retval1 LF@%%1 LF@position_substring\n");
    printf ("JUMPIFEQ end_substring LF@position_substring LF@%%3\n");
    printf ("ADD LF@position_substring LF@position_substring int@1\n");
    printf ("JUMP do_while_substring\n");

    printf ("LABEL substring_error\n");
    printf ("MOVE LF@retval1 nil@nil\n");
    printf ("LABEL end_substring\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    /// ORD
    printf ("#build in function ord\n");
    printf ("LABEL ord\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@strlen_ord\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("STRLEN LF@strlen_ord LF@%%1\n");
    printf ("JUMPIFEQ error_ord LF@strlen_ord int@0\n");
    printf ("SETCHAR LF@retval1 int@0 LF@%%1\n");
    printf ("STRI2INT LF@retval1 LF@retval1 int@0\n");
    printf ("JUMP end_ord\n");
    printf ("LABEL error_ord\n");
    printf ("MOVE LF@retval1 int@0\n");
    printf ("LABEL end_ord\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");

    /// CHR
    printf ("#build in function chr\n");
    printf ("LABEL chr\n");
    printf ("PUSHFRAME\n");
    printf ("DEFVAR LF@retval1\n");
    printf ("INT2CHAR LF@retval1 LF@%%1\n");
    printf ("POPFRAME\n");
    printf ("RETURN\n");




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

void print_op(Syntactic_data_ptr data, int index){
    switch((*data).buffer.token[index]->type){
        case(TYPE_PLUS):
            printf("ADD ");
            break;
        case(TYPE_MUL):
            printf("MUL ");
            break;
        case(TYPE_CONCAT):
            printf("CONCAT ");
            break;
        case(TYPE_MINUS):
            printf("SUB ");
            break;
        case(TYPE_DIV):
            printf("DIV ");
            break;
        default:
            printf("at this index of buffer is no operation\n");
            break;
    }
    return;

}