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
