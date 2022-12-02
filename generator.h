/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
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
 * @brief
 * @param data
 * @param i
 */
void print_operand(Syntactic_data_ptr data, int i);

///ARITHMETIC OPERATIONS HANDLING

///ridi zpracovani vyrazu
void generate_expression(Syntactic_data_ptr data, int index);

///najde nejvnitrnejsi zavorku
int find_sub_exp(Syntactic_data_ptr data, int index);

///najde operand s nejvyssi prioritou
int find_operand(Syntactic_data_ptr data, int index);

///vypocita a nahradit vysledek docasnou hodnotou
int compute(Syntactic_data_ptr data, int index);