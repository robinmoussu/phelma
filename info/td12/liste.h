#ifndef _LISTE
#define _LISTE

#include <stdio.h>
#include <string.h>

typedef char* ELEMENT;
struct cellule { 
   ELEMENT val;
   struct cellule * suiv;} ;

typedef struct cellule * Liste;


Liste creer_liste(void);
int est_vide(Liste L);
Liste rech(ELEMENT e, Liste L);
Liste ajout_tete(ELEMENT e, Liste L);

#endif
