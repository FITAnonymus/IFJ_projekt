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
#include <math.h>


int token_int(Buffer *buf, token_struct *token){

    char *alloc_check;
    int integer = strtol(buf->buf, &alloc_check,10); ///convert char to number

    if (*alloc_check)  ///allocation fail
    {
        return ERR_INTERNAL;
    }

    token->type = TYPE_INTEGER;  ///select token type
    token->attribute.integer= integer;  ///assign value

    return TOKEN_OK;

}

int convertOctalToDecimal(int octalNumber){
    double decimalNumber = 0;
    int  i = 0;

    while(octalNumber != 0) {
        decimalNumber += (octalNumber%10) * pow(8,i);
        ++i;
        octalNumber/=10;
    }

    i = 1;
    int result = decimalNumber;
    return result;
}



void identify(Buffer *buffer, token_struct *token){

    if(cmp_string_buffer("else", buffer)==0){ ///cmp returns null in equality, that is the reason for the negation at the beginning
        token->type = KEYWORD_ELSE;
        //token->attribute = NULL; ///no atributes for keyword
    }
    else if(!cmp_string_buffer("float", buffer)){
        token->type = KEYWORD_FLOAT;
       // token->attribute = NULL;
    }
    else if(!cmp_string_buffer("function", buffer)){
        token->type = KEYWORD_FUNCTION;
       // token->attribute = NULL;
    }
    else if(!cmp_string_buffer("if", buffer)){
        token->type = KEYWORD_IF;
       // token->attribute = NULL;
    }
    else if(!cmp_string_buffer("int", buffer)){
        token->type = KEYWORD_INT;
        //token->attribute = NULL;
    }
    else if(!cmp_string_buffer("null", buffer)){
        token->type = KEYWORD_NULL;
        //token->attribute = NULL;
    }
    else if(!cmp_string_buffer("return", buffer)){
        token->type = KEYWORD_RETURN;
        //token->attribute = NULL;
    }
    else if(!cmp_string_buffer("string", buffer)){
        token->type = KEYWORD_STRING;
       // token->attribute = NULL;
    }
    else if(!cmp_string_buffer("void", buffer)){
        token->type = KEYWORD_VOID;
        //token->attribute = NULL;
    }
    else if(!cmp_string_buffer("while", buffer)){
        token->type = KEYWORD_WHILE;
        //token->attribute = NULL;
    }
    else {
        token->type = TYPE_FUNCTION_ID;
       // token->attribute.buf->buf = buffer->buf;
    }

}

int token_float(Buffer *buf, token_struct *token){
    printf("token float\n");
    char *alloc_check;
    float n_float = strtod(buf->buf, &alloc_check); ///convert char to number

    if (*alloc_check)   ///allocation fail
    {
        return ERR_INTERNAL;
    }

    token->type = TYPE_FLOAT; ///select token type
    token->attribute.decimal = n_float;///assign value

    return TOKEN_OK;

}
int main(){


    Buffer *buffer;
    Buffer buf;
    buffer =&buf;

    init_buffer(buffer);
    printf("init_buffer_ok\n");
    token_struct *p_token;
    struct token_struct token;
    token.type= TYPE_EMPTY;
    p_token = &token;
    p_token->attribute.buf = buffer;
   // token.attribute.buf;

    int result = get_next_token(p_token);

    printf("%d\n", token.type);
    /**
    if(token.attribute != NULL){
        if(token.attribute->integer != NULL){  printf("%d\n", *token.attribute->integer);}
        if(token.attribute->integer != NULL){  printf("%d\n", *token.attribute->integer);}
    }
     */
    return result;
}

