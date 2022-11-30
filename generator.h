/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Code generator library.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */
#include "token_buffer.h" //buffer operations ?
#include "syntactic.h"  // data
#include <stdbool.h>
#include "error.h"
#include <stdio.h>

/**
 *
 * @param data Syntactic data passed from parser
 * @return 0 in case of no problem, other wise ERR_INTERNAL
 */
int generator(Syntactic_data_ptr data);

/**
 * @struct Stack to store labels
 * Structure is implemented as a linked list.
 * It is used in generator to determine, which label to print, in nested conditions and loops.
 */


bool GF; ///global frame indicator
bool LF; ///local frame indicator
bool TF; ///temporary frame indicator

/**
 * Function generates begining of if statement.
 * Using generate label, generate condition
 * @param data
 * @return 0 in case of success, otherwise ERR_INTERNAL
 */
int gen_if(Syntactic_data_ptr data);

/**
 * Function generates begining of else statement.
 * Using generate label
 * @param data
 * @return 0 in case of success, otherwise ERR_INTERNAL
 */
int gen_else(Syntactic_data_ptr data);

/**
 * Function generates begining of while statement.
 * Using generate label, generate condition
 * @param data
 * @return 0 in case of success, otherwise ERR_INTERNAL
 */
int gen_while(Syntactic_data_ptr data);

/**
 * Function generates end of while statement.
 * Using generate label
 * @param data
 * @return
 */
void gen_end_while(Syntactic_data_ptr data);

/**
 * Function generates declaration of function
 * Using generate label
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */
int gen_function(Syntactic_data_ptr data);

/**
 * Function generates declaration of function
 * Using generate label
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */
int gen_call_function(Syntactic_data_ptr data);

/**
 * Function generates unique label id and stores it in the list
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */
void generate_label(Syntactic_data_ptr data, int index);

/**
 * Function generates condition and appropriate jump
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */

int generate_condition(Syntactic_data_ptr data, int index);

/**
 * Generates start of the program
 *
 */
void generate_start();

/**
 * Generates end of the program
 *
 */
void generate_end();

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
 * depending on actual frame prints (gf.lf or tf) and @
 * must be folowed by print_string meaning a variable name
 */
void print_frame();             ///TODO MAKE DOCUMENTATION FOR THIS MESS
void print_float(Buffer *buf);
void end();
void print_main(Syntactic_data_ptr data);
typedef struct stack_label{
    int label;
    struct stack_label * next;

}Stack_label;

typedef struct generator_stack{
    Stack_label* top;
}Generator_stack;
int stack_pop_label(Generator_stack * stack);
int stack_push_label(Generator_stack * stack, int label);
void free_label_stack(Generator_stack * stack);
void print_operand(Syntactic_data_ptr data, int i);