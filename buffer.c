/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of dynamic string format used in lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include <string.h>

int initialize_buf(buf *buffer);
int add_char_to_buf(char c, buf *buffer);
int cmp_string_buf(string string, buf *buffer);
int copy_buf(buf *buffer);
