/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library for lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include <stdio.h>
#include "buffer.c"///todo buffer.h

/**
 * @struct Types of lexemes which can be loaded
 */
typedef enum {
    TYPE_EMPTY,
    TYPE_ERROR,
    ///keywords
    KEYWORD_ELSE,
    KEYWORD_FLOAT,
    KEYWORD_FUNCTION,
    KEYWORD_IF,
    KEYWORD_INT,
    KEYWORD_NULL,
    KEYWORD_RETURN,
    KEYWORD_STRING,
    KEYWORD_VOID,
    KEYWORD_WHILE,
   // IDENTIFIER_OR_KEYWORD,//TODO REMOVE
    TYPE_FUNCTION_ID,
    TYPE_VARIABLE_ID,
    ///variable type
    TYPE_INTEGER,
    TYPE_FLOAT,
    TYPE_EXPONENTIAL, ///probably superfluous but better to have it
    TYPE_STRING,
    TYPE_NULL,
    TYPE_INTEGER_Q,///types ending "Q" represents situation when data type begins with ? and thus can contain a null value
    TYPE_STRING_Q,
    TYPE_FLOAT_Q,
    ///end of line + file
    TYPE_EOF,
    TYPE_EOL,
    /// operations
    TYPE_ASSIGN,
    TYPE_PLUS,
    TYPE_MINUS,
    TYPE_MUL,
    TYPE_DIV,
    TYPE_CONCAT,
    TYPE_COMPARE,
    TYPE_COMPARE_NEG,
    TYPE_GREATER,
    TYPE_LOWER,
    TYPE_GREATER_EQ,
    TYPE_LOWER_EQ,
    ///brackets comma semicolon
    TYPE_PAR_LEFT,
    TYPE_PAR_RIGHT,
    TYPE_COMMA,
    TYPE_SEMICOLON,
    ///prolog
    TYPE_PROLOG_START,
    TYPE_PROLOG_END
}token_type;

/**
 * @struct Attributes of given token/lexeme (value)
 */
typedef union {
    Buffer *buf;
    int integer;
    float decimal;
}token_attribute;

/**
 *  @struct Token - unit representing one lexeme
 */
typedef struct token{
    token_type type;
    token_attribute *attribute;
}token;

/**
 * @brief Main function of lexical analysis/scanner
 * the function is loading characters from stdin and matches int with known lexemes
 *
 * @param token
 * @return 0 in case of loading lexeme, 1 in case of lexical error
 */
token* get_next_token(token *token);


/**
 * Process string is handling a lexeme which is starting by quotation marks
 * @param c Currently processed character
 * @param buf buffer of current token
 * @return 0 if the operation was successful, 1 in case of lexical error
 */
int process_string(char c, Buffer *buf);

/**
 * Process number is handling a lexeme which is representing a number
 * function can handle integer, float and number with exponent
 *
 * @param c Currently processed character/ in this case a number
 * @param buf buffer of current token
 * @return 0 if the operation was successful, 1 in case of lexical error
 */
int process_number(char c, Buffer *buf);

/**
 * @struct Scanner states
 * represents a states of finite state machine, which principle is used in lexeme processing
 */
enum scanner_state{
    STATE_START,
    //STATE_DIV,
    //STATE_LEFT_PAR,
    //STATE_RIGHT_PAR,
   // STATE_MUL,
   // STATE_CONCAT,
    STATE_QUESTION_MARK,
    STATE_BEGIN_PROLOG,
    STATE_END_PROLOG,
    STATE_BEGIN_VAR, // when start state receives a $
    STATE_EQUAL,
    STATE_DOUBLE_EQUAL,
    STATE_EXCLAMATION,
    STATE_EXCLAMATION_EQ,
    STATE_BACKSLASH,
    STATE_LOWER, ///todo remove superfluous states below
    //STATE_LOWER_EQ,
    //STATE_GREATER_EQ,
    STATE_GREATER,
    STATE_COMMENT,
    STATE_BEGIN_COMMENT,
    STATE_BLOCK_COMMENT,
    STATE_END_BLOCK_COMMENT,
    STATE_FUN_ID_KEYWORD,
    STATE_BEGIN_STRING,
    STATE_END_STRING,
    STATE_INT,
    STATE_FLOAT
}scanner_state;