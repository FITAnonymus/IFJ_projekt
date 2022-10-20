/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library for lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include <stdio.h>
#include "buffer.c"///todo buffer.h
//#include <math.h>

/**
 * @struct Types of lexemes which can be loaded
 */
typedef enum {
    TYPE_EMPTY,
   // TYPE_ERROR,
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
    //TYPE_EOL,
    /// operations
    TYPE_COLON,
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
    TYPE_BRACE_RIGHT, ///CURL BRACES
    TYPE_BRACE_LEFT,
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
}token_struct_attribute;

/**
 *  @struct Token - unit representing one lexeme
 */
typedef struct token_struct{
    token_type type;
    token_struct_attribute *attribute;
}token_struct;

/**
 * @brief Main function of lexical analysis/scanner
 * the function is loading characters from stdin and matches int with known lexemes
 *
 * @param token
 * @return 0 in case of loading lexeme, 1 in case of lexical error
 */
int get_next_token(token_struct *token);


/**
 * @brief Function to convert string to INTEGER value and store it in token attribute
 * @param buf Buffer - declared in buffer.h
 * @param token Token - destination to store the value
 */
int token_int(Buffer *buf, token_struct *token);

/**
 * @brief Function to convert string to FLOAT value and store it in token attribute
 * @param buf Buffer - declared in buffer.h
 * @param token Token - destination to store the value
 */
int token_float(Buffer *buf, token_struct *token);

/**
 * @brief Function determines whether is given identifier keyword or function id
 * @param buf buffer for identification
 */
void identify(Buffer *buf, token_struct *token);


/**
 * @brief Function for converting octal numbers to decimal, used in string processing
 * @param octalNumber octal number to convert
 * @return decimal number
 */
int convertOctalToDecimal(int octalNumber);

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
    //STATE_INT,
   // STATE_FLOAT,
    STATE_BEGIN_ESCAPE,
    STATE_OCTAL,
    STATE_HEX,
    STATE_NUM,
    STATE_NUM_E,
    STATE_FLOAT,
    STATE_FLOAT_E,
    STATE_EXP_SIGN,
    STATE_EXP_SIGN_F,
}scanner_state;