/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library for stack, which is used in syntactic bottom-up analysis.
    * For maintain structures dynamic feature, is implemented as a linked list.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */
#include "scanner.h"
#include "expression.h"


#ifndef SYNTACTIC_STACK_H
#define SYNTACTIC_STACK_H

/**
 * @struct One cell of a stack
 */
typedef struct stack_item{
    Token_struct * token;
    struct stack_item * next;
    Relation relation;
    int stop;
    StackTop type;
}stack_item;

/**
 * @struct Struct representing a stack as the linked list of items
 */
typedef struct stack{
    struct stack_item* top;
}Stack;

/**
 * Initialization of stack
 * @param stack The stack, which we currently work with.
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

int stack_push(Stack * stack, Token_struct *token);


/**
 * Free allocated memory for stack and destroys its structure
 * @param stack Pointer to the stack for deallocation
 */
void free_stack(Stack  * stack);


#endif