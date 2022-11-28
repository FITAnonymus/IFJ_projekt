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
int generator(syntactic_data_ptr data);

/**
 * @struct Stack to store labels
 * Structure is implemented as a linked list.
 * It is used in generator to determine, which label to print, in nested conditions and loops.
 */
struct Label {
    int id;
    struct Label *next;
};

/**
 * Pushing labels on the top the label list
 * @param 0 in case of sucess, otherwise error internal
 */
int push_label(int value);

/**
 * Pop labels from the top of the label list
 * @return positive integer id of label, and minus one in case o f ERR-INTERNAL
 */
int pop_label();

bool GF; ///global frame indicator
bool LF; ///local frame indicator
bool TF; ///temporary frame indicator

/**
 * Function generates begining of if statement.
 * Using generate label, generate condition
 * @param data
 * @return 0 in case of success, otherwise ERR_INTERNAL
 */
int gen_if(syntactic_data_ptr data);

/**
 * Function generates begining of else statement.
 * Using generate label
 * @param data
 * @return 0 in case of success, otherwise ERR_INTERNAL
 */
int gen_else(syntactic_data_ptr data);

/**
 * Function generates begining of while statement.
 * Using generate label, generate condition
 * @param data
 * @return 0 in case of success, otherwise ERR_INTERNAL
 */
int gen_while(syntactic_data_ptr data);

/**
 * Function generates end of while statement.
 * Using generate label
 * @param data
 * @return
 */
void gen_end_while(syntactic_data_ptr data);

/**
 * Function generates declaration of function
 * Using generate label
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */
int gen_function(syntactic_data_ptr data);

/**
 * Function generates declaration of function
 * Using generate label
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */
int gen_call_function(syntactic_data_ptr data);

/**
 * Function generates unique label id and stores it in the list
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */
void generate_label(syntactic_data_ptr data, int index);

/**
 * Function generates condition and appropriate jump
 * @param data
 * @return  0 in case of success, otherwise ERR_INTERNAL
 */

int generate_condition(syntactic_data_ptr data);

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






