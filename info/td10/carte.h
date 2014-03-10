#ifndef _CARTE
#define _CARTE
enum { TREFLE, CARREAU, COEUR, PIQUE } COULEUR;

typedef struct {
    int rang;
    char visible;
    char couleur;
} CARTE;

void init_carte (CARTE *);
void affiche (CARTE *);
void affichevisible (CARTE *);

#endif
