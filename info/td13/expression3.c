#include "traceexp.h"
#include "arbre.h"

#define MAXFLOAT ((float)3.40282346638528860e+38) 


int main(int argc, char** argv) { char s[512];
  double xmin=-5, xmax=5;
  ARBRE r=NULL, d=NULL, ds=NULL;
  int dx=300,dy=200;
  SDL_Surface* f1;

  /*
	Lecture d'une expression prefixe au clavier 
  */
  puts("Entrer une expression"); gets(s);
  r=lire(s);

  /*
	Affichage de cette expression en notation classique
  */
  puts("Expression :"); affiche(r); puts("");

  /*
	Simplification et Affichage de cette expression en notation classique
  */
  puts("Expression simplifiee"); affiche(r=simplifie(r));


  /*
	Derivation et Affichage de cette derivee en notation classique
        Simplification et Affichage de cette derivee en notation classique
  */
  puts(""); puts("Derivee"); affiche(d=deriv(r)); puts("");
  puts("Derivee simplifiee"); affiche(ds=simplifie(deriv(r))); puts("");

 
  if ( (f1=newfenetregraphique(dx,dy)) == NULL) { printf("Visu graphique impossible\n"); exit(1); }
  puts("Entrer les bornes du trace (xmin et xmax): attention au domaine de definition");
  scanf("%lf %lf",&xmin,&xmax);

  /*
	Trace des 2 courbes
  */
  trace2courbe(f1,r,d,dx,xmin,xmax);
  getchar(); getchar(); 
  return 0;
}
