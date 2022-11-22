/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of stack, which is used in syntactic bottom-up analysis.
    * For maintain structures dynamic feature, is implemented as a linked list.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */


void init_stack(stack  * stack){
    stack->top = NULL; ///pointer to first item is null
}

stack_item stack_pop(stack * stack){

    stack_item result = *stack->top; ///preparing return value

    stack_item *to_delete = stack->top; ///deleting first item
    stack->top = stack->top->next; ///keeping the link
    free(to_delete);

    return result;
}
int stack_push(stack * stack, Token_struct *token){

    stack_item *new = (stack_item *)malloc(sizeof(struct stack_item)); ///allocation of new item
    if(!new){
        return ERR_INTERNAL; ///malloc fail
    }
    new->token = token; ///assigning new value
    new->next = stack->top; ///keeping the links
    stack->top = new;

  return TOKEN_OK;
}
void free_stack(stack  * stack){

   while(stack->top){ ///while stack isn not empty
       stack_item * to_delete = stack->top; ///prepare item to delete
       stack->top = stack->top->next; ///keep the links
       free(to_delete);  ///delete the item
   }
   stack = NULL; ///deleting finished

}
