/*
*/

#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_draw.h>
#include <SDL_phelma.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609
#endif

void VanKoch (float x1, float y1, float x5, float y5, int ordre, SDL_Surface* f, int couleur);
void DrawVanKoch (int ordre, SDL_Surface* f, int couleur, int wight, int hight);
void DrawSnow (int ordre, SDL_Surface* f, int couleur, int wight, int hight);

int main() {
    SDL_Surface* f;
    int couleur;
    int ordre;
    int wight = 300;
    int hight = 100;

    /* Initialisation de la bibliotheque video  */
    /* Creation d'une fenetre de dimension dimx x dimy, couleurs sur 32 bits */
    f=newfenetregraphique(wight,hight);
    if ( f== NULL) { printf("Impossible d'ouvrir la fenetre d'(affichageõ"); exit(1);}
    couleur= 0; /*0xff0000FF;*/
    /*Draw_Line(f,10,0,300,50,couleur);*/
    /*SDL_Flip(f);*/


    printf ("ordre ? ");
    scanf ("%d", &ordre);

    printf ("couleur ? ");
    scanf ("%d", &couleur);
    DrawVanKoch (ordre, f, couleur, wight, hight);

    printf ("couleur ? ");
    scanf ("%d", &couleur);
    DrawSnow (ordre, f, couleur, wight, hight);


    getchar();

    return 0;
}

void VanKoch (float x1, float y1, float x5, float y5, int ordre, SDL_Surface* f, int couleur)
{
    if (ordre == 0) {
    Draw_Line(f,10,0,300,50,couleur);
        Draw_Line(f,x1,y1,x5,y5, couleur);
    } else {
        float x2, y2, x3, y3 , x4, y4;
        x2 = (x1* 2 +x5)/ 3.f;
        y2 = (y1* 2 +y5)/ 3.f;
        x4 = (x1+x5* 2)/ 3.f;
        y4 =(y1+y5* 2)/ 3.f;
        x3 = x2/2.f - cos(M_PI/ 6)*y2+x4/ 2 +cos(M_PI/ 6)*y4;
        y3 = cos( M_PI/ 6)*x2+y2/ 2. - cos(M_PI/ 6)*x4+y4/ 2.f;

        VanKoch (x1, y1, x2, y2, ordre-1, f, couleur);
        VanKoch (x2, y2, x3, y3, ordre-1, f, couleur);
        VanKoch (x3, y3, x4, y4, ordre-1, f, couleur);
        VanKoch (x4, y4, x5, y5, ordre-1, f, couleur);
    }
}


void DrawVanKoch (int ordre, SDL_Surface* f, int couleur, int wight, int hight)
{
    VanKoch (0,0, wight, hight, ordre, f, couleur);
    SDL_Flip(f);
}

void DrawSnow (int ordre, SDL_Surface* f, int couleur, int wight, int hight)
{
    VanKoch (wight/3.f, hight/3.f, wight*2.f/3.f, hight/3.f, ordre, f, couleur);
    VanKoch (wight/3.f, hight/3.f, wight/2.f, hight*2.f/3.f, ordre, f, couleur);
    VanKoch (wight/2.f, hight*2.f/3.f, wight*2.f/3.f, hight/3.f, ordre, f, couleur);
    SDL_Flip(f);
}


