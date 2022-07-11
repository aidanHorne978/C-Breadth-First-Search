#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "mylib.h"

/* allocates memory
   @param size_t s is the size of memory to be allocated
*/
void *emalloc(size_t s){
    void *d;
    
    d = malloc (s);
    if (NULL == d){
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return d;
}

/* reallocates memory
   @param p is the thing to be reallocated to the size of size_t s
*/
void *erealloc(void *p, size_t s){
    void *d;
    d = realloc(p, s);
    
    if (NULL == d){
        fprintf(stderr, "Memory allocation failed!\n");
        exit (EXIT_FAILURE);
    }
    return d;
}
