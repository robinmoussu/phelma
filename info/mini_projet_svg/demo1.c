#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_tab.h>
#include <image.h>

#include <stdlib.h>
#include <time.h>
#define NB_TEST_PATCH 100

SDL_Surface* newfenetregraphique (int,int);
void ecritureimagepgm(char*,unsigned char**,int,int) ;

#include "inpaint.h"


typedef enum { false, true } bool;

/***********************************************/

int main() { int i,j,nbligne,nbcol;
	unsigned char** im=NULL; /* Le tableau image */
	SDL_Surface* fenetre=NULL;
	/* Creation d'une fenetre 640 x 480, couleurs sur 32 bits */
	fenetre= newfenetregraphique (840, 480);
	/* Lecture du fichier image pgm, en niveau de gris, sur 8 bits */
	im = lectureimage8("lena2.pgm",&nbligne,&nbcol);
	/* On place cette image dans la fenetre, en position 10 20
	Attention : la fenetre doit pouvoir contenir l’image */
	afficheim8SDL(fenetre,im,nbligne,nbcol,10,20);
	/* On parcourt toute l'image et on inverse chaque pixel */
	for (i=0; i<nbligne; i++) for (j=0; j<nbcol; j++) im[i][j]=255-im[i][j];
	/* On affiche cette nouvelle image sur l'ecran, en position 350 150 */
	afficheim8SDL(fenetre,im,nbligne,nbcol,350,150);
	puts("Taper pour continuer"); getchar();
	/* On sauve l'image modifie dans un fichier image pgm, en niveau de gris, sur 8 bits */
	ecritureimagepgm("resultat.pgm",im,nbligne,nbcol) ;

	srand(time(0));

	return 0;
}

/***********************************************/

/*
//  Faire une fonction qui calcule la distance entre le patch en position is, js et celui
//  en position it,jt de taille taillepatch. Cette fonction retourne une constante
//  très grande DMAX si le pixel it,jt est un trou ou si Card(V(x,y,u,v)) est trop petit.
//  L’entête de la fonction sera unsigned int distance( PIXEL** im,
//  PIXEL** trous, int is, int js, int it, int jt, int
//  taillepatch, int nl, int nc)
*/
unsigned int distance( PIXEL** im,
      PIXEL** trous, int is, int js, int it, int jt, int
      taillepatch, int nl, int nc)

{
   int distance;
   int somme = 0;
   int nb_pixel = 0;
   int i, j;

   for (i = -taillepatch; i<=taillepatch; i++) {
      for (j = -taillepatch; j<=taillepatch; j++) {
         int carre;
		 if ((is - i < 0) || (is + i > nl) || (js - j < 0) || (js + j > nc)) {
		 /* on est hors de l'image */
			continue;
		 }
         if (( trous[is + i][js + j] == TROU) || ( trous[it + i][jt + j] == TROU)) {
            /* c'est un trou */
            continue;
         }
         nb_pixel++;

         /* on calcule la somme quadratique */
         carre = im[is + i][js + j] - im[it + i][jt + j];
         somme += carre*carre;
      }
   }

   /* la ditance quadratique est la somme quadratique divisé par le cardinal du nombre de pixel */
   distance = somme / (nb_pixel*nb_pixel);

   return distance;
}

/*
//  Faire une fonction qui calcule le patch le plus ressemblant à celui en position is,js
//  selon le §4. L’entête de la fonction sera void trouvemeilleurPPV(PPV**
//  champ, PIXEL** im, PIXEL** trous, int is, int js, int
//  taillepatch, int nl, int nc)
*/
void trouvemeilleurPPV(PPV**
       champ, PIXEL** im, PIXEL** trous, int is, int js, int
       taillepatch, int nl, int nc)
{
   int i,j;
   int dist;
   int patch_number;
                        
   /* on cherche un meilleur patch de manière aléatoire */
   for (patch_number = 0 ; patch_number < NB_TEST_PATCH ; patch_number++) {
      /* on génère un patch (dont la position ne déborde pas de l'image) */
      int ip,jp; /* postition du patch */

      ip = (rand() % (nl - (2*taillepatch + 1))) + taillepatch;
      jp = (rand() % (nc - (2*taillepatch + 1))) + taillepatch;

      dist = distance (im, trous, is, js, ip, jp, taillepatch, nl, nc);
      if (dist < champ[is][js].d ) {
         champ[is][js].d = dist;
      }
   }

   /* on vérifie qu'un des voisins du meilleur patche n'est pas meilleur */
   for (i=-1 ; i <= 1 ; i++) {
      for ( j=-1 ; j <= 1 ; j++ ) {
         dist = distance (im, trous, is, js, is + i*taillepatch, js + j*taillepatch, taillepatch, nl, nc);
         if (dist < champ[is][js].d ) {
            champ[is][js].d = dist;
         }
      }
   }
}

/*
// Faire une fonction qui réalise l’inpainting: elle réalise les opérations du §. L’entête de
// la fonction sera unsigned char** inpaint(unsigned char** im,
// unsigned char** trous, int taillepatch, int nbiter, int nl,
// int nc)
*/
unsigned char** inpaint(unsigned char** im,
unsigned char** trous, int taillepatch, int nbiter, int nl,
int nc)
{
	int i,j,n;
	int u, v;
	bool reste_trou = true;
	PPV** champ = alloue_champPPV(nl, nc);
	unsigned char ** rst = alloue_image(nl, nc);

	initialisePPV (champ, im, trous, taillepatch, nl, nc);
	do {
		reste_trou = false;

		for (i=0 ; i<nc ; i++) {
			for (j=0 ; j<nl ; j++) {
				if (trous[i][j] == TROU) {
					reste_trou = true;
					if ( isborddetrou(i, j, trous, nl, nc, taillepatch)) {
						for (n = 0; n<nbiter ; n++) {
							trouvemeilleurPPV(champ, im, trous, i, j,
		   						taillepatch, nl, nc);
						}
						trous[i][j] = !TROU;
					}
				}
			}
		}
	} while (reste_trou == true);

	/* on fabrique l'image de destination à partir des patchs */
	for (i=0 ; i<nc ; i++) {
		for (j=0 ; j<nl ; j++) {
			u = champ[i][j].u;
			v = champ[i][j].v;
			rst[i][j] = im[u][v];
		}
	}
	return rst;
}



