#ifndef GENERATOR_H
#define GENERATOR_H

/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    * @file generator.h
    * @brief Code generator library.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */
#include "token_buffer.h"
#include "syntactic.h"
#include <stdbool.h>
#include "error.h"
#include <stdio.h>

/**
 * @struct Label is string one label
 */
typedef struct stack_label{
    int label;
    struct stack_label * next;

}Stack_label;
/**
 * @struct Stack to store labels
 * Structure is implemented as a linked list.
 * It is used in generator to determine, which label to print, in nested conditions and loops.
 */
typedef struct generator_stack{
    Stack_label* top;
}Generator_stack;

/**
 * @struct Variable name + pointer to another
 */
typedef struct stack_var{
    Buffer *buf;
    struct stack_var * next;

}Stack_var;
/**
 * @struct Stack to store variables
 * Structure is implemented as a linked list.
 *
 */
typedef struct gen_stack_var{
    Stack_var* top;
}Gen_stack_var;

/**
 * Main function which is processing given input
 * @param data Syntactic data passed from parser
 * @return 0 in case of no problem, other wise ERR_INTERNAL
 */
int generator(Syntactic_data_ptr data);

bool GF; ///global frame indicator
bool LF; ///local frame indicator
bool TF; ///temporary frame indicator

/**
 * Function generates unique label id and stores it in the list
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */
int generate_label( int index);

/**
 * Function generates condition and appropriate jump
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */

void generate_condition(Syntactic_data_ptr data, int index,  Generator_stack *if_stack, bool in_while);

/**
 * Generates start of the program
 *
 */
void generate_start();

/**
 * prints content of tokens buffer, respekting the rules of ifjcode22 - see escape sequences in instructions
 */
void print_string(Buffer *buf);

/**
 * if the given prolog contains a main function we need to print it at the top of the programe
 * task : iterate through the token buffer if found main print main and return back to the start
 */
void print_main();

/**
 * @brief  Depending on actual frame prints (gf.lf or tf) and @
 * must be folowed by print_string meaning a variable name
 */
void print_frame();
/**
 * Function prints a floating point number in the syntax of Ifjcode22
 * @param buf  buffer to be printed
 */
void print_float(Buffer *buf);

/**
 * End of instruction - line feed
 */
void end();

/**
 * Depending on whether the program contains main function, the function print_main,
 * will print a jump to main at the start of the program
 * @param data
 */
void print_main(Syntactic_data_ptr data);

/**
 * @brief Stack_pop_label is used to pop label from appropriate stack
 * @param stack
 * @return id of the label on the top of the stack
 */
int stack_pop_label(Generator_stack * stack);

/**
 * @brief Stack_push_label stores given label on the top of stack
 * @param stack Target stack
 * @param label Value to be pushed on the stack
 * @return 0 in case of success, ERR_INTERNAL in case of malloc fail
 */

int stack_push_label(Generator_stack * stack, int label);
/**
 * @brief Free_label_stack correctly destroys given stack
 * @param stack stack to be deallocated
 */

void free_label_stack(Generator_stack * stack);
/**
 * @brief Print operand depending on its type
 * @param data syntactic data
 * @param i index of the operand in token buffer
 */
void print_operand(Syntactic_data_ptr data, int i);

/**
 * @grief Generates build in functions
 */
void generate_build_in();

void free_var_stack(Gen_stack_var *stack);
bool declared(Gen_stack_var *stack, Buffer *buf);
int add_var(Gen_stack_var *stack, Buffer *buf);

void print_op(Syntactic_data_ptr data, int index);


/// arithmetic expression
int expression(Syntactic_data_ptr data, int index);
int Postfix_conv(Token_buffer *input, Token_buffer *output, int index);
int compute(Token_buffer * output_from_postfix);

#endif