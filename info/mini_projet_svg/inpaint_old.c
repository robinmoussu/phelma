#include <stdio.h>
#include <stdlib.h>

#define DMAX 100000

typedef unsigned char PIXEL;

typedef struct {int u;
		int v;
		int d;} PPV;

unsigned char ** alloue_image(int nl, int nc){PIXEL **p; int i;

	p=(PIXEL **)calloc(nl,sizeof(*p));
	if (*p ==NULL) return NULL; 
	else {
		*p=(PIXEL*)calloc(nc*nl,sizeof(**p));
		if (*p==NULL){ 
			return NULL; 
		}
		else {
			for (i=1;i<nl;i++) { 
				p[i]=p[i-1]+nc;
			}
		}
	}
	return p;
}
		
PPV ** alloue_champPPV(int nl, int nc){PPV **p; int i;

	p=(PPV **)calloc(nl,sizeof(*p));
	if (*p ==NULL) return NULL; 
	else {
		*p=(PPV*)calloc(nc*nl,sizeof(**p));
		if (*p==NULL){ 
			return NULL; 
		}
		else {
			for (i=1;i<nl;i++) { 
				p[i]=p[i-1]+nc;
			}
		}
	};	
	return p;
}

		

void initialisePPV (PPV** champ, PIXEL** im, PIXEL ** trous, int taille, int nl, int nc){ int i, j;
	
	for (i=0;i<nl;i++){
		for (i=0;i<nc;i++){

			if (trous[i][j]==0){
				champ[i][j].u=i;
				champ[i][j].v=j;
				champ[i][j].d=0;
			}
			else{
				champ[i][j].u=i;
				champ[i][j].v=j;
				champ[i][j].d=DMAX;
			}
		}
	}
}
			










































