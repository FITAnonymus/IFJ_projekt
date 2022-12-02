//
// Created by samuel on 19.10.2022.
//


/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of syntactic analysand.
    *
    * @author Samuel Simun <xsimun04@stud.fit.vutbr.cz>
    */


#include "gramatic_rules.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>
#include "token_buffer.h"
#include "semantics.h"
#include "generator.h"


#define FALSE 0
#define TRUE 1


/**
 * @brief Function for deallocating all sources
 * the function handles end of program - free all allocated memory
 *
 * @param Syntactic_data_ptr -  Data set which will be freed
 * @return void
 */
void Destroy_data(Syntactic_data_ptr to_delete) {

    if (to_delete == NULL) {
        return;
    }

    free_table(to_delete->main_var);
    free_ptable(to_delete->function_var);
    free_token_buffer(&to_delete->buffer);
    free(to_delete);
}


/**
 * @brief Function handles unexpected end of parser
 * the function handles program error -> calling Destroy data and exiting with
 * with error code
 *
 * @param int
 * @param Syntactic_data_ptr
 * @return void
 */
void Program_Error(int error, Syntactic_data_ptr data){
    Destroy_data(data);
    printf("Program skoncil s hodnotou : %d\n",error);
    exit(error);
}


/**
 * @brief Function of initializing data sources
 * Function allocates data
 * sources and sets to default values
 *
 * @return Syntactic_data_ptr
 */
Syntactic_data_ptr Init_data(void){
    Syntactic_data_ptr data_ptr = malloc(sizeof(Syntactic_data));
    if (data_ptr == NULL){
        exit(ERR_INTERNAL);
    }

    if (init_token_buffer(&data_ptr->buffer))
        Program_Error(ERR_INTERNAL, data_ptr);

    if (create_ptable(1543, &(data_ptr->function_var)))
        Program_Error(ERR_INTERNAL, data_ptr);

    if (create_table(1543, &(data_ptr->main_var)))
        Program_Error(ERR_INTERNAL, data_ptr);

    data_ptr->inside_function = FALSE;
    data_ptr->used_var = NULL;
    data_ptr->local_var = NULL;

    return data_ptr;
}


/**
 * @brief Function get new token from file
 * Function get new token from file and return it for next processing
 *
 * @param Syntactic_data_ptr
 * @return token_struct token
 */
Token_struct Get_token(Syntactic_data_ptr data){
    Token_struct * p_token = init_token();

    get_next_token(p_token);
    Insert_to_buffer(p_token,data);
    return *p_token;
}

/**
 * @brief Function which add given token to buffer
 * Function handles token, push it into buffer, which is taken by generator
 *
 * @see buffer.c
 * @param token
 * @param Syntactic_data_ptr
 * @return void
 */
void Insert_to_buffer(Token_struct *token, Syntactic_data_ptr data){
    if (add_token_buffer(token, &data->buffer))
        Program_Error(ERR_INTERNAL, data);
}

/**
 * @brief Function handles start of program
 * Function handles start tokens and analyze them, set strict_types
 *
 * @param token start token
 * @param Syntactic_data_ptr
 * @return Error value (SYNTAX_OK or ERR_SYNTAX)
 */
int Validate_program(Token_struct token, Syntactic_data_ptr data){

    return SYNTAX_OK;

}

/**
 * @brief Function handles default
 * Function handles default functions which are added to function hash table
 *
 * @param Syntactic_data_ptr
 * @return Error_code
 */
void add_default_functions(Syntactic_data_ptr data){
    return;
}

/**
 * @brief Function handles start of command with keyword function
 * Function handles token Function by calling function from gramatic_rules.c
 *
 * @see gramatic_rules.c
 * @param Syntactic_data_ptr
 * @return void
 */
int Handle_function_dec(Syntactic_data_ptr data){
    /// Create local sym_table for function

    return SYNTAX_OK;

}


/**
 * @brief Function handles start of command with keyword if
 * Function handles token Function by calling function from gramatic_rules.c
 *
 * @see gramatic_rules.c
 * @param Syntactic_data_ptr
 * @return void
 */
int Handle_if(Syntactic_data_ptr data){



    return SYNTAX_OK;
}


/**
 * @brief Function handles start of command with keyword while
 * Function handles token Function by calling function from gramatic_rules.c
 *
 * @see gramatic_rules.c
 * @param Syntactic_data_ptr
 * @return void
 */
int Handle_while(Syntactic_data_ptr data){



    return SYNTAX_OK;
}


/**
 * @brief Function handles start of command with keyword Int
 * Function handles token Function by calling function from gramatic_rules.c
 *
 * @see gramatic_rules.c
 * @param Syntactic_data_ptr
 * @return void
 */
int Handle_expression(Token_struct token, Syntactic_data_ptr data){




    return SYNTAX_OK;
}


/**
 * @brief Function handles start of calling function
 * Function handle calling function
 *
 * @param Syntactic_data_ptr
 * @return int Error status
 */
int Handle_function(Syntactic_data_ptr data){





    return SYNTAX_OK;
}




/**
 * @brief Main function for Syntactic / Semantic analyze
 *
 * @param Syntactic_data_ptr
 * @return int Error status
 */
int parser(Syntactic_data_ptr data){
    Token_struct token;

    while(token.type != TYPE_PROLOG_END && token.type != TYPE_EOF) {
           token = Get_token(data);
           Insert_to_buffer(&token, data);
    }

    return SYNTAX_OK;
}


int main(void){
    Syntactic_data_ptr data = Init_data();
    add_default_functions(data);


    parser(data);

    generator(data);
    Destroy_data(data);
    return 0;
}



