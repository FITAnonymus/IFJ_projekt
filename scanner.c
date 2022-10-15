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


int token_int(Buffer *buf, token_struct *token){

    char *alloc_check;
    int integer = strtol(buf->buf, &alloc_check,10); ///convert char to number

    if (*alloc_check)  ///allocation fail
    {
        return ERR_INTERNAL;
    }

    token->type = TYPE_INTEGER;  ///select token type
    token->attribute->integer= integer;  ///assign value

    return TOKEN_OK;

}

int convertOctalToDecimal(int octalNumber) {
    int decimalNumber = 0, i = 0;

    while(octalNumber != 0) {
        decimalNumber += (octalNumber%10) * pow(8,i);
        ++i;
        octalNumber/=10;
    }

    i = 1;

    return decimalNumber;
}



void identify(Buffer *buf, token_struct *token){

    if(!cmp_string_buffer("else", buf)){ ///cmp returns null in equality, that is the reason for the negation at the beginning
        token->type = KEYWORD_ELSE;
        token->attribute = NULL; ///no atributes for keyword
    }
    else if(!cmp_string_buffer("float", buf)){
        token->type = KEYWORD_FLOAT;
        token->attribute = NULL;
    }
    else if(!cmp_string_buffer("function", buf)){
        token->type = KEYWORD_FUNCTION;
        token->attribute = NULL;
    }
    else if(!cmp_string_buffer("if", buf)){
        token->type = KEYWORD_IF;
        token->attribute = NULL;
    }
    else if(!cmp_string_buffer("int", buf)){
        token->type = KEYWORD_INT;
        token->attribute = NULL;
    }
    else if(!cmp_string_buffer("null", buf)){
        token->type = KEYWORD_NULL;
        token->attribute = NULL;
    }
    else if(!cmp_string_buffer("return", buf)){
        token->type = KEYWORD_RETURN;
        token->attribute = NULL;
    }
    else if(!cmp_string_buffer("string", buf)){
        token->type = KEYWORD_STRING;
        token->attribute = NULL;
    }
    else if(!cmp_string_buffer("void", buf)){
        token->type = KEYWORD_VOID;
        token->attribute = NULL;
    }
    else if(!cmp_string_buffer("while", buf)){
        token->type = KEYWORD_WHILE;
        token->attribute = NULL;
    }
    else {
        token->type = TYPE_FUNCTION_ID;
        token->attribute->buf->buf = buf->buf;
    }

}

int token_float(Buffer *buf, token_struct *token){

    char *alloc_check;
    int n_float = strtod(buf->buf, &alloc_check); ///convert char to number

    if (*alloc_check)   ///allocation fail
    {
        return ERR_INTERNAL;
    }

    token->type = TYPE_FLOAT; ///select token type
    token->attribute->decimal= n_float;///assign value

    return TOKEN_OK;

}

//todo remove
int main(){

    struct token_struct token1;
    struct token_struct *current_token;
    current_token = &token1;
    current_token->type = TYPE_EMPTY;
    current_token->attribute = NULL;
    int result= get_next_token(current_token);
    printf("Typ tokenu:\n");
    printf("%d\n", current_token->type);
    if(current_token->attribute != NULL){
        printf("ma atribut\n");
    }

    return result;
}

