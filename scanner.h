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
    ///variable type
    ///end of line + file
    /// arithmetic sign
    ///logical sign --see instructions on page 8+9
    ///brackets comma semicolon

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