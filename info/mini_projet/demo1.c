#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_tab.h>
#include <image.h>
int main(int a, char** b) { int i,j,nbligne,nbcol;
   unsigned char** im=NULL; // Le tableau image
   SDL_Surface* fenetre=NULL;
   /* Creation d'une fenetre 640 x 480, couleurs sur 32 bits */
   fenetre=newfenetregraphique (840, 480);
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
}

//  Faire une fonction qui calcule la distance entre le patch en position is, js et celui
//  en position it,jt de taille taillepatch. Cette fonction retourne une constante
//  très grande DMAX si le pixel it,jt est un trou ou si Card(V(x,y,u,v)) est trop petit.
//  L’entête de la fonction sera unsigned int distance( PIXEL** im,
//  PIXEL** trous, int is, int js, int it, int jt, int
//  taillepatch, int nl, int nc)
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
         if (( trous[is + i][js + j] == 255) || ( trous[it + i][jt + j] == 255)) {
            // c'est un trou
            continue;
         }
         nb_pixel++;

         // on calcule la somme quadratique
         carre = img[is + i][js + j] - img[it + i][jt + j];
         somme += carre*carre;
      }
   }

   // la ditance quadratique est la somme quadratique divisé par le cardinal du nombre de pixel
   distance = somme / (nb_pixel*nb_pixel);

   return distance;
}

//  Faire une fonction qui calcule le patch le plus ressemblant à celui en position is,js
//  selon le §4. L’entête de la fonction sera void trouvemeilleurPPV(PPV**
//  champ, PIXEL** im, PIXEL** trous, int is, int js, int
//  taillepatch, int nl, int nc)
#include <stdlib.h>
#include <time.h>
#define NB_TEST_PATCH 100
srand(time(0));
void trouvemeilleurPPV(PPV**
      champ, PIXEL** im, PIXEL** trous, int is, int js, int
      taillepatch, int nl, int nc)
{
   int i.j;
   unsigned int dist;
   int patch_number;

   // on cherche un meilleur patch de manière aléatoire
   for (patch_number = 0 ; patch_number < NB_TEST_PATCH ; patch_number++) {
      // on génère un patch (dont la position ne déborde pas de l'image)
      int ip,jp; // postition du patch

      ip = random() % (nl - (2*taillepatch + 1));
      jp = random() % (nc - (2*taillepatch + 1));

      dist = distance (im, trous, is, js, ip, jp, taillepatch, nl, nc);
      i (dist < PPV[is][js].distance ) {
         PPV[is][js].distance = dist
      }
   }

   // on vérifie qu'un des voisin du meilleur patche n'est pas meilleur
   for (i=-1 ; i <= 1 ; i++) {
      for ( j=-1 ; j <= 1 ; j++ ) {
         dist = distance (im, trous, is, js, is + i*taillepatch, js + j*taillepatch, taillepatch, nl, nc);
         if (dist < PPV[is][js].distance ) {
            PPV[is][js].distance = dist;
         }
      }
   }

}

