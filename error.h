/**
* Projekt: IFJ 2022
*
*
* @authors
*/

// ERROS BASED ON MODULES OF TRANSLATOR AND ELEARNING INSTRUCTIONS PAGE 2
#define TOKEN_OK 0
#define SYNTAX_OK 0
#define SEMANTIC_OK 0
#define GENERATING_OK 0
#define ERR_LEX 1
//#define ERR_SYN
//#define ERR_SEM
//#define ERR_
/**
* • 1 - chyba v programu v rámci lexikální analýzy (chybná struktura aktuálního lexému).
• 2 - chyba v programu v rámci syntaktické analýzy (chybná syntaxe programu, chybějící hlavička, atp.).
• 3 - sémantická chyba v programu – nedefinovaná funkce, pokus o redefinice funkce.
• 4 - sémantická/běhová chyba v programu – špatný počet/typ parametrů u volání funkce či typ návratové hodnoty z funkce.
• 5 - sémantická chyba v programu – použití nedefinované proměnné.
• 6 - sémantická/běhová chyba v programu – chybějící/přebývající výraz v příkazu návratu z funkce.
• 7 - sémantická/běhová chyba typové kompatibility v aritmetických, řetězcových a
relačních výrazech.
• 8 - ostatní sémantické chyby.
• 99 - interní chyba překladače tj. neovlivněná vstupním programem (např. chyba alokace paměti atd.).
*/