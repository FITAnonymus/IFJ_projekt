/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of dynamic string format used in lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "buffer.h"
#include "error.h"

#define BUFF_INC 8


int init_buffer(Buffer *buf){

    ///malloc first cell + check if malloc was successful
    ///float - because we need to count with the biggest possible data type on input
    buf->buf = (char *) malloc(BUFF_INC);

    if (buf->buf == NULL)
    {
        return ERR_INTERNAL;
    }

    buf->lenght = 0; ///lenght of a buffer
    buf->buf[0] = '\0'; /// end of string added

    buf->size = BUFF_INC;

    return 0;
}

int add_to_buffer(char c, Buffer *buf) {


    if (buf->lenght + 1 >= buf->size) {

            unsigned int size_to_alloc = (buf->lenght + BUFF_INC);///one more cell

            buf->buf = (char *) realloc((void *) buf->buf, size_to_alloc); /// try to alloc the cell

            if (buf->buf == NULL) { return ERR_INTERNAL; }/// check if allocation was successful



            buf->size = size_to_alloc;///new size of buffer


    }
        buf->lenght++;
        buf->buf[buf->lenght] = '\0'; ///new end of string
        buf->buf[buf->lenght - 1] = c; ///new character added to string just before end


    return 0;
}

int cmp_string_buffer(const char string[], Buffer *buf){

    return strcmp(string, buf->buf);
}

//int copy_buffer(Buffer *src, Buffer *dst){
//
//    if(src->size > dst->size)/// allocating only when its needed
//    {
//        dst->buf =(char *)realloc(dst->buf, src->size); /// try realloc
//        if(dst->buf == NULL){return ERR_INTERNAL;}///check if success
//
//        dst->lenght =src->lenght; /// new attributes for destination buffer
//        dst->size = src->size;
//    }
//    strcpy(dst->buf, src->buf); ///copying
//    return 0;
//}

void free_buffer(Buffer *buf){
    free(buf->buf);
    free(buf); ///free whole buffer structure
    buf = NULL;
}

void print_buffer(Buffer *buf){
    for(int i =0; buf->buf[i] != '\0'; i++){printf("%c", buf->buf[i]);}
    return;
}
//int clean_buffer(Buffer *buf){
//
//    free(buf->buf);
//    buf->buf = (char *) malloc(BUFF_INC);
//    if (buf->buf == NULL)
//    {
//        return ERR_INTERNAL;
//    }
//
//    buf->lenght = 0; ///lenght of a buffer
//    buf->buf[0] = '\0'; /// end of string added
//
//    buf->size = BUFF_INC;
//
//    return 0;
//}
