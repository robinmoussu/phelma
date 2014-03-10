#ifndef LISTE_H
#define LISTE_H

#include "carte.h"

typedef CARTE ELEMENT;
typedef struct cellule {
    ELEMENT val;
    struct cellule *suiv;
} Cellule, *Liste;

Liste creer_liste (void);
int est_vide (Liste l);
void visualiser_liste (Liste l);
Liste ajout_tete (CARTE c, Liste l);
Liste ajout_queue (CARTE c, Liste l);
Liste supprimen (int n, Liste l);


#endif
