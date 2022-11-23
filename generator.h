/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Code generator library.
    *
    *
    */
#include "token_buffer.h"
#include <stdio.h>
/**
 * @brief Function will iterate through the token buffer, based on tokens type prints corresponding IFJ22Code code
 * @param tok_buf
 * @return 0, in case of no problems, otherwise error value
 */
int process_tok_buf(Token_buffer * tok_buf);

void print_frame(bool GF, bool LF, bool TF);
void print_start(); ///Kód v jazyce IFJcode22 začíná úvodním řádkem s tečkou následovanou jménem jazyka: .IFJcode22

/**
 * Function simplifies complicated arithmetic expressions and replaces it with a single temporary variable.
 * The most important task of this function is to correctly check parenthesis, to correctly check priority of the operations
 * @param tok_buf Input program
 * @param index index of first token of the expression
 */
void handle_expression(Token_buffer * tok_buf, int index);

/**
 * In case of loaded IF token, function generates unique else_label, based on index
 * @param tok_buf Input program
 * @param index index of token where was the function called - helps generate original label names
 * @return 0
 */
int generate_label(Token_buffer * tok_buf, int index);

/**
 * In case of loaded IF token, function generates compare and jump construction using function handle operation
 * @param tok_buf Input program
 * @param index index of token where was the function called
 * @return
 */
int condition_gen(Token_buffer * tok_buf), int index);

/**
 * Function handles arithmetic operation
 *
 * @param tok_buf Input program
 * @param index index of first operand
 * @return
 */
void handle_operation(Token_buffer * tok_buf, int index);

///Vestavěné funkce ze standardního vstupu načtou jeden řádek ukončený odřádkováním
///nebo koncem souboru (EOF). Funkce reads tento řetězec vrátí bez symbolu konce
///řádku (načítaný řetězec nepodporuje escape sekvence). V případě readi a readf
///jsou okolní bílé znaky ignorovány. Jakýkoli jiný nevhodný znak před či za samotným
///číslem je známkou špatného formátu a vede na návratovou hodnotu null. Funkce
///readi načítá a vrací celé číslo, readf desetinné číslo. V případě chybějící hodnoty
///na vstupu (např. načtení EOF) nebo jejího špatného formátu je vrácena hodnota null.

int bi_reads(); ///bi = build in 
int bi_readi();
int bi_readf();

int bi_write(); /// Příkaz pro výpis hodnot: function write ( term1 , term2 , …, term𝑛 ) : void
       /// Vestavěný příkaz má libovolný počet parametrů tvořených termy oddělenými čárkou.
int bi_strlen(); ///– Vrátí délku (počet znaků) řetězce $𝑠. Např. strlen("x\nz") vrací 3.

int bi_substring(); /// viz konec stranky 10 zadani

int bi_ord();///Vrátí ordinální hodnotu (ASCII) prvního znaku v řetězci 𝑐. Je-li řetězec prázdný, vrací funkce 0.

int bi_chr(); ///Vrátí jednoznakový řetězec se znakem, jehož ASCII kód je zadán parametrem 𝑖.
/// Hodnotu 𝑖 mimo interval[0; 255]řeší odpovídající instrukce IFJcode22.


