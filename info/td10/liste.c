#include <string.h>
#include <stdlib.h>
#include "liste.h"


Liste creer_liste (void)
{
    return NULL;
}
int est_vide (Liste l)
{
    return (l == NULL);
}
void visualiser_liste (Liste l)
{
    if (l != NULL) {
        affiche((ELEMENT*) l);
        visualiser_liste(l->suiv);
    }
}
Liste ajout_tete (ELEMENT e, Liste l)
{
    Liste p=calloc(1,sizeof(*p));
    if (p==NULL)
        return NULL;

    /* on recopie le contenue de l'element de tête de liste dans p */
    memcpy(&(p->val), &e, sizeof(ELEMENT));
    p->suiv = l;
    return p;
}
Liste ajout_queue (CARTE c, Liste l)
{

    Liste p=calloc(1,sizeof(*p));
    if (p==NULL)
        return NULL;
    memcpy(p, &c, sizeof(ELEMENT));
    p->suiv = NULL;
    l->suiv = p;
    return l;
}
Liste supprimen (int n, Liste l)
{
    if (n!=0)
        supprimen(n-1,l->suiv);
    else {
        if (l->suiv != NULL) {
            memcpy(l, l->suiv, sizeof(Cellule));
            free(l->suiv);
        } else {
            free(l);
            l = NULL;
        }
    }
    return l;
}
