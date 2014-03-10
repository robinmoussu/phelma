#ifndef _PILE
#define _PILE
#include <stdio.h>
#include "carte.h"
#include "liste.h"

File creer_file(void); // Créer une file vide
int file_vide(File ); // Teste si la file est vide
void visualiser_fil(File f);
File enfiler(CARTE , File ); // Ajoute une carte à la file par la queue
CARTE defiler(File* f); Renvoie la carte en tete de file ET la supprime de la file

#endif


