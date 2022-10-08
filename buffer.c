/**
    * Project: Implementace překladače imperativního jazyka IFJ22.
    *
    * @brief Implementation of dynamic string format used in lexical analysis.
    *
    * @author Daniel Žárský <xzarsk04@stud.fit.vutbr.cz>
    */

#include "buffer.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>


int init_buffer(Buffer *buf){

    ///malloc first cell + check if malloc was successful
    buf->buf = (char *) malloc(sizeof(char))
    if (buf->buf == NULL)
    {
        return ERR_INTERNAL;
    }

    buf->lenght = 0; ///lenght of a buffer
    buf->buf[0] = '\0'; /// end of string added
    buf->size = sizeof(char);
    return 0;
}


int add_to_buffer(char c, Buffer *buf){

    unsigned long size_to_alloc = (buf->size + sizeof(char));///one more cell

    buf->buf = (char *)realloc(buf->buf, size_to_alloc); /// try to alloc the cell

    if(buf->buf == NULL){return ERR_INTERNAL;}/// check if allocation was successful

    buf->lenght++;
    buf->size += sizeof(char);///new size of buffer

    buf->buf[buf->lenght]='\0'; ///new end of string
    buf->buf[buf->lenght-1]= c; ///new character added to string just before end

}

int cmp_string_buffer(char string[], Buffer *buf){

    return strcmp(string, buf->buf);
}


int copy_buffer(Buffer *src, Buffer *dst){

    if(src->size > dst->size)/// allocating only when its needed
    {
        dst->buf =(char *)realloc(dst->buf, src->size); /// try realloc
        if(dst->buf == NULL){return ERR_INTERNAL;}///check if success

        dst->lenght =src->lenght; /// new attributes for destination buffer
        dst->size = src->size;
    }
    strcpy(dst->buf, src->buf); ///copying
    return 0;
}

int free_buffer(Buffer *buf){

    free(buf); ///free whole buffer structure
}


//testing purposes only
int main(){

    Buffer test;
    Buffer *buf;
    buf = &test;
    int result = init_buffer(buf);
    return result;

}





