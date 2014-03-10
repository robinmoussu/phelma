#include <image.h>
#include <stdlib.h>

unsigned int ** alloue_image_int(int nl, int nc) { int i;
  unsigned int** p;
  if ( (p=(unsigned int**)calloc(nl,sizeof(*p)))==NULL) return NULL;
  if ( (*p=(unsigned int*)calloc(nl*nc,sizeof(**p)))==NULL) return NULL;
  for (i=1; i<nl; i++) p[i]=p[i-1]+nc;
  return p;
}

unsigned char ** alloue_image_char(int nl, int nc) { int i;
  unsigned char** p;
  if ( (p=(unsigned char**)calloc(nl,sizeof(*p)))==NULL) return NULL;
  if ( (*p=(unsigned char*)calloc(nl*nc,sizeof(**p)))==NULL) return NULL;
  for (i=1; i<nl; i++) p[i]=p[i-1]+nc;
  return p;
}

void libereimage(void ** im) { free(*im); free(im); }

unsigned char** getrouge(unsigned char** ims,unsigned int** im,int nl,int nc) { int i,j;
  if (ims==NULL) ims=alloue_image_char(nl,nc);
  for (i=0; i< nl; i++) for (j=0; j< nc; j++) ims[i][j]=ROUGE(im[i][j]);
  return ims;
}

unsigned char** getvert(unsigned char** ims,unsigned int** im,int nl,int nc) { int i,j;
  if (ims==NULL) ims=alloue_image_char(nl,nc);
  for (i=0; i< nl; i++) for (j=0; j< nc; j++) ims[i][j]=VERT(im[i][j]);
  return ims;
}

unsigned char** getbleu(unsigned char** ims,unsigned int** im,int nl,int nc) { int i,j;
  if (ims==NULL) ims=alloue_image_char(nl,nc);
  for (i=0; i< nl; i++) for (j=0; j< nc; j++) ims[i][j]=BLEU(im[i][j]);
  return ims;
}

void setrouge(unsigned char**im, unsigned int** ims, int nl, int nc) { int i,j;
   for (i=0; i< nl; i++) for (j=0; j< nc; j++) SETROUGE(ims[i][j],im[i][j]);
}

void setvert(unsigned char**im, unsigned int** ims, int nl, int nc) { int i,j;
   for (i=0; i< nl; i++) for (j=0; j< nc; j++) SETVERT(ims[i][j],im[i][j]);
}

void setbleu(unsigned char**im, unsigned int** ims, int nl, int nc) { int i,j;
   for (i=0; i< nl; i++) for (j=0; j< nc; j++) SETBLEU(ims[i][j],im[i][j]);
}

