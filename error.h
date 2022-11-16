    /**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Definition of error codes and return values
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

///internal error codes
#define TOKEN_OK 0
#define SYNTAX_OK 0
#define SEMANTIC_OK 0
#define GENERATING_OK 0
    ///// ERROS BASED ON MODULES OF TRANSLATOR AND ELEARNING INSTRUCTIONS PAGE 2
    //todo translation
#define ERR_LEX 1 ///* • 1 - chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému).
#define ERR_SYNTAX 2 ///• 2 - chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu, chybějící hlavička, atp.).
#define ERR_SEMANTIC_DEF_FCE 3///• 3 - sémantická chyba v programu – nedefinovaná funkce, pokus o redefinice funkce.
#define ERR_SEMANTIC_ARG_FCE 4 /// • 4 - sémantická/běhová chyba v programu – špatný počet/typ parametrů u volání funkce či typ návratové hodnoty z funkce.
#define ERR_SEMANTIC_DEF_VAR 5 ///• 5 - sémantická chyba v programu – použití nedefinované proměnné.
#define ERR_SEMANTIC_RETURN 6 ///• 6 - sémantická/běhová chyba v programu – chybějící/přebývající výraz v příkazu návratu z funkce.
#define ERR_SEMANTIC_TYPE 7 /// • 7 - sémantická/běhová chyba typové kompatibility v aritmetických, řetězcových a relačních výrazech.
#define ERR_SEMANTIC_OTHER 8 ///• 8 - ostatní sémantické chyby.
#define ERR_INTERNAL 99 ///• 99 - interní chyba překladače tj. neovlivněná vstupním programem (např. chyba alokace paměti atd.).
