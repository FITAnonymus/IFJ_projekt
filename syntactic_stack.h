/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    * @file syntactic_stack.h
    * @brief Library for stack, which is used in syntactic bottom-up analysis.
    * For maintain structures dynamic feature, is implemented as a linked list.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */
#ifndef SYNTACTIC_STACK_H
#define SYNTACTIC_STACK_H


#include "scanner.h"
#include "expression.h"

/**
 * @struct One cell of a stack
 */
typedef struct stack_item{
    Token_struct * token;
    struct stack_item * next;
    int relation;
    int stop;
}Stack_item;

/**
 * @struct Struct representing a stack as the linked list of items
 */
typedef struct stack{
     Stack_item* top;
}Stack;

/**
 * Initialization of stack
 * @param stack The stack, which we currently work with.
 * @return void
 */
void init_stack(Stack * stack);

/**
 * Removing an item from the top of the stack and returning its value.
 * @param stack The stack, which we currently work with.
 * @return
 */
Token_struct*  stack_pop(Stack * stack);


/**
 * Adding a new item on the top of the stack.
 * @param stack The stack, which we currently work with.
 * @return In case of success returns zero, otherwise ERR_INTERNAL
 */

int stack_push(Stack * stack, Token_struct *token, int relation, int stop);


/**
 * Free allocated memory for stack and destroys its structure
 * @param stack Pointer to the stack for deallocation
 * @return void
 */
void free_stack(Stack  * stack);


#endif