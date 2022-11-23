/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library for lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#ifndef SCANNER_H
#define SCANNER_H

#include <stdlib.h>
#include "buffer.h"


/**
 * @struct Types of lexemes which can be loaded
 */
typedef enum {
    TYPE_EMPTY,

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
    ///declarations ending by ? => can contain null
    KEYWORD_INT_Q,
    KEYWORD_STRING_Q,
    KEYWORD_FLOAT_Q,

    TYPE_FUNCTION_ID, ///function identifier
    TYPE_VARIABLE_ID, ///variable identifier
    ///variable type
    TYPE_INTEGER,
    TYPE_FLOAT,
    TYPE_STRING,
    ///end of file (end of line is skipped)
    TYPE_EOF,
    /// operations and other characters
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

    TYPE_PAR_LEFT, ///basic parenthesis
    TYPE_PAR_RIGHT,
    TYPE_BRACE_RIGHT, ///curl braces
    TYPE_BRACE_LEFT,

    TYPE_COMMA,
    TYPE_SEMICOLON,
    ///prolog
    TYPE_PROLOG_START,
    TYPE_PROLOG_END,


    ///token types for symstack
    STACK_START,  /// <
    STACK_STOP,   /// >
    STACK_REDUCE  /// "="
}token_type;

/**
 *  @struct Token - unit representing one lexeme
 */
typedef struct token_struct{
    token_type type;
    Buffer *buf;

}Token_struct;

/**
 *
 * @return pointer to newly allocated token
 */
Token_struct * init_token();

/**
 * @brief Main function of lexical analysis/scanner
 * the function is loading characters from stdin and matches int with known lexemes
 *
 * @param token
 * @return 0 in case of loading lexeme, 1 in case of lexical error
 */
int get_next_token(Token_struct *token);

/**
 * @brief Function determines whether is given identifier keyword or function id
 * @param buf buffer for identification
 */
void identify(Token_struct *token);

/**
 * @struct Scanner states
 * represents a states of finite state machine, which principle is used in lexeme processing
 */
typedef enum{
    STATE_START,
    STATE_PROLOG,
    STATE_QUESTION_MARK,
    STATE_BEGIN_VAR, /// when start state receives a $
    STATE_EQUAL,
    STATE_DOUBLE_EQUAL,
    STATE_EXCLAMATION,
    STATE_EXCLAMATION_EQ,
    STATE_BACKSLASH,
    STATE_LOWER,
    STATE_GREATER,
    STATE_COMMENT,
    STATE_BLOCK_COMMENT,
    STATE_END_BLOCK_COMMENT,
    STATE_FUN_ID_KEYWORD,
    STATE_BEGIN_STRING,
    STATE_BEGIN_ESCAPE,
    STATE_OCTAL,
    STATE_HEX,
    STATE_NUM,
    STATE_NUM_E,
    STATE_FLOAT,
    STATE_FLOAT_E,
    STATE_EXP_SIGN,
    STATE_EXP_SIGN_F
}scanner_state;
/*
///TODO testing field
char tokens[46][20]={
    "TYPE_MUL",
    "TYPE_DIV",
    "TYPE_PLUS",
    "TYPE_MINUS",
    "TYPE_CONCAT",
    "TYPE_LOWER",
    "TYPE_GREATER",
    "TYPE_LOWER_EQ",
    "TYPE_GREATER_EQ",
    "TYPE_COMPARE",
    "TYPE_COMPARE_NEG",
    "TYPE_PAR_LEFT", ///basic parenthesis
    "TYPE_PAR_RIGHT",
    "TYPE_INTEGER",
    "TYPE_FLOAT",
    "TYPE_STRING",
    "E_$",


    "TYPE_EMPTY",

    ///keywords
    "KEYWORD_ELSE",
    "KEYWORD_FLOAT",
    "KEYWORD_FUNCTION",
    "KEYWORD_IF",
    "KEYWORD_INT",
    "KEYWORD_NULL",
    "KEYWORD_RETURN",
    "KEYWORD_STRING",
    "KEYWORD_VOID",
    "KEYWORD_WHILE",
    ///declarations ending by ? => can contain null
    "KEYWORD_INT_Q",
    "KEYWORD_STRING_Q",
    "KEYWORD_FLOAT_Q",

    "TYPE_FUNCTION_ID", ///function identifier
    "TYPE_VARIABLE_ID", ///variable identifier
    ///variable type
    ///end of file (end of line is skipped)
    "TYPE_EOF",
    /// operations and other characters
    "TYPE_COLON",
    "TYPE_ASSIGN",
    "TYPE_COMPARE_NEG",

    "TYPE_BRACE_RIGHT", ///curl braces
    "TYPE_BRACE_LEFT",

    "TYPE_COMMA",
    "TYPE_SEMICOLON",
    ///prolog
    "TYPE_PROLOG_START",
    "TYPE_PROLOG_END",

    ///token types for symstack
    "STACK_START",  /// <
    "STACK_STOP",   /// >
    "STACK_REDUCE"  /// "="
};
*/
#endif