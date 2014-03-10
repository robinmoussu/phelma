#include <SDL_phelma.h>
/*
#include <SDL_courbes.h>
*/
#include <time.h>
#include <math.h>

void CourbeTableau_char(SDL_Surface* f1, unsigned char* tab, int nbpoints, int imin, int imax, unsigned char min, unsigned char max, int coul) {
  int i, i1,val1,i2,val2;
  if (nbpoints<=0 || min>=max) return;

  i1 = imin;
  val1 = (f1->h-1) -(tab[0]-min)*(f1->h-1)/(max-min);
  for (i=i1+1; i<imax; i++) {
    val2 = (f1->h-1)-(tab[i]-min)*(f1->h-1)/(max-min);
    i2 = floor(((i)*(double)f1->w)/ (double)(nbpoints-1));
    Draw_Line(f1,i1,val1,i2,val2,coul);
    i1=i2; val1=val2;
  }
  SDL_Flip(f1);
}


void CourbeminmaxCouleur_char(SDL_Surface* f1, unsigned char* tab, int nbpoints, unsigned char min, unsigned char max, int coul) {
  int i, i1,val1,i2,val2;
  if (nbpoints<=0) return;
  CourbeTableau_char(f1,tab,nbpoints,0,nbpoints,min,max,coul);
}

void CourbeCouleur_char(SDL_Surface* f1, unsigned char* tab, int nbpoints,int coul) { 
  unsigned char min,max;
  int i;
  for (i=1, min=max=tab[0]; i<nbpoints; i++) 
    if (tab[i]>max) max=tab[i];
    else if (tab[i]<min) min=tab[i];
  if (min==max) return;
  CourbeminmaxCouleur_char(f1,tab,nbpoints,min,max,coul);
}

void Courbe_char(SDL_Surface* f1, unsigned char* tab, int nbpoints) { 
  CourbeCouleur_char(f1,tab,nbpoints,0); 
}


void Courbeminmax_char(SDL_Surface* f1, unsigned char* tab, int nbpoints, unsigned char min, unsigned char max) { 
  CourbeminmaxCouleur_char(f1,tab,nbpoints,min,max,0);
}

void Courbenoire_char(SDL_Surface* f1, unsigned char* tab, int nbpoints ){ 
  Courbe_char(f1,tab,nbpoints);
}

void CourbeXYminmax(SDL_Surface* f1, double* x, double* y, int nbpoints, double xmin, double xmax, double ymin, double ymax,int coul) {
int i, i1,val1,i2,val2;
  if (nbpoints<=0 || xmin>=xmax) return;

  i1 = (x[0]-xmin)*f1->w/(xmax-xmin);;
  val1 = (f1->h-1)-(y[0]-ymin)*f1->w/(ymax-ymin)-1;
  for (i=1; i<nbpoints; i++) {
    val2 = (f1->h-1)-(y[i]-ymin)*f1->w/(ymax-ymin)-1;
    i2 = (x[i]-xmin)*f1->w/(xmax-xmin);
    Draw_Line(f1,i1,val1,i2,val2,coul);
    i1=i2; val1=val2;
  }
   SDL_Flip(f1);
}
