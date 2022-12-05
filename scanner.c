
/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of functions providing lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include "scanner.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

Token_struct * init_token(){
    Token_struct * token;
    token = malloc(sizeof (Token_struct) );
    Buffer * buf = (Buffer *) malloc(sizeof (Buffer));
       if(!buf || !token){
             return NULL;
        }
     init_buffer(buf);

    token->type = TYPE_EMPTY;
    token->buf = buf;
    return token;
}

void identify(Token_struct *token){

    if(cmp_string_buffer("else", token->buf)==0){ ///cmp returns null in equality, that is the reason for the negation at the beginning
        token->type = KEYWORD_ELSE;
    }
    else if(cmp_string_buffer("float", token->buf)==0){
        token->type = KEYWORD_FLOAT;
    }
    else if(cmp_string_buffer("function", token->buf)==0){
        token->type = KEYWORD_FUNCTION;
    }
    else if(cmp_string_buffer("if", token->buf)==0){
        token->type = KEYWORD_IF;
    }
    else if(cmp_string_buffer("int", token->buf)==0){
        token->type = KEYWORD_INT;
    }
    else if(cmp_string_buffer("null", token->buf)==0){
        token->type = KEYWORD_NULL;
    }
    else if(cmp_string_buffer("return", token->buf)==0){
        token->type = KEYWORD_RETURN;
    }
    else if(cmp_string_buffer("string", token->buf)==0){
        token->type = KEYWORD_STRING;
    }
    else if(cmp_string_buffer("void", token->buf)==0){
        token->type = KEYWORD_VOID;
    }
    else if(cmp_string_buffer("while", token->buf)==0){
        token->type = KEYWORD_WHILE;
    }
    else {
        token->type = TYPE_FUNCTION_ID;
    }

}

