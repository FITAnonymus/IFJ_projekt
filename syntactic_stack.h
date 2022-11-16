/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library for stack, which is used in syntactic bottom-up analysis.
    * For maintain structures dynamic feature, is implemented as a linked list.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */
#include "scanner.h"
/**
 * @struct One cell of a stack
 */
typedef struct stack_cell{
    token_struct * token;
    struct stack_cell * next;
}stack_cell;

/**
 * Initialization of stack
 * @param stack The stack, which we currently work with.
 */
void init_stack(stack_cell * stack);
/**
 * Removing an item from the top of the stack.
 * @param stack The stack, which we currently work with.
 * @return
 */
int stack_pop(stack_cell* stack);

/**
 * Getting the value from the top of the stack.
 * @param stack The stack, which we currently work with.
 * @return Pointer to a token at the top of the stack, or null in case of an empty stack.
 */
token_struct* stack_top(stack_cell * stack);

/**
 * Adding a new item on the top of the stack.
 * @param stack The stack, which we currently work with.
 * @return In case of success returns zero, otherwise ERR_INTERNAL
 */
int stack_push(stack_cell* stack);

/**
 * Free allocated memory for stack and destroys its structure
 * @param stack Pointer to the stack for deallocation
 */
void free_stack(stack_cell * stack);
