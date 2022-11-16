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

#define STRING_INC 8
/**
int main(){

    return 0;
}
*/
int init_buffer(Buffer *buf){

    ///malloc first cell + check if malloc was successful
    ///float - because we need to count with the biggest possible data type on input
    buf->buf = (char *) malloc(STRING_INC);
    if (buf->buf == NULL)
    {
        return ERR_INTERNAL;
    }

    buf->lenght = 0; ///lenght of a buffer
    buf->buf[0] = '\0'; /// end of string added
    buf->size = STRING_INC;
    return 0;
}


int add_to_buffer(char c, Buffer *buf){
   /// printf("add to buffer\n");//todo
    if(buf->lenght +1 >= buf->size) {

        unsigned int size_to_alloc = (buf->lenght + STRING_INC);///one more cell
        ///printf("new size\n");//todo


        buf->buf = (char *) realloc((void * )buf->buf, size_to_alloc); /// try to alloc the cell


       /// printf("realloc ok\n");//todo

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

void free_buffer(Buffer *buf){

    free(buf); ///free whole buffer structure

}




