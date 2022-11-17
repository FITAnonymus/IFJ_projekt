
/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of functions providing lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include <ctype.h> /// includes functions for determining type of loaded data
#include <stdio.h>
#include "scanner.h" /// includes prototypes and list of keywords, states and types of tokens and structure of token itself
///buffer functions are included in scanner.h
#include <stdlib.h>
#include <stdbool.h>

void identify(Buffer *buffer, token_struct *token){

    if(cmp_string_buffer("else", buffer)==0){ ///cmp returns null in equality, that is the reason for the negation at the beginning
        token->type = KEYWORD_ELSE;
    }
    else if(!cmp_string_buffer("float", buffer)){
        token->type = KEYWORD_FLOAT;
    }
    else if(!cmp_string_buffer("function", buffer)){
        token->type = KEYWORD_FUNCTION;
    }
    else if(!cmp_string_buffer("if", buffer)){
        token->type = KEYWORD_IF;
    }
    else if(!cmp_string_buffer("int", buffer)){
        token->type = KEYWORD_INT;
    }
    else if(!cmp_string_buffer("null", buffer)){
        token->type = KEYWORD_NULL;
    }
    else if(!cmp_string_buffer("return", buffer)){
        token->type = KEYWORD_RETURN;
    }
    else if(!cmp_string_buffer("string", buffer)){
        token->type = KEYWORD_STRING;
    }
    else if(!cmp_string_buffer("void", buffer)){
        token->type = KEYWORD_VOID;
    }
    else if(!cmp_string_buffer("while", buffer)){
        token->type = KEYWORD_WHILE;
    }
    else {
        token->type = TYPE_FUNCTION_ID;
    }

}

int main(){ ///TODO TESTING MAIN - REMOVE


    Buffer *buffer;
    Buffer buf;
    buffer =&buf;

    init_buffer(buffer);
    printf("init_buffer_ok\n");
    token_struct *p_token;
    struct token_struct token;
    token.type= TYPE_EMPTY;
    p_token = &token;
    p_token->buf = buffer;

    int result = get_next_token(p_token);

    printf("%d\n", token.type);

    return result;
}