int get_next_token(struct token_struct *token) {
    ///support variables
    char c;
    int current = STATE_START;
    int octal_index;
    int hex_index;
    int prolog_index = 0;
   bool first = true;

    ///string constants for lexical analysis
   // char prolog_start[6] = "<?php";
    //char char_int[4]="int";
   // char char_str[7]="string";
    //char char_float[6] ="float";

    ///main loop for loading the characters
    while (1) {

        c = getc(stdin);

        switch (current) {
            case (STATE_START):
                if ((c == ' ') || (c == '\n')) { current = STATE_START; }  ///EOL+whitespaces

                if (c == '(') {
                    token->type = TYPE_PAR_LEFT;
                   // token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == ')') {
                    token->type = TYPE_PAR_RIGHT;
                   // token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '*') {
                    token->type = TYPE_MUL;
                    //token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '+') {
                    token->type = TYPE_PLUS;
                   // token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '-') {
                    token->type = TYPE_MINUS;
                    //token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '.') {
                    token->type = TYPE_CONCAT;
                    //token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == ':') {
                    token->type = TYPE_COLON;
                    //token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '{') {
                    token->type = TYPE_BRACE_LEFT;
                   // token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == '}') {
                    token->type = TYPE_BRACE_RIGHT;
                    //token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == ';') {
                    token->type = TYPE_SEMICOLON;
                    //token->attribute = NULL;
                    return TOKEN_OK;
                }

                if (c == ',') {
                    token->type = TYPE_COMMA;
                    //token->attribute = NULL;
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
                   // token->attribute = NULL;
                    return TOKEN_OK;
                } else return ERR_LEX; ///!= is not possible
                break;

            case (STATE_LOWER):
                if (c == '=') {
                    token->type = TYPE_LOWER_EQ;
                    //token->attribute = NULL;
                    return TOKEN_OK;
                }
                else if(c == '?') {
                    current = STATE_PROLOG;
                }
                else {
                    token->type = TYPE_LOWER;
                    //token->attribute = NULL;
                    ungetc(c, stdin);
                    return TOKEN_OK;
                }
                break;
            case(STATE_PROLOG):
                if(add_to_buffer(c ,token->attribute.buf)!= 0){return ERR_INTERNAL;}
                prolog_index++;
                if(prolog_index == 3){

                    if(cmp_string_buffer("php",token->attribute.buf) ==0)
                    {token->type = TYPE_PROLOG_START;
                    return TOKEN_OK;}
                    else{return ERR_LEX;}
                }
                current = STATE_PROLOG;
                break;
            case (STATE_GREATER):
                if (c == '=') {
                    token->type = TYPE_GREATER_EQ;
                    //token->attribute = NULL;
                    return TOKEN_OK;
                } else {
                    token->type = TYPE_GREATER;
                    //token->attribute = NULL;
                    ungetc(c, stdin);
                    return TOKEN_OK;
                }

                break;

            case (STATE_EQUAL):
                if (c == '=') { current = STATE_DOUBLE_EQUAL; }
                else {
                    {
                        token->type = TYPE_ASSIGN;
                        //token->attribute = NULL;
                        ungetc(c, stdin);
                        return TOKEN_OK;
                    }
                }
                break;

            case (STATE_DOUBLE_EQUAL):
                if (c == '=') {
                    {
                        token->type = TYPE_COMPARE;
                        //token->attribute = NULL;
                        return TOKEN_OK;
                    }
                } else { return ERR_LEX; } /// double equal is not possible

                break;

            case (STATE_BEGIN_VAR):

                if(isalnum(c) || (c =='_'))
                {
                  ; /// add char to buffer
                    if (add_to_buffer(c, token->attribute.buf) != 0) ///return only in case of an error
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
                } else if (c == '/') {      ///single line comment

                    current = STATE_COMMENT;

                } else {              /// division

                    token->type = TYPE_DIV;
                   // token->attribute = NULL;
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
                    //token->attribute = NULL;
                }
                if ((add_to_buffer(c, token->attribute.buf)) != 0) {///add char to buffer
                    return ERR_INTERNAL;
                }else{
                        if (cmp_string_buffer("string", token->attribute.buf) == 0) {
                            token->type = TYPE_STRING_Q;
                           // token->attribute = NULL;  ///?char
                            return TOKEN_OK;
                        }else if ((cmp_string_buffer("int", token->attribute.buf))== 0) {
                            token->type = TYPE_INTEGER_Q;
                           // token->attribute = NULL;///?int
                            return TOKEN_OK;
                        } else if (cmp_string_buffer("float", token->attribute.buf)== 0) {
                            token->type = TYPE_FLOAT_Q;
                           // token->attribute = NULL; ///?float
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

                if (add_to_buffer(c, token->attribute.buf) != 0) {  ///add char to buffer
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

                if (isdigit(c)) {/// \ddd
                    ungetc(c, stdin); ///we need to reload the value for checking the real value
                    current = STATE_OCTAL;
                }

                if (c == 't') { ///tab Ascii code 9
                    if (!add_to_buffer(9, token->attribute.buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }

                }

                if (c == '"') { ///double quote  Ascii code 34
                    if (!add_to_buffer(34, token->attribute.buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }

                if (c == 92) { ///backslash ascii code 92
                    if (!add_to_buffer(92, token->attribute.buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }

                if (c == '$') { ///dollar
                    if (!add_to_buffer('$', token->attribute.buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }

                if (c == 'n') { ///line feed
                    if (!add_to_buffer(10, token->attribute.buf)) {  ///add char to buffer
                        return ERR_INTERNAL;///memory allocation fail
                    }
                }


                break;

            case (STATE_OCTAL):


                octal_index = 0;
                char octal[4];
                while (true) {
                    c = getc(stdin);
                    /// ascii   0-7
                    if (isdigit(c) && (c <= 55) && (c >= 48)) { ///number fulfilling the octal rules
                        octal[octal_index] = c;
                        octal_index++;
                        if (octal_index == 2)break;///complete number
                    } else {

                        return ERR_LEX;
                    }


                }
                int octal_num = atoi(octal); ///converting string (octal number) to integer
                double decimal_octal = convertOctalToDecimal(octal_num);///converting octal to decimal (ascii)

                int result_octal = decimal_octal;
                if (!add_to_buffer(result_octal, token->attribute.buf)) {///add to buffer
                    return ERR_INTERNAL;
                }

                break;

            case (STATE_HEX):

                hex_index = -1; ///index start so we can check hex array overflow before assigning another char to it
                char hex[3];
                while (true) {
                    c = getc (stdin);///loading what is after escape sequence
                    hex_index++;
                    ///either number or  capital letter(A-F) or small letters (a-f)
                    if (isdigit (c) || ((c >= 65) && (c <= 70))||((c >= 97) && (c <= 102))) { ///conditions of hexadecimal number fulfilled

                        if (hex_index > 1) { ///array overflow check
                            ungetc (c, stdin);
                            return ERR_LEX; ///hexadecimal number too long
                        }
                        hex[hex_index] = c;

                    } else {

                        if(hex_index <= 1){ return ERR_LEX; }///unfinished variable
                        break; ///variable hexa finished => continue to the conversion
                    }

                }
                int i,val;
                double decimal;
                for(i=0; hex[i]!='\0'; i++)
                {

                     //Find the decimal representation of hex[i]
                    if(hex[i]>='0' && hex[i]<='9')
                    {
                        val = hex[i] - 48;
                    }
                    else if(hex[i]>='a' && hex[i]<='f')
                    {
                        val = hex[i] - 97 + 10;
                    }
                    else if(hex[i]>='A' && hex[i]<='F')
                    {
                        val = hex[i] - 65 + 10;
                    }

                     decimal += val * pow(16, 2);

                }
                int result = decimal;
                if (!add_to_buffer(result, token->attribute.buf)) {///add to buffer
                    return ERR_INTERNAL;
                }

                break;

            case(STATE_NUM):

                    if(isdigit(c)){ ///next number

                        if (add_to_buffer(c, token->attribute.buf) != 0) {///add to buffer
                            return ERR_INTERNAL;
                        }
                        current = STATE_NUM; ///continue loading numbers
                    }
                    else if(c == '.'){ ///decimal number

                        current = STATE_FLOAT;
                        if(add_to_buffer(c, token->attribute.buf)!=0){///add dot to buffer
                            return ERR_INTERNAL;
                        }

                    }
                    else if(tolower(c) == 'e'){ ///exponent start
                        current = STATE_NUM_E;
                        if(add_to_buffer(c, token->attribute.buf) != 0){ ///add exponent to buffer
                            return ERR_INTERNAL;
                        }

                    }
                    else{
                        ungetc(c, stdin); ///number ends

                        token->type = TYPE_INTEGER;
                        token_int(token->attribute.buf, token); /// whole number (int)
                        printf("%d", token->attribute.integer);///todo ok
                        return TOKEN_OK;
                    }

                break;
            case(STATE_NUM_E):

                if(isdigit(c))///exponent numbers
                {
                    if (add_to_buffer(c, token->attribute.buf) != 0) {///add to buf
                        return ERR_INTERNAL;
                    }
                    current = STATE_NUM_E; ///next exponent number
                }
                else if((c == '+')||(c == '-')){ ///sign
                    if (add_to_buffer(c, token->attribute.buf) != 0) {///add sign to buffer
                        return ERR_INTERNAL;
                    }

                    current = STATE_EXP_SIGN;}///this state is need to check whether there is only one exponent sign
                else{
                    ungetc(c, stdin); ///end of exponent
                    token_int(token->attribute.buf, token);
                    token->type = TYPE_INTEGER;
                    printf("%d\n", token->attribute.integer);///todo problem?

                    return TOKEN_OK;
                }
                break;

            case(STATE_FLOAT):

                printf("state_float\n");///todo
                if(isdigit(c)){ ///numbers behind decimal dot

                    if (add_to_buffer(c, token->attribute.buf) != 0){
                        return ERR_INTERNAL;
                    }
                    current = STATE_FLOAT;
                    printf("state_float again\n");///todo
                }
                else if(tolower(c)=='e'){current = STATE_FLOAT_E;} ///floats exponent
                else{
                    printf("konec tokenu\n");///todo
                    ungetc(c, stdin);
                    token->type = TYPE_FLOAT;
                    token_float(token->attribute.buf, token); ///end of decimal number
                    return TOKEN_OK;
                }
                break;


            case(STATE_FLOAT_E):
                printf("state exp float\n");///todo
                if(isdigit(c))///loading float exponent numbers
                {
                    if (add_to_buffer(c, token->attribute.buf) != 0) {
                        return ERR_INTERNAL;
                    }
                    current = STATE_FLOAT_E; ///continue loading
                }
                else if((c == '+')||(c == '-')){ ///sign

                    if (add_to_buffer(c, token->attribute.buf) != 0) {///add sign to buffer
                        return ERR_INTERNAL;
                    }
                    current = STATE_EXP_SIGN_F;
                }///load numbers
                else{
                    if(c == 32){return ERR_LEX;}///empty exponent
                    ungetc(c, stdin);
                    token->type = TYPE_FLOAT;
                    token_float(token->attribute.buf, token); ///end of float exponent
                    return TOKEN_OK;

                }

                break;
            case(STATE_EXP_SIGN_F):

                if(isdigit(c)) ///loading exponent numbers
                {
                    if (add_to_buffer(c, token->attribute.buf) != 0) {
                        return ERR_INTERNAL;
                    }
                    current = STATE_EXP_SIGN_F; ///continue loading
                }
                else{
                    if(c == 32){return ERR_LEX;}///empty exponent after sign
                    ungetc(c, stdin);
                    token->type = TYPE_FLOAT;
                    token_float(token->attribute.buf, token); ///end of float exponent

                    printf("%f\n", token->attribute.decimal);///todo problem?
                    return TOKEN_OK;
                }
                break;

            case(STATE_EXP_SIGN):
                if(isdigit(c))///loading exponent numbers
                {
                    if (add_to_buffer(c, token->attribute.buf) != 0) {
                        return ERR_INTERNAL;
                    }
                    current = STATE_EXP_SIGN;///continue loading
                }
                else{
                    if(c == 32){return ERR_LEX;}///empty exponent after sign
                    ungetc(c, stdin);
                    token->type = TYPE_INTEGER;
                    token_int(token->attribute.buf, token);///end of exponent
                    return TOKEN_OK;

                }
                break;
            case(STATE_FUN_ID_KEYWORD):
                ///same rules as for variable
                /// [( letter  or  '_' ) and   first ]   or [ (number or letter or _) but not first]

                if ((((isalpha(c)) || c == '_') & (first == true)) || ((isalnum(c) || c == '_') & (first = false))) ///fulfilled conditions for identifier
                {
                     /// add char to buffer
                    if (add_to_buffer(c, token->attribute.buf) != 0) ///return only in case of an error
                    {
                        return ERR_INTERNAL;
                    }
                    ///keep adding character to variable
                    first = true; // TODO upravit at vyhovuje podminkam pro promennou !!! asi s tim poradi zpracovani cisel ale jeste otestovat!!
                    current = STATE_FUN_ID_KEYWORD;
                }
                else {
                    ungetc(c, stdin);
                    identify(token->attribute.buf, token );
                    return TOKEN_OK;
                }
                break;








        }


    }

}

