/**
 * Projekt: IFJ 2022
 *
 * @Support of lexical analysis
 * @providing dynammic string buffer data type
 * @plus basic functions of it
 *
 * @authors
 */

#include <string.h>

int initialize_buf(buf *buffer);
int add_char_to_buf(char c, buf *buffer);
int cmp_string_buf(string string, buf *buffer);
int copy_buf(buf *buffer);