int get_next_token(struct token_struct *token) {
    ///support variables
    char c;                       ///loaded character
    int current = STATE_START;    ///current state of finite state machine
    int oct_cnt = 0;              ///number of octal numbers loaded
    int hex_cnt = 0;              ///number of hexadecimal numbers loaded
    char num_to_convert[3];       ///octal or hexadecimal number intended for conversion
    int prolog_index = 0;         ///number of prolog characters loaded
    bool first = true;            ///control of the first character of identifier
    bool sign = false;            ///control whether was loaded only one sign per number
    bool exp_sign = false;        ///control whether was loaded only one sign per number
    bool dot = false;             ///control whether was loaded only one dot per float
    bool exponent = false;        ///control whether was loaded only one exponent per number
    bool exponent_empty = true;   ///control of empty exponent

    while (1) { ///main loop for loading the input characters

        c = getc(stdin);

        switch (current) {
            case (STATE_START):
                if ((c == ' ') || (c == '\n')) { current = STATE_START; }  ///EOL+whitespaces

                if (c == '(') {
                    token->type = TYPE_PAR_LEFT;
                    return TOKEN_OK;
                }

                if (c == ')') {
                    token->type = TYPE_PAR_RIGHT;
                    return TOKEN_OK;
                }

                if (c == '*') {
                    token->type = TYPE_MUL;
                    return TOKEN_OK;
                }

                if (c == '+') {
                    token->type = TYPE_PLUS;
                    return TOKEN_OK;
                }

                if (c == '-') {
                    token->type = TYPE_MINUS;
                    return TOKEN_OK;
                }

                if (c == '.') {
                    token->type = TYPE_CONCAT;
                    return TOKEN_OK;
                }

                if (c == ':') {
                    token->type = TYPE_COLON;
                    return TOKEN_OK;
                }

                if (c == '{') {
                    token->type = TYPE_BRACE_LEFT;
                    return TOKEN_OK;
                }

                if (c == '}') {
                    token->type = TYPE_BRACE_RIGHT;
                    return TOKEN_OK;
                }

                if (c == ';') {
                    token->type = TYPE_SEMICOLON;
                    return TOKEN_OK;
                }

                if (c == ',') {
                    token->type = TYPE_COMMA;
                    return TOKEN_OK;
                }

                if (c == '!') { current = STATE_EXCLAMATION; }

                if (c == '>') { current = STATE_GREATER; }

                if (c == '<') { current = STATE_LOWER; }

                if (c == '=') { current = STATE_EQUAL; }

                if (c == '$') { current = STATE_BEGIN_VAR; }

                if (c == '/') { current = STATE_BACKSLASH; }

                if (c == '?') { current = STATE_QUESTION_MARK; }

                if (c == '"') { current = STATE_BEGIN_STRING; }

                if (isdigit(c)) {
                    ungetc(c, stdin);
                    current = STATE_NUM;
                } ///number

                if (isalpha(c) || c == '_') {
                    ungetc(c, stdin);
                    current = STATE_FUN_ID_KEYWORD;
                } /// function ID or keyword

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

                if(isalnum(c) || (c =='_'))
                {
                     /// add char to buffer
                    if (add_to_buffer(c, token->buf) != 0) ///return only in case of an error
                    {
                        return ERR_INTERNAL;
                    }
                    ///keep adding character to variable
                    first = false;///todo aby vyhovoval podmince
                    current = STATE_BEGIN_VAR;
                } else {

                    ungetc(c, stdin);
                    token->type = TYPE_VARIABLE_ID;
                    return ERR_LEX; ///dollar can not be typed directly
                }

                break;

            case (STATE_BACKSLASH):
                if (c == '*') { ///beginning of a block comment

                    current = STATE_BLOCK_COMMENT;
                } else if (c == '/') {///single line comment

                    current = STATE_COMMENT;

                } else { /// division

                    token->type = TYPE_DIV;
                    return TOKEN_OK;
                }
                break;

            case (STATE_COMMENT):
                if (c == '\n') { ///until eol

                    current = STATE_START;
                } else if (c == EOF) { ///eof in comment

                    return ERR_LEX;
                } else {
                    current = STATE_COMMENT; ///skipping chars and staying in comment mode
                }
                break;

            case (STATE_BLOCK_COMMENT):
                if (c == '*') {

                    current = STATE_END_BLOCK_COMMENT; /// possible end of comment

                } else if (c == EOF)///eof in comment
                {

                    return ERR_LEX;
                } else {
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
                    token->type = TYPE_PROLOG_END;
                    return TOKEN_OK;
                }
                if ((add_to_buffer(c, token->buf)) != 0) {///add char to buffer

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


            case (STATE_BEGIN_STRING):

                if (c < 32) { /// special char which is not possible to type directly, some of these chars are handled via escape sequence
                    return ERR_LEX;
                }

                if (c == 92) {
                    current = STATE_BEGIN_ESCAPE;
                    break;
                } ///start of escape sequence , break => so the backslash wont be written in string

                if (add_to_buffer(c, token->buf) != 0) {  ///add char to buffer
                    return ERR_INTERNAL;///memory allocation fail
                }

                if (c == '"') { ///end of string - token complete
                    token->type = TYPE_STRING;
                    return TOKEN_OK;

                }

                break;
            case (STATE_BEGIN_ESCAPE):
                if (c == 'x') { /// \xdd
                    current = STATE_HEX;
                }
                else if (isdigit(c)) {/// \ddd
                    ungetc(c, stdin); ///we need to reload the value for checking the real value
                    current = STATE_OCTAL;
                }
                else if (c == 't') { ///tab Ascii code 9
                    if (!add_to_buffer(9, token->buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }

                }
                else if (c == '"') { ///double quote  Ascii code 34
                    if (!add_to_buffer(34, token->buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }
               else  if (c == 92) { ///backslash ascii code 92
                    if (!add_to_buffer(92, token->buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }
               else if (c == '$') { ///dollar
                    if (!add_to_buffer('$', token->buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }
                else if (c == 'n') { ///line feed
                    if (!add_to_buffer(10, token->buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }
                else{ ///case when the sequence dont max any escape sequence described in the task so the input is written as whole in the buffer

                }

                break;

            case (STATE_OCTAL):
                if(isdigit(c) && oct_cnt < 3){ ///still loading the correct octal number, continue loading
                     num_to_convert[oct_cnt] = c;
                     oct_cnt++;
                     current = STATE_OCTAL;
                }
                else if(oct_cnt >= 3){ ///end of octal number, add char to buffer, get back to loading string
                    add_to_buffer(strtol(num_to_convert,NULL, 8), token->buf);
                    current = STATE_BEGIN_STRING;
                }
                else if(!isdigit(c) && oct_cnt < 3){ ///wrong character, expected rest of the octal number
                    return ERR_LEX;
                }

                break;

            case (STATE_HEX):
                 ///todo check hexa rules
                if(isalnum(c) && hex_cnt < 2){ ///still loading the correct hexadecimal number, continue loading
                    num_to_convert[hex_cnt] = c;
                    hex_cnt++;
                    current = STATE_HEX;
                }
                else if(hex_cnt >= 2){ ///end of hexadecimal number, add char to buffer, get back to loading string
                    add_to_buffer(strtol(num_to_convert,NULL, 16), token->buf);
                    current = STATE_BEGIN_STRING;
                }
                else if(!isdigit(c) && oct_cnt < 3){ ///wrong character, expected rest of the hexadecimal number
                    return ERR_LEX;
                }

                break;

            case(STATE_NUM):
                if (isdigit(c)|| tolower(c) == 'e' || c=='.' || c == '+' || c == '-') { ///numerical input
                    ///INPUT CHECK
                    if(tolower(c) == 'e'){
                        if (exponent == true){ ///double exponent in number
                            return ERR_LEX;
                        }
                       exponent = true;
                    }
                    if(exponent == false && (c == '-'|| c == '+')){
                        if(sign == true){ ///two signs in one number
                            return ERR_LEX;
                        }
                        sign = true;
                    }
                    if(c == '.' && exponent == false){
                        if(dot == true){ ///double dot in number
                            return ERR_LEX;
                        }
                        dot = true;
                    }
                    if(exponent == true && (c == '-'|| c == '+')){
                        if(exp_sign == true || exponent_empty == false){ ///two signs in exponent, or sign in nonempty exponent
                            return ERR_LEX;
                        }
                        exp_sign = true;
                    }
                    if(exponent == true && isdigit(c)){
                        exponent_empty = false;
                    }

                    add_to_buffer(c, token->buf);


                }
                else{ ///end of numerical input
                    ungetc(c, stdin);
                    if(exponent_empty == true){
                        return ERR_LEX;
                    }
                    if(dot == true || exp_sign == true || sign == true){ ///one of these chars will make it a float or negative int
                        token->type = TYPE_FLOAT;
                    }
                    else {
                        token->type = TYPE_INTEGER; ///positive int
                    }
                    return TOKEN_OK;
                }
             break;

            case(STATE_FUN_ID_KEYWORD):
                ///same rules as for variable
                /// [( letter  or  '_' ) and   first ]   or [ (number or letter or _) but not first]

                if ((((isalpha(c)) || c == '_') & (first == true)) || ((isalnum(c) || c == '_') & (first = false))) ///fulfilled conditions for identifier
                {
                    /// add char to buffer
                    if (add_to_buffer(c, token->buf) != 0) ///return only in case of an error
                    {
                        return ERR_INTERNAL;
                    }
                    ///keep adding character to variable
                    first = true; // TODO upravit at vyhovuje podminkam pro promennou !!!
                    current = STATE_FUN_ID_KEYWORD;
                }
                else {
                    ungetc(c, stdin);
                    identify(token->buf, token );
                    return TOKEN_OK;
                }
                break;








        }


    }

}


