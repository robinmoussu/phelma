/* Auteur : François Lemaire */

#ifndef _LIBGRAPH_H
#define _LIBGRAPH_H     1

#include <X11/X.h>
#include <X11/Xlib.h>

#define FONT "fixed"

/* Declaration de types */

typedef unsigned long tCouleur;

typedef struct _tPoint {
  int x,y;
} tPoint;

typedef XImage tImage;

/* Declaration des couleurs de bases */
extern tCouleur cBlanc, cNoir, cRouge, cBleu, cVert, cCyan, cMagenta, cJaune;

/* Initialisations, ... */
void initialiseX11(int, int);
void changeTitre(char*);
void fermeX11();
void changeRaffraichissement(Bool);

/* Gestion de la taille de la fenetre */
int largeurFenetre();
int hauteurFenetre();

/* Gestion des couleurs */
tCouleur determineCouleur(unsigned char, unsigned char, unsigned char);
void selectCouleur(tCouleur);
tCouleur recupCouleur();
unsigned char compRouge(tCouleur); 
unsigned char compBleue(tCouleur); 
unsigned char compVerte(tCouleur); 

/* Primitives de trac'e */
void raffraichitEcran();
void remplitEcran(tCouleur);
tCouleur recupPoint(tPoint);
void point(tPoint);
tCouleur recupPoint(tPoint);
void ligne(tPoint, tPoint);
void rectangle(tPoint, tPoint);
void rectanglePlein(tPoint, tPoint);
void cercle(tPoint, int);
void cerclePlein(tPoint, int);
void ellipse(tPoint, int, int);
void ellipsePleine(tPoint, int, int);
void arc(tPoint, int, int, float, float);
void arcPlein(tPoint, int, int, float, float);

/* Entrées/Sorties */
int sauveEcran(char*);
int chargeEcran(char*);

/* Images */
tImage *recupImage();
void afficheImage(tImage*);
void libereImage(tImage*);
tCouleur recupImagePoint(tImage*, tPoint);
void imagePoint(tImage*, tPoint);

/* Gestion des fontes */
int selectFonte(char*);
void ecritChaine(tPoint, char*);
void tailleChaine(char*, int*, int*, int*);

/* Clavier */
KeySym litTouche();
void pauseJusqueEntree();

#endif

unsigned char *load_pixmap(char *filename, int *width, int *height);

int load_RGB_pixmap(char *filename, int *width, int *height,
	unsigned char**R_data, unsigned char**G_data, unsigned char**B_data);

void store_pixmap(char *filename, unsigned char *data, int width, int height);

void store_RGB_pixmap(char *filename,
	unsigned char *R_data, unsigned char *G_data, unsigned char *B_data,
	int width, int height);