int get_next_token(Token_struct *token) {
    ///support variables
    char c;                       ///loaded character
    int current = STATE_START;    ///current state of finite state machine
    int oct_cnt;              ///number of octal numbers loaded
    int hex_cnt;              ///number of hexadecimal numbers loaded
    char num_to_convert[3];       ///octal or hexadecimal number intended for conversion
    int prolog_index = 0;         ///number of prolog characters loaded
    bool first = true;            ///control of the first character of identifier
    bool exp_sign = false;        ///control whether was loaded only one sign per number

    while (1) { ///main loop for loading the input characters

        c = getc(stdin);

        switch (current) {
            case (STATE_START):
                if ((c == ' ') || (c == '\n')) { current = STATE_START; }  ///EOL+whitespaces

                else if (c == '(') {
                    token->type = TYPE_PAR_LEFT;
                    return TOKEN_OK;
                }

                else if (c == EOF) {
                    token->type = TYPE_EOF;
                    return TOKEN_OK;
                }

                else if (c == ')') {
                    token->type = TYPE_PAR_RIGHT;
                    return TOKEN_OK;
                }

                else if (c == '*') {
                    token->type = TYPE_MUL;
                    return TOKEN_OK;
                }

                else if (c == '+') {
                    token->type = TYPE_PLUS;
                    return TOKEN_OK;
                }

                else if (c == '-') {
                    token->type = TYPE_MINUS;
                    return TOKEN_OK;

                }

                else if (c == '.') {
                    token->type = TYPE_CONCAT;
                    return TOKEN_OK;
                }

                else if (c == ':') {
                    token->type = TYPE_COLON;
                    return TOKEN_OK;
                }

                else if (c == '{') {
                    token->type = TYPE_BRACE_LEFT;
                    return TOKEN_OK;
                }

                else if (c == '}') {
                    token->type = TYPE_BRACE_RIGHT;
                    return TOKEN_OK;
                }

                else if (c == ';') {
                    token->type = TYPE_SEMICOLON;
                    return TOKEN_OK;
                }

                else if (c == ',') {
                    token->type = TYPE_COMMA;
                    return TOKEN_OK;
                }

                else if (c == '!') { current = STATE_EXCLAMATION; }

                else if (c == '>') { current = STATE_GREATER; }

                else if (c == '<') { current = STATE_LOWER; }

                else if (c == '=') { current = STATE_EQUAL; }

                else if (c == '$') { current = STATE_BEGIN_VAR; }

                else if (c == '/') { current = STATE_BACKSLASH; }

                else if (c == '?') { current = STATE_QUESTION_MARK; }

                else if (c == '"') { current = STATE_BEGIN_STRING; }


                else  if (isdigit(c)) {
                    ungetc(c, stdin);
                    current = STATE_NUM;
                } ///number

               else if (isalpha(c) || c == '_') {
                    ungetc(c, stdin);
                    current = STATE_FUN_ID_KEYWORD;
                } /// function ID or keyword

                else{
                    return ERR_LEX;
                }

                break;

            case (STATE_EXCLAMATION):
                if (c == '=') { current = STATE_EXCLAMATION_EQ; }
                break;

            case (STATE_EXCLAMATION_EQ):
                if (c == '=') {
                    token->type = TYPE_COMPARE_NEG;
                    return TOKEN_OK;
                } else {return ERR_LEX;} ///sequence != is not possible
                break;

            case (STATE_LOWER):
                if (c == '=') {
                    token->type = TYPE_LOWER_EQ;
                    return TOKEN_OK;
                }
                else if(c == '?') {
                    current = STATE_PROLOG;
                }
                else {
                    token->type = TYPE_LOWER;
                    ungetc(c, stdin);
                    return TOKEN_OK;
                }
                break;

            case(STATE_PROLOG):
                if(add_to_buffer(c ,token->buf)!= 0){return ERR_INTERNAL;}
                prolog_index++;
                if(prolog_index == 3){

                    if(cmp_string_buffer("php",token->buf) ==0)
                    {token->type = TYPE_PROLOG_START;
                        return TOKEN_OK;}
                    else{return ERR_LEX;}
                }
                current = STATE_PROLOG;
                break;

            case (STATE_GREATER):
                if (c == '=') {
                    token->type = TYPE_GREATER_EQ;
                    return TOKEN_OK;
                } else {
                    token->type = TYPE_GREATER;
                    ungetc(c, stdin);
                    return TOKEN_OK;
                }
                break;

            case (STATE_EQUAL):
                if (c == '=') { current = STATE_DOUBLE_EQUAL; }
                else {
                    {
                        token->type = TYPE_ASSIGN;
                        ungetc(c, stdin);
                        return TOKEN_OK;
                    }
                }
                break;

            case (STATE_DOUBLE_EQUAL):
                if (c == '=') {
                    {
                        token->type = TYPE_COMPARE;
                        return TOKEN_OK;
                    }
                } else { return ERR_LEX; } /// double equal is not possible

                break;

            case (STATE_BEGIN_VAR):

                if(((first == true)&&((isalpha(c)||(c == '_'))))||((first == false)&&((isalnum(c)||(c == '_')))))
                {    first = false;
                     /// add char to buffer
                    if (add_to_buffer(c, token->buf) != 0) ///return only in case of an error
                    {
                        return ERR_INTERNAL;
                    }
                    ///keep adding character to variable

                    current = STATE_BEGIN_VAR;
                } else if (first==false){ ///some chars of the var were loaded

                    ungetc(c, stdin);
                    token->type = TYPE_VARIABLE_ID;
                    return TOKEN_OK;
                }else{
                    return ERR_LEX; ///unfulfilled condition for the first char of var
                }

                break;

            case (STATE_BACKSLASH):
                if (c == '*') { ///beginning of a block comment

                    current = STATE_BLOCK_COMMENT;
                } else if (c == '/') {///single line comment

                    current = STATE_COMMENT;

                } else { /// division

                    ungetc(c, stdin);
                    token->type = TYPE_DIV;
                    return TOKEN_OK;
                }
                break;

            case (STATE_COMMENT):
                if (c == '\n') { ///until eol

                    current = STATE_START;
                }
                else if (c == EOF) { ///eof in comment
                    token->type = TYPE_EOF;
                    return TOKEN_OK;
                }
                else {
                    current = STATE_COMMENT; ///skipping chars and staying in comment mode
                }
                break;

            case (STATE_BLOCK_COMMENT):
                if (c == '*') {

                    current = STATE_END_BLOCK_COMMENT; /// possible end of comment

                } else if (c == EOF)///eof in comment
                {

                    return ERR_LEX;
                }
                else {
                    current = STATE_BLOCK_COMMENT; ///skipping chars and staying in comment mode
                }
                break;


            case (STATE_END_BLOCK_COMMENT):
                if (c == '/') {
                    current = STATE_START; /// block comment ended
                } else {
                    current = STATE_BLOCK_COMMENT; ///continue in block comment
                }
                break;

            case (STATE_QUESTION_MARK):
                if (c == '>') {
                   current = STATE_CHECK_EOF; ///we will check whether the is something behind the epilog
                   break;
                }
                if ((add_to_buffer(c, token->buf)) != 0) {///add char to buffer
                    printf("here");
                    return ERR_INTERNAL;
                }else{

                    if (cmp_string_buffer("string", token->buf) == 0) {

                        token->type = KEYWORD_STRING_Q;
                        return TOKEN_OK;

                    }else if ((cmp_string_buffer("int", token->buf))== 0) {

                        token->type = KEYWORD_INT_Q;
                        return TOKEN_OK;

                    } else if (cmp_string_buffer("float", token->buf)== 0) {

                        token->type = KEYWORD_FLOAT_Q;
                        return TOKEN_OK;
                    }
                    current = STATE_QUESTION_MARK;
                }
                break;

            case( STATE_CHECK_EOF):
                if(c != EOF){
                    return  ERR_LEX; ///chars after epilog
                }
                token->type = TYPE_PROLOG_END; ///epilog ok
                return TOKEN_OK;


            case (STATE_BEGIN_STRING):

                if (c < 32) { /// special char which is not possible to type directly, some of these chars are handled via escape sequence
                    return ERR_LEX;
                }

                if (c == 92) {

                    current = STATE_BEGIN_ESCAPE;
                    break;
                } ///start of escape sequence , break => so the backslash wont be written in string

                if (c == '"') { ///end of string - token complete

                    token->type = TYPE_STRING;
                    return TOKEN_OK;

                }

                if (add_to_buffer(c, token->buf) != 0) {  ///add char to buffer
                    return ERR_INTERNAL;///memory allocation fail
                }
                break;

            case (STATE_BEGIN_ESCAPE):

                if (c == 'x') { /// xdd
                    hex_cnt =0;
                    current = STATE_HEX;


                }
                else if (isdigit(c)) {/// ddd
                    ungetc(c, stdin); ///we need to reload the value for checking the real value
                    oct_cnt =0;
                    current = STATE_OCTAL;


                }
                else if (c == 't') { ///tab Ascii code 9
                    if (add_to_buffer(9, token->buf)!=0) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                    current = STATE_BEGIN_STRING;
                }
                else if (c == '"') { ///double quote  Ascii code 34
                    if (add_to_buffer(34, token->buf)!=0) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                    current = STATE_BEGIN_STRING;
                }
               else  if (c == 92) { ///backslash ascii code 92
                    if (add_to_buffer(92, token->buf)!=0) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                    current = STATE_BEGIN_STRING;
                }
               else if (c == '$') { ///dollar
                    if (add_to_buffer('$', token->buf)!=0) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                    current = STATE_BEGIN_STRING;
                }
                else if (c == 'n') { ///line feed
                    if (add_to_buffer(10, token->buf)!=0) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                    current = STATE_BEGIN_STRING;
                }
                else{ ///case when the sequence dont max any escape sequence described in the task so the input is written as whole in the buffer
                    current = STATE_BEGIN_STRING;
                }

                break;

            case (STATE_OCTAL):
                if(isdigit(c) && (oct_cnt < 3)){ ///still loading the correct octal number, continue loading
                     num_to_convert[oct_cnt] = c;
                     oct_cnt++;
                     current = STATE_OCTAL;
                }
                else if(oct_cnt >= 3){ ///end of octal number, add char to buffer, get back to loading string  ungetc(c, stdin);
                    ungetc(c, stdin);
                    add_to_buffer(strtol(num_to_convert,NULL, 8), token->buf);
                    current = STATE_BEGIN_STRING;
                }
                else if(!isdigit(c)){ ///wrong character, expected rest of the octal number
                    return ERR_LEX;
                }

                break;

            case (STATE_HEX):

                if(!isdigit(c) && hex_cnt < 2){ ///check for valid hexadecimal input

                    if(c < 'A' || c> 'F'){
                        return ERR_LEX;
                    }
                }
                if(isalnum(c) && hex_cnt < 2){ ///still loading the correct hexadecimal number, continue loading
                    num_to_convert[hex_cnt] = c;
                    hex_cnt++;
                    current = STATE_HEX;
                }
                else if(hex_cnt >= 2){ ///end of hexadecimal number, add char to buffer, get back to loading string
                    ungetc(c, stdin);
                    add_to_buffer(strtol(num_to_convert,NULL, 16), token->buf);
                    current = STATE_BEGIN_STRING;
                }
                else if(!isdigit(c)){ ///wrong character, expected rest of the hexadecimal number
                    return ERR_LEX;
                }

                break;

            case(STATE_NUM):

                 if(tolower(c) == 'e'){
                     current = STATE_FIRST_EXPONENT;
                     if(add_to_buffer(c, token->buf) != 0){
                         return ERR_INTERNAL;
                     }
                     break;

                }
                 else if(c == '.'){
                     current = STATE_FIRST_DECIMAL;
                     if(add_to_buffer(c, token->buf) != 0){
                         return ERR_INTERNAL;
                     }
                     break;
                 }
                 else if(isdigit(c)){ ///add to buf continue loading
                     if(add_to_buffer(c, token->buf) != 0){
                         return ERR_INTERNAL;
                     }
                     current = STATE_NUM;
                 }
                else{ ///end of numerical input

                    ungetc(c, stdin);
                    token->type = TYPE_INTEGER;
                    current = STATE_START;
                    return TOKEN_OK;
                }
                break;

            case(STATE_FIRST_DECIMAL):
               if(!isdigit(c)){
                   return ERR_LEX;
               }
               else{
                   if(add_to_buffer(c, token->buf) != 0){
                       return ERR_INTERNAL;
                   }
                   current = STATE_DECIMAL;
                   break;
               }
            case(STATE_DECIMAL):
                if(tolower(c) == 'e'){ ///add to buffer continue to exponent

                    if(add_to_buffer(c, token->buf) != 0){
                        return ERR_INTERNAL;
                    }
                    current = STATE_FIRST_EXPONENT;
                }
                else if(c == '.'){  ///double dot
                    return ERR_LEX;
                }
                else if(isdigit(c)){ ///normaly continue
                    if(add_to_buffer(c, token->buf) != 0){ ///add to buffer continue to exponent
                        return ERR_INTERNAL;
                    }
                    current = STATE_DECIMAL;
                }
                else{                  ///end of number
                    ungetc(c, stdin);
                    current = STATE_START;
                    token->type = TYPE_FLOAT;
                    return TOKEN_OK; ///float loaded
                }
                break;
            case(STATE_FIRST_EXPONENT):
                if(isdigit(c)){
                    if(add_to_buffer(c, token->buf) != 0){ ///add to buffer continue loading
                        return ERR_INTERNAL;
                    }
                    current = STATE_EXPONENT;
                }
                else if(c == '+' || c == '-'){ ///sign in exponent

                    if(add_to_buffer(c, token->buf) != 0){ ///add to buffer continue loading
                        return ERR_INTERNAL;
                    }
                    exp_sign = true;
                    current = STATE_EXPONENT;
                }else{
                    return ERR_LEX; ///empty exponent
                }

                break;

            case(STATE_EXPONENT):
                    if(isdigit(c)){
                        if(add_to_buffer(c, token->buf) != 0){ ///add to buffer continue loading
                            return ERR_INTERNAL;
                        }
                        current = STATE_EXPONENT;
                    }
                    else if(c == '+' || c == '-'){ ///sign in exponent
                        if(exp_sign == true){
                            return ERR_LEX;
                        }
                        if(add_to_buffer(c, token->buf) != 0){ ///add to buffer continue loading
                            return ERR_INTERNAL;
                        }
                        exp_sign = true;
                        current = STATE_EXPONENT;
                    }
                    else{           ///end of exponent
                        ungetc(c, stdin);
                        current = STATE_START;
                        if(exp_sign == true){
                            token->type = TYPE_FLOAT;
                        }
                        else{
                            token->type = TYPE_INTEGER;
                        }
                        return TOKEN_OK; ///float loaded
                    }
                    break;
            case(STATE_FUN_ID_KEYWORD):


                if(((first == true)&&((isalpha(c)||(c == '_'))))||((first == false)&&((isalnum(c)||(c == '_')))))
                {

                    first = false;
                    /// add char to buffer
                    if (add_to_buffer(c, token->buf) != 0) ///return only in case of an error
                    {
                        return ERR_INTERNAL;
                    }

                    ///keep adding character to variable

                    current = STATE_FUN_ID_KEYWORD;
                }
                else {
                    ungetc(c, stdin);
                    identify(token);
                    return TOKEN_OK;
                }
                break;

        }

    }

}


