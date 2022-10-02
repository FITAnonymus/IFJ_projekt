/**
 * Projekt: IFJ 2022
 *
 * @Lexical analysis library
 *
 * @authors
 *
 */

#include <stdio.h>
#include <buffer.h>


enum keyword{
 //else, float, function, if, int, null, return, string,
    //void, while
};

enum token_type{
    //end of line/file
    //keyword
  // logical operator
  //arithmetic operator
  // data type identifier
  // (),;
};

union token_attribute{
//buffer - dynamic string
 int integer;
  float decimal; // see instructions in elearning
};

typedef struct token{
//type
//attribute
}token;

int load_buffer();
int free_buffer();
//initialize buffer and unload - dynamic string
token get_next_token();
int process_string(); //identify keyword or make new token name
int process_int(); //
int process_float();//
//main function with while
//prototypes of processing functions
// get source file

enum scanner_state{

};