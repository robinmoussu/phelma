
#ifndef INPAINT
#define INPAINT

#define DMAX 100000

typedef unsigned char PIXEL;

typedef struct {int u;
		int v;
		int d;} PPV;

#define TROU 255

unsigned char ** alloue_image(int nl, int nc);
PPV ** alloue_champPPV(int nl, int nc);
void initialisePPV (PPV** champ, PIXEL** im, PIXEL ** trous, int taille, int nl, int nc);
int isborddetrou(int x, int y, PIXEL** trous, int nl, int nc, int taillepatch);

unsigned int distance( PIXEL** im,
      PIXEL** trous, int is, int js, int it, int jt, int
      taillepatch, int nl, int nc);
void trouvemeilleurPPV(PPV**
       champ, PIXEL** im, PIXEL** trous, int is, int js, int
       taillepatch, int nl, int nc);


#endif
