
/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library Token_buffer.
    * Token_buffer is a supportive data structure for syntax analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include "scanner.h"

/**
 * @struct Structure used for storing tokens. Implemented as a dynamic field of token structures.
 */
typedef struct {
    token_struct *token;
    unsigned long lenght;
    unsigned long size;
}Token_buffer;

/**
 * @brief Initialize empty token buffer.
 *
 * @param tok_buf Pointer to newly initialized buffer of tokens
 * @return 0 if the operation was successful, ERR_INTERNAL in case of failed allocation
 */
int init_token_buffer(Token_buffer *tok_buf);

/**
 * @brief Addition of one token to token_buffer
 *
 * @param token pointer the token which is supposed to be added to buffer
 * @param tok_buf Pointer to already initialized buffer of tokens
 * @return 0 if the operation was successful, ERR_INTERNAL in case of failed allocation
 */
int add_token_buffer(token_struct *token,Token_buffer *tok_buf);

/**
 * @brief Destroys token_buffer and deallocates all the resources
 *
 * @param tok_buf pointer to token_buffer for disposal
 * @return 0 if the operation was successful, ERR_INTERNAL in case of failed allocation
 */
int free_token_buffer(Token_buffer *tok_buf);