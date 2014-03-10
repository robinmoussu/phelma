#ifndef HASH_H
#define HASH_H

#include "listHash_tablee.h"

typedef struct {
    Liste* table;
    int size;
} Hash_table;

/* @brief Fonction de hashage
 * @c : chaine dont ont cherche le hash
 * @dim : dimention de table de hashage
 * @return : hash
 */
unsigned long hash(const char *c, unsigned int dim);

/* @brief Initialise la table de hashage
 * @size Taille de la table
 * @return Table initialisé
 */
Hash_table ht_init(int size);

#endif
