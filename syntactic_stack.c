/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of stack, which is used in syntactic bottom-up analysis.
    * For maintain structures dynamic feature, is implemented as a linked list.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */
#include "syntactic_stack.h"
#include <stdlib.h>
#include "error.h"


void init_stack(Stack  * stack){
    stack->top = NULL; ///pointer to first item is null
}

Token_struct * stack_pop(Stack * stack){

    Stack_item *result = stack->top; ///preparing return value

    Stack_item *to_delete = stack->top; ///deleting first item
    stack->top = stack->top->next; ///keeping the link
    free(to_delete->token);


    return result->token;
}

int stack_push(Stack * stack, Token_struct *token){

    Stack_item *new = (Stack_item *)malloc(sizeof(Stack_item)); ///allocation of new item
    if(!new){
        return ERR_INTERNAL; ///malloc fail
    }
    new->token = token; ///assigning new value
    new->next = stack->top; ///keeping the links
    stack->top = new;

  return TOKEN_OK;
}
void free_stack(Stack * stack){

   if(stack == NULL){
       return;
   }
   while(stack->top != NULL){ ///while stack isn not empty
       Stack_item * to_delete = stack->top; ///prepare item to delete
       stack->top = stack->top->next; ///keep the links
       free(to_delete);  ///delete the item
   }
   stack = NULL; ///deleting finished

}
