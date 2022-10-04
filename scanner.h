/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Library for lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include <stdio.h>
#include <buffer.h>

/**
enum keyword{
     //todo maybe not needed
};
*/


enum token_type{
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
    ///variable type
    TYPE_INTEGER,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_NULL,
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
    TYPE_SEMICOLON
};

union token_attribute{
    buffer *string;
    int integer;
    float decimal;
    //todo??  Speciálním případem je hodnota null, pouze u otazniku pred identifikatorem
};

typedef struct token{
    token_type type;
    token_attribute *attribute;
}token;

int load_buffer();
int free_buffer();
//initialize buffer and unload - dynamic string
token get_next_token();//todo depends on graph
int process_string(); //identify keyword or make new token name
int process_int(); //
int process_float();//see insttuctions !!!!!

//main function with while
//prototypes of processing functions
// get source file

enum scanner_state{
    //todo depends on graph
};