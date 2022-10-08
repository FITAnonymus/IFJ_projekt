/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library for lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include <stdio.h>
//#include <buffer.c>

enum token_type{
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
    IDENTIFIER_OR_KEYWORD,
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
};

union token_attribute{

    char string[100];
    int integer;
    float decimal;

};

typedef struct token{
    enum token_type type;
    union token_attribute *attribute;
}token;

//int load_buffer();
//int free_buffer();
//initialize buffer and unload - dynamic string
int get_next_token(token *token);
int process_string(); //identify keyword or make new token name
int process_int(); //
int process_float();//see insttuctions !!!!!

//main function with while
//prototypes of processing functions
// get source file

enum scanner_state{
    STATE_START,
    STATE_DIV,
    STATE_LEFT_PAR,
    STATE_RIGHT_PAR,
    STATE_MUL,
    STATE_CONCAT,
    STATE_QUESTION_MARK,
    STATE_BEGIN_PROLOG,
    STATE_END_PROLOG,
    STATE_BEGIN_VAR, // when start state receives a $
    STATE_EQUAL,
    STATE_DOUBLE_EQUAL,
    STATE_EXCLAMATION,
    STATE_EXCLMATION_EQ,
    STATE_LOWER,
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