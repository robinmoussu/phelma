#ifndef SDL_tab
#define SDL_tab

int copyim32toSDL(SDL_Surface* f1, unsigned int ** im, int ligne, int col,int x, int y) ;
int afficheim32SDL(SDL_Surface* f1, unsigned int ** im, int ligne, int col, int x, int y) ;
int copyim8toSDL(SDL_Surface* f1, unsigned char ** im, int ligne, int col, int x, int y) ;
int afficheim8SDL(SDL_Surface* f1, unsigned char ** im, int ligne, int col, int x, int y) ;
int afficheimageSDL(SDL_Surface* f1, void** im, int ligne, int col, int octetparpixel) ;
unsigned int** SDLtoim32(SDL_Surface* f1) ;
unsigned char ** SDLtoim8(SDL_Surface* f1) ;
unsigned char ** lectureimage8(char* fichier, int* pligne, int* pcolonne);
unsigned int  ** lectureimage32(char* fichier, int* pligne, int* pcolonne);

void ecritimagepgm(char*, unsigned char **, int , int);
void ecritimageppm(char*, unsigned int **, int , int);
#endif
