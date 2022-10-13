/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of functions providing lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */



#include <ctype.h> // includes functions for determining type of loaded data
#include <stdio.h>
#include "scanner.h" // includes prototypes and list of keywords, states and types of tokens and structure of token itself
#include <stdlib.h> // used for string processing
//#include "buffer.h"
#include <stdbool.h>


/**
int process_float()
    {

         * Desetinný literál (rozsah C-double) také vyjadřuje nezáporná čísla v desítkové soustavě, přičemž literál je tvořen celou a desetinnou částí, nebo celou částí a exponentem, nebo celou a desetinnou částí a exponentem. Celá i desetinná část je tvořena
    neprázdnou posloupností číslic. Exponent je celočíselný, začíná znakem ’e’ nebo
    ’E’, následuje nepovinné znaménko ’+’ (plus) nebo ’-’ (mínus) a poslední částí je
    neprázdná posloupnost číslic. Mezi jednotlivými částmi nesmí být jiný znak, celou a
    desetinnou část odděluje znak ’.’ (tečka)5
    .

    }
    int process_int()
    {

           • Celočíselný literál (rozsah C-int) je tvořen neprázdnou posloupností číslic a vyjadřuje
           hodnotu celého nezáporného čísla v desítkové soustavě.


    }

    int process_string()
    {
        /**
       • Řetězcový literál je oboustranně ohraničen dvojitými uvozovkami (", ASCII hodnota
    34). Tvoří jej libovolný počet znaků zapsaných případně i na více řádcích. Možný
    je i prázdný řetězec (""). Znaky s ASCII hodnotou větší než 31 (mimo ") lze zapisovat přímo. Některé další znaky lze zapisovat pomocí escape sekvence: ’\"’, ’\n’,
    ’\t’, ’\\’. Jejich význam se shoduje s odpovídajícími znakovými konstantami jazyka PHP6
    . Na rozdíl od jazyka C nelze escape sekvencí vytvořit chybu – pakliže
    znaky za zpětným lomítkem neodpovídají žádnému z uvedených vzorů, jsou (včetně
    lomítka) bez jakýchkoli náhrad součástí řetězce. Expanzi (interpolaci) proměnných
    v řetězcích neuvažujte, nicméně znak dolar lze sázet jen pomocí escape sekvence
    ’\$’. Znak v řetězci může být zadán také pomocí escape sekvence ’\xdd’, kde dd je
    dvoumístné hexadecimální číslo od 01 do FF (písmena A-F mohou být malá i velká).
    Znak v řetězci může být zadán také pomocí obecné escape sekvence ’\ddd’, kde ddd
    je právě třímístné oktalové číslo od 001 do 377.
    Délka řetězce není omezena (resp. jen dostupnou velikostí haldy). Například řetězcový literál

    }
*/


    //main just for testing purposes in real implementation will be next token called from syntax analysis
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



    struct token_struct* get_next_token(struct token_struct *token) {
        char c;
        int current = STATE_START;
        char prolog_start[6] = "<?php";
        ///constants for lexical analysis

         char char_int[4]="int";
         char char_str[7]="string";
         char char_float[6] ="float";

        while (1) {

            //load char from source file
            c = getc(stdin); //Překladač bude načítat řídicí program v jazyce IFJ22 ze standardního vstupu.
            bool first = true;
            // reduce states with direct transfer to other states(without condition)
            // only deterministic states
            // check unreachable states
            switch (current) {
                case (STATE_START):
                    if ((c == ' ') || (c == '\n')) { current = STATE_START; }

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

                    if (c == '!') { current = STATE_EXCLAMATION; }

                    if (c == 92) {
                        token->type = TYPE_DIV;
                        token->attribute = NULL;
                        return TOKEN_OK;
                    }// \ = 92 in ascii

                    if (c == '>') { current = STATE_GREATER; }

                    if (c == '<') { current = STATE_LOWER; }

                    if (c == '=') { current = STATE_EQUAL; }

                    if (c == '$') { current = STATE_BEGIN_VAR; }

                    if (c == '/') { current = STATE_BACKSLASH; }

                    if (c == '?') { current = STATE_QUESTION_MARK; }

                    break;
                case (STATE_EXCLAMATION):
                    if (c == '=') { current = STATE_EXCLAMATION_EQ; }
                    break;

                case (STATE_EXCLAMATION_EQ):
                    if (c == '=') {
                        token->type = TYPE_COMPARE_NEG;
                        token->attribute = NULL;
                        return TOKEN_OK;
                    } else return token; ///!= is not possible
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

                case (STATE_BEGIN_VAR):
                    token->type = TYPE_VARIABLE_ID;

                    /// [( letter  or  '_' ) and   first ]   or [ (number or letter or _) but not first]
                    if ((((isalpha(c)) || c == '_') & (first == true)) ||
                        ((isalnum(c) || c == '_') & (first = false))) ///fulfilled conditions for variable
                    {
                        int result = add_to_buffer(c, token->attribute->buf); /// add to tokens buffer
                        if (result != 0) ///return only in case of an error
                        {
                            return result;
                        }
                        ///keep adding character to variable
                        first = false;
                        current = STATE_BEGIN_VAR;
                    } else {
                        if (first)///unfulfilled conditions for first letter of variable
                        {
                            return ERR_LEX;
                        } else {
                            ungetc(c, stdin);
                            return TOKEN_OK;
                        }///end of variable name
                    }

                    break;
                case (STATE_BACKSLASH):
                    if (c == '*') { current = STATE_BLOCK_COMMENT; }
                    else if (c == '/') {
                        current = STATE_COMMENT;
                    } else {//err todo error samotne lomitko
                        }
                        break;
                        case (STATE_COMMENT):
                            if (c == '\n') {
                                current = STATE_START;
                            } else if (c == EOF) {
                                //todo err eof v commentu
                            } else {
                                current = STATE_COMMENT;
                            }
                        break;

                case (STATE_BLOCK_COMMENT):
                            if (c == '*'){

                                current = STATE_END_BLOCK_COMMENT;

                            }
                            else if (c == EOF)
                            {
                                token->type = TYPE_ERROR; token->attribute->integer= ERR_LEX;
                            }
                            else{
                                current = STATE_BLOCK_COMMENT;
                            }
                        break;
                case (STATE_END_BLOCK_COMMENT):
                            if (c == '/') {
                                current = STATE_START;
                            } else {
                                current = STATE_BLOCK_COMMENT;
                            }
                        break;
                case (STATE_QUESTION_MARK):
                     if( c == '>'){token->type = TYPE_PROLOG_END; token->attribute = NULL;}
                     else{
                         if((!isalpha(c))||(c != '<')){
                             token->type = TYPE_ERROR; token->attribute->integer= ERR_LEX;
                             return token;
                         }
                         if (!(add_to_buffer(c, token->attribute->buf))){
                             token->type = TYPE_ERROR; token->attribute->integer= ERR_INTERNAL;
                             return token;
                         }
                         else{
                             if(!cmp_string_buffer(prolog_start,token->attribute->buf))///cmp returns zero in case of success that the reason for the negation
                             {
                                 token->type = TYPE_PROLOG_START; token->attribute = NULL;
                                 return token;
                             }
                             else if(!cmp_string_buffer(char_str,token->attribute->buf)){
                                 token->type = TYPE_STRING_Q; token->attribute = NULL;
                                 return token;
                             }
                             else if(!cmp_string_buffer(char_int,token->attribute->buf)){
                                 token->type = TYPE_INTEGER_Q; token->attribute = NULL;
                                 return token;
                             }
                             else if(!cmp_string_buffer(char_float,token->attribute->buf)){
                                 token->type = TYPE_FLOAT_Q; token->attribute = NULL;
                                 return token;
                             }
                             else{
                                 token->type = TYPE_ERROR; token->attribute->integer= ERR_LEX;
                                 return token;
                             }
                         }

                     }
                    break;


                        default:;

                    }


            }
        return token;
        }

