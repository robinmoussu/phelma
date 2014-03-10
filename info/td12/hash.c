#include "hash.h"

#define NULL 0

unsigned long hash(const char *c, unsigned int dim)
{
    unsigned long const a = 31;
    unsigned long h;


    for (h=0 ; c != NULL; c++) {
        h = (unsigned long)(h*a + c);
        h %= dim;
    }

    return h;
}