int get_next_token(struct token_struct *token) {
    ///support variables
    char c;
    int current = STATE_START;
    int octal_index;
    int hex_index;
    bool first = true;

    ///string constants for lexical analysis
    char prolog_start[6] = "<?php";
    char char_int[4]="int";
    char char_str[7]="string";
    char char_float[6] ="float";

    ///main loop for loading the characters
    while (1) {

        c = getc(stdin);

        switch (current) {
            case (STATE_START):
                if ((c == ' ') || (c == '\n')) { current = STATE_START; }  ///EOL+whitespaces

                if (c == '(') {
                    token->type = TYPE_PAR_LEFT;
                    token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == ')') {
                    token->type = TYPE_PAR_RIGHT;
                    token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '*') {
                    token->type = TYPE_MUL;
                    token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '+') {
                    token->type = TYPE_PLUS;
                    token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '-') {
                    token->type = TYPE_MINUS;
                    token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '.') {
                    token->type = TYPE_CONCAT;
                    token->attribute = NULL;
                    return TOKEN_OK;
                }

                if(c == ':'){
                    token->type = TYPE_COLON;
                    token->attribute = NULL;
                    return TOKEN_OK;
                }

                if( c== '{'){
                    token->type = TYPE_BRACE_LEFT;
                    token->attribute = NULL;
                    return TOKEN_OK;
                }

                if( c == '}'){
                    token->type = TYPE_BRACE_RIGHT;
                    token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '!') { current = STATE_EXCLAMATION; }

                if (c == '>') { current = STATE_GREATER; }

                if (c == '<') { current = STATE_LOWER; }

                if (c == '=') { current = STATE_EQUAL; }

                if (c == '$') { current = STATE_BEGIN_VAR; }

                if (c == '/') { current = STATE_BACKSLASH; }

                if (c == '?') { current = STATE_QUESTION_MARK; }

                if(c == '"') { current = STATE_BEGIN_STRING; }

                if(isdigit(c)){ ungetc(c, stdin); current = STATE_NUM;} ///number

                if(isalpha(c) || c == '_'){ ungetc(c, stdin); current = STATE_FUN_ID_KEYWORD;} /// function ID or keyword

                break;
            case (STATE_EXCLAMATION):
                if (c == '=') { current = STATE_EXCLAMATION_EQ; }
                break;

            case (STATE_EXCLAMATION_EQ):
                if (c == '=') {
                    token->type = TYPE_COMPARE_NEG;
                    token->attribute = NULL;
                    return TOKEN_OK;
                } else return ERR_LEX; ///!= is not possible
                break;

            case (STATE_LOWER):
                if (c == '=') {
                    token->type = TYPE_LOWER_EQ;
                    token->attribute = NULL;
                    return TOKEN_OK;
                } else {
                    token->type = TYPE_LOWER;
                    token->attribute = NULL;
                    ungetc(c, stdin);
                    return TOKEN_OK;
                }
                break;

            case (STATE_GREATER):
                if (c == '=') {
                    token->type = TYPE_GREATER_EQ;
                    token->attribute = NULL;
                    return TOKEN_OK;
                } else {
                    token->type = TYPE_GREATER;
                    token->attribute = NULL;
                    ungetc(c, stdin);
                    return TOKEN_OK;
                }

                break;

            case (STATE_EQUAL):
                if (c == '=') { current = STATE_DOUBLE_EQUAL; }
                else {
                    {
                        token->type = TYPE_ASSIGN;
                        token->attribute = NULL;
                        ungetc(c, stdin);
                        return TOKEN_OK;
                    }
                }
                break;

            case (STATE_DOUBLE_EQUAL):
                if (c == '=') {
                    {
                        token->type = TYPE_COMPARE;
                        token->attribute = NULL;
                        return TOKEN_OK;
                    }
                } else { return ERR_LEX; } /// double equal is not possible

                break;

            case(STATE_BEGIN_VAR):


                /// [( letter  or  '_' ) and   first ]   or [ (number or letter or _) but not first]
                if ((((isalpha(c)) || c == '_') & (first == true)) || ((isalnum(c) || c == '_') & (first = false))) ///fulfilled conditions for variable
                {
                    int result = add_to_buffer(c, token->attribute->buf); /// add char to buffer
                    if (result != 0) ///return only in case of an error
                    {
                        return result;
                    }
                    ///keep adding character to variable
                    first = false;
                    current = STATE_BEGIN_VAR;
                }
                else {

                        ungetc(c, stdin);
                        return ERR_LEX; ///dollar can not be typed directly
                }
                token->type = TYPE_VARIABLE_ID;

                break;



            case (STATE_BACKSLASH):
                if (c == '*') { ///beginning of a block comment

                    current = STATE_BLOCK_COMMENT;
                }
                else if (c == '/'){      ///single line comment

                    current = STATE_COMMENT;

                } else {              /// division

                    token->type = TYPE_DIV;
                    token->attribute = NULL;
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
                if (c == '*'){

                    current = STATE_END_BLOCK_COMMENT; /// possible end of comment

                }
                else if (c == EOF)///eof in comment
                {

                    return ERR_LEX;
                }
                else{
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
                if( c == '>'){token->type = TYPE_PROLOG_END; token->attribute = NULL;}
                else{
                    if((!isalpha(c))||(c != '<')){ ///unfulfilled condition for prolog start and data types

                        return ERR_LEX;
                    }
                    if (!(add_to_buffer(c, token->attribute->buf))){///add char to buffer

                        return ERR_INTERNAL;
                    }
                    else{
                        if(!cmp_string_buffer(prolog_start,token->attribute->buf))///cmp returns zero in case of success that the reason for the negation
                        {
                            token->type = TYPE_PROLOG_START; token->attribute = NULL;   ///prolog start
                            return TOKEN_OK;
                        }
                        else if(!cmp_string_buffer(char_str,token->attribute->buf)){
                            token->type = TYPE_STRING_Q; token->attribute = NULL;  ///?char
                            return TOKEN_OK;
                        }
                        else if(!cmp_string_buffer(char_int,token->attribute->buf)){
                            token->type = TYPE_INTEGER_Q; token->attribute = NULL;///?int
                            return TOKEN_OK;
                        }
                        else if(!cmp_string_buffer(char_float,token->attribute->buf)){
                            token->type = TYPE_FLOAT_Q; token->attribute = NULL; ///?float
                            return TOKEN_OK;
                        }
                        else{

                            return ERR_LEX;
                        }
                    }

                }
                break;

            case(STATE_BEGIN_STRING):

                if(c <32){ /// special char which is not possible to type directly, some of these chars are handled via escape sequence
                    return ERR_LEX;
                }

                if(c == 92){current = STATE_BEGIN_ESCAPE; break;} ///start of escape sequence , break => so the backslash wont be written in string

                if(c == '"'){ ///end of string - token complete
                    return TOKEN_OK;
                }

                if(!add_to_buffer(c, token->attribute->buf)){  ///add char to buffer
                    return ERR_INTERNAL;///memory allocation fail
                }

                break;
            case(STATE_BEGIN_ESCAPE):
                if(c == 'x'){ /// \xdd
                    current = STATE_HEX;
                }

                if(isdigit(c)){/// \ddd
                    ungetc(c,stdin); ///we need to reload the value for checking the real value
                    current = STATE_OCTAL;
                }

                if(c == 't'){ ///tab Ascii code 9
                    if(!add_to_buffer(9, token->attribute->buf)){  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }

                }

                if(c == '"'){ ///double quote  Ascii code 34
                    if(!add_to_buffer(34, token->attribute->buf)){  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }

                if(c == 92){ ///backslash ascii code 92
                    if(!add_to_buffer(92, token->attribute->buf)){  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }

                if(c == '$'){ ///dollar
                    if(!add_to_buffer('$', token->attribute->buf)){  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }

                if(c == 'n'){ ///line feed
                    if(!add_to_buffer(10, token->attribute->buf)){  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }


                break;
            case(STATE_OCTAL):


                octal_index = 0;
                char octal[4];
                while(true){
                    c = getc(stdin);
                    if(isdigit(c)||(c <= 7)){ ///number fulfilling the octal rules
                        octal[octal_index]=c;
                        octal_index++;
                        if(octal_index == 2)break;///complete number
                    }
                    else{

                        return ERR_LEX;
                    }


                }
                int octal_num= atoi(octal); ///converting string (octal number) to integer
                int decimal =  convertOctalToDecimal(octal_num);///converting octal to decimal (ascii)

                if (!add_to_buffer(decimal, token->attribute->buf)) {///add to buffer
                    return ERR_INTERNAL;
                }

                break;

            case(STATE_HEX):

                 hex_index =0;
                char hex[3];
                while(true){
                    c = getc(stdin);
                    if(isdigit(c)||(c <= 15)){ ///number fulfilling the octal rules
                        hex[hex_index]=c;
                        hex_index++;
                        if(octal_index == 1)break; ///complete number
                    }
                    else{

                        return ERR_LEX;
                    }


                }
                int hexa = atoi(hex); ///converting string (octal number) to integer



                break;

            case(STATE_NUM):
                    if(isdigit(c)){ ///next number

                        if (!add_to_buffer(c, token->attribute->buf)) {///add to buffer
                            return ERR_INTERNAL;
                        }
                        current = STATE_NUM; ///continue loading numbers
                    }
                    else if(c == '.'){ ///decimal number

                        current = STATE_FLOAT;
                        if(!add_to_buffer(c, token->attribute->buf)){///add dot to buffer
                            return ERR_INTERNAL;
                        }

                    }
                    else if(tolower(c) == 'e'){ ///exponent start
                        current = STATE_NUM_E;
                        if(!add_to_buffer(c, token->attribute->buf)){ ///add exponent to buffer
                            return ERR_INTERNAL;
                        }

                    }
                    else{
                        ungetc(c, stdin); ///number ends
                        token_int(token->attribute->buf, token); /// whole number (int)
                        break;
                    }

                break;
            case(STATE_NUM_E):
                if(isdigit(c))///exponent numbers
                {
                    if (!add_to_buffer(c, token->attribute->buf)) {///add to buf
                        return ERR_INTERNAL;
                    }
                    current = STATE_NUM_E; ///next exponent number
                }
                else if((c == '+')||(c == '-')){ ///sign
                    if (!add_to_buffer(c, token->attribute->buf)) {///add sign to buffer
                        return ERR_INTERNAL;
                    }

                    current = STATE_EXP_SIGN;}///this state is need to check whether there is only one exponent sign
                else{
                    ungetc(c, stdin); ///end of exponent
                    token_int(token->attribute->buf, token);
                    break;

                }
                break;

            case(STATE_FLOAT):
                if(isdigit(c)){ ///numbers behind decimal dot
                    if (!add_to_buffer(c, token->attribute->buf)) {
                        return ERR_INTERNAL;
                    }
                    current = STATE_FLOAT;
                }
                else if(tolower(c)=='e'){current = STATE_FLOAT_E;} ///floats exponent
                else{
                    ungetc(c, stdin);
                    token_float(token->attribute->buf, token); ///end of decimal number
                    break;
                }
                break;


            case(STATE_FLOAT_E):
                if(isdigit(c))///loading float exponent numbers
                {
                    if (!add_to_buffer(c, token->attribute->buf)) {
                        return ERR_INTERNAL;
                    }
                    current = STATE_FLOAT_E; ///continue loading
                }
                else if((c == '+')||(c == '-')){ ///sign

                    if (!add_to_buffer(c, token->attribute->buf)) {///add sign to buffer
                        return ERR_INTERNAL;
                    }
                    current = STATE_EXP_SIGN_F;}///load numbers
                else{
                    ungetc(c, stdin);
                    token_float(token->attribute->buf, token); ///end of float exponent
                    break;

                }

                break;
            case(STATE_EXP_SIGN_F):
                if(isdigit(c)) ///loading exponent numbers
                {
                    if (!add_to_buffer(c, token->attribute->buf)) {
                        return ERR_INTERNAL;
                    }
                    current = STATE_EXP_SIGN; ///continue loading
                }
                else{
                    ungetc(c, stdin);
                    token_float(token->attribute->buf, token);///end of float exponent
                    break;
                }
                break;

            case(STATE_EXP_SIGN):
                if(isdigit(c))///loading exponent numbers
                {
                    if (!add_to_buffer(c, token->attribute->buf)) {
                        return ERR_INTERNAL;
                    }
                    current = STATE_EXP_SIGN;///continue loading
                }
                else{
                    ungetc(c, stdin);
                    token_int(token->attribute->buf, token);///end of exponent
                    break;
                }
                break;
            case(STATE_FUN_ID_KEYWORD):

                ///same rules as for variable
                /// [( letter  or  '_' ) and   first ]   or [ (number or letter or _) but not first]
                if ((((isalpha(c)) || c == '_') & (first == true)) || ((isalnum(c) || c == '_') & (first = false))) ///fulfilled conditions for identifier
                {
                    int result = add_to_buffer(c, token->attribute->buf); /// add char to buffer
                    if (result != 0) ///return only in case of an error
                    {
                        return result;
                    }
                    ///keep adding character to variable
                    first = false;
                    current = STATE_FUN_ID_KEYWORD;
                }
                else {

                    ungetc(c, stdin);
                    identify(token->attribute->buf, token );
                }
                break;








        }


    }

}

