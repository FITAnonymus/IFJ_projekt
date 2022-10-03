/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of functions providing lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */



#include <ctype.h> // includes functions for determining type of loaded data
#include <stdio.h>
#include <buffer.h> // used for storing the identifier of token
#include <scanner.h> // includes prototypes and list of keywords, states and types of tokens and structure of token itself
#include <error.h>
#include <stdlib.h> // used for string processing

    int process_float()
    {
        /**
         * Desetinný literál (rozsah C-double) také vyjadřuje nezáporná čísla v desítkové soustavě, přičemž literál je tvořen celou a desetinnou částí, nebo celou částí a exponentem, nebo celou a desetinnou částí a exponentem. Celá i desetinná část je tvořena
    neprázdnou posloupností číslic. Exponent je celočíselný, začíná znakem ’e’ nebo
    ’E’, následuje nepovinné znaménko ’+’ (plus) nebo ’-’ (mínus) a poslední částí je
    neprázdná posloupnost číslic. Mezi jednotlivými částmi nesmí být jiný znak, celou a
    desetinnou část odděluje znak ’.’ (tečka)5
    .
         */
    }
    int process_int()
    {
        /**
           • Celočíselný literál (rozsah C-int) je tvořen neprázdnou posloupností číslic a vyjadřuje
           hodnotu celého nezáporného čísla v desítkové soustavě.

       */
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
         */
    }




    token get_next_token()
    {

          while(true){

              //load char from source file

              switch(){
               // instructions for each state
               //lecture notes:
               // reduce states with direct transfer to other states(without condition)
               // only deterministic states
               // check unreachable states



              }


          }


    }