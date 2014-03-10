#include <stdlib.h>
#include "hash.h"

#ifndef NULL
#define NULL 0
#endif

unsigned long hash(const char *c, unsigned int dim)
{
    const char *it;
    unsigned long const a = 31;
    unsigned long h=0;

    for (it=c ; *it != '\0'; it++) {
        h = (unsigned long)(h*a + *it);
        h %= dim;
    }

    return h;
}

Hash_table ht_init(int size)
{
    Hash_table h;

    h.size = size;
    h.table = (Liste*) calloc(size, sizeof(h.table));
    return h;
}

void ht_add(Hash_table h, ELEMENT e)
{
    ajout_tete(e,h.table[hash(e,h.size)]);
}
