#include <stdio.h>
#include <stdlib.h>

#define DMAX 100000
#define nbiter 100

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
      for (j=0;j<nc;j++){

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




int isborddetrou(int x, int y, PIXEL** trous, int nl, int nc, int taillepatch){	


   if ((x>taillepatch) & (y>taillepatch) & (x<nc-taillepatch) & (y< nl-taillepatch) & (trous[x][y]=0) & ((trous[x+1][y]==0) || (trous[x][y+1]==0) || (trous[x-1][y]==0) || (trous[x][y-1]==0))){ 
      return 1;
   }

   else return 0;
}


void optimisePPV(PPV** champ, PIXEL** im, PIXEL**zone, PIXEL** trous, int nb, int taillepatch, int nl, int nc){
   
      PIXEL** imr; int i,j,k,l;
      
      imr= alloue_image( nl, nc);
      
      for (i=0;i<nl;i++){
         for(j=0;j<nc;j++){
            if (champ[i][j].d!=0){
               champ[i][j].u = rand()%256 ; 
               champ[i][j].v = rand()%256;
            }
         }
      }
   
      
      while (trous!=NULL){
         for (k=0;k<nbiter;k++){
            for(i=0;i<nl;i++){
               for(j=0;j<nc;j++){
                  if (champ[i][j].d==0){
                     if(isborddetrou(i,j,trous,nl, nc, taillepatch)==1){
                        trouvemeilleurPPV(champ, im, trous, i, j, taillepatch, nl, nc);
                     }
                  }
               }
            }
         }
      }
   


      for(i=0;i<nl;i++){
         for(j=0;j<nc;j++){
            if (champ[i][j].d==0){
               if(isborddetrou(i,j,trous,nl, nc, taillepatch)==1){
                  for(k=-1;k<2;k++){
                     for(l=-1;l<nc;l++){	
                        im[i+k][j+l]=im[champ[i][j].u+k][champ[i][j].v+l];
                        trous[i+k][j+l]=0;
                     }
                  }
               }
            }
         }
      }



}






































