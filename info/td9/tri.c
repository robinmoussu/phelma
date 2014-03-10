/* vim: set sw=4 ts=4 sts=4 et tw=78 foldmarker={,} foldlevel=0 foldmethod=marker spell:*/

#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void Swap (double *a, double *b)
{
    double tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int Pere (int n)
{
    return (n-2)/2;
}

int Fils_gauche (int n)
{
    return 2*n + 1;
}

int Fils_droit (int n)
{
    return 2*n + 2;
}

void Affiche_tas (double *tas, int n)
{
    int i;
    int ligne = 1;

    for (i = 0; i<n ; i++) {
        if (i+1 >= ligne*2) {
            printf ("\n");
            ligne *= 2;
        }
        printf("%4.0f", tas[i]);

    }
    printf("Affiche_tas");
    printf("\n");
    printf("Affiche_tas");
}

/* ajoute le nombre dont l’indice est « n » au tas « tas »
 * existant. L’élément à ajouter est déjà dans le tableau « tas
 * ». Avant exécution de cette fonction, ce tableau forme déjà un tas entre les indices 0 et n
 * - 1. Après exécution de cette fonction, ce tableau forme un tas entre les indices 0 et n
 */
void Augmente_tas (double *tas, int n)
{
    int i = n-1;

    printf("\n Augmente_tas");
        printf("%4.0f", tas[n-1]);
    while ((tas[i] > tas[Pere(i)]) && i!=0 ) {
    printf("- %d", i);
        /* le tas n'est pas trié */
        Swap(&tas[Pere(i)], &tas[i]);
        i = Pere(i);
    }
    printf("\n Augmente_tas");
}

/* qui établit un tas à partir du tableau tas de n
 * éléments. Avant l’exécution de cette fonction, le tableau « tas
 * » contient n éléments non organisés en tas. Après exécution, les éléments du tableau
 * « tas » ont été réorganisés pour former un tas entre les indices 0 et n -  1.
 */
void Construction_tas(double* tas, int n)
{
    int i;

    for (i=1; i<n; i++) {
        printf("\n Construction_tas");
        printf(" %d", i);
        Augmente_tas(tas,i);
        printf("---");
    }
        printf("###");
    printf("\n Construction_tas");

}

/* Cette fonction fait descendre le premier élément (la
 * racine du tas) à sa place. Avant l’appel, les éléments entre les indices 1 et n respectent les
 * conditions d’un tas, mais pas l’element d’indice 0. Après l’execution de cette fonction, les
 * éléments d’indice 0 à n forment un tas.
 */
void Descendre_tas(double* tas, int n)
{
    int i=0;    /* indice de l'élément à comparer */

    while (1) {
        if (Fils_gauche(i) < n) {
            if (tas[Fils_gauche(i)] > tas[i]) {
                Swap(&tas[Fils_gauche(i)], &tas[i]);
                i = Fils_gauche(i);
            }
        } else if (Fils_droit(i) < n) {
            if (tas[Fils_droit(i)] > tas[i]) {
                Swap(&tas[Fils_droit(i)], &tas[i]);
                i = Fils_droit(i);
            }
        } else {
            /* le tas est trié, on s'arrete */
            break;
        }
    }
}

/* supprime le premier nombre de « tas » en l’échangeant avec le dernier (indice n -  1)
 * et en réorganisant le tas ensuite. On suppose qu’avant l’appel de cette fonction, le paramètre «
 * tas  » est un tas de n éléments (tableau). Après exécution, le paramètre «
 * tas » est un tas de n - 1 éléments, l’élément supprimé (celui qui était le premier) est à l’indice n
 * - 1 dans le tableau « tas ».
 */
void Suppression_tas(double* tas, int n)
{
    Swap(&tas[0], &tas[n-1]);
    Descendre_tas(tas, n-1);
}

/* qui trie le tableau « tas » par la méthode décrite ci dessus. La fonction construit
 * un tas, puis ordonne les éléments selon la méthode décrite. Après
 * exécution, le paramètre « tas » est tableau trié par ordre croissant de n éléments
 */
void Tri(double *t, int n)
{
    int i;

    Construction_tas(t,n);
    for (i=n; i>0; i--) {
        Suppression_tas(t, n);
    }
}

/* fonction de comparaison utilise pour le quick sort */
int Compare ( const void* ax, const void * ay)
{
    return( *((double *)ax)- *((double *)ay));
}

void Benchmark ()
{
    int     LO;                             /* Nombre de reels a trier : 10E LO */
    clock_t avant, apres;
    double  temps1[100], temps2[100];
    double  *t1, *t2;
    int     i,j,k,l,m;

    /* Lecture du nombre d’octaves au clavier */
    printf("Nombre d'octave a trier "); fflush(stdout); scanf("%d", &LO);
    /* Creation des tableaux a trier */
    if ( (t1=calloc(pow(10,LO+1),sizeof(*t1))) == NULL) {
        printf("Allocation impossible\n"); exit(1);
    }
    if ( (t2=calloc(pow(10,LO+1),sizeof(*t1))) == NULL) {
        printf("Allocation impossible\n"); exit(1);
    }

    /* Initialisation du generateur aleatoire */
    srand(time(0));

    /* Premiere boucle sur le nombre d’octave */
    for (k=10,i=m=0; i<LO; k*=10,i++) {
        for (j=1; j<10; j++) {
            /* j*k est le nombre d’elements a trier */
            printf("%d ", j*k); fflush(stdout);
            /* Tirage aleatoire des nombres a trier */
            for (l=0; l<j*k; l++) {
                t1[l]=rand();
            }
            /* Copie dans le deuxieme tableau */
            memcpy(t2,t1,j*k*sizeof(double));
            avant = clock();
            /* Tri par quick sort */
            qsort(t1,j*k,sizeof(*t1),Compare);
            apres = clock();
            temps1[m]=(double)(apres - avant)/CLOCKS_PER_SEC;
            /* Tri par ma fonction */
            avant = clock(); Tri(t2,j*k); apres = clock();
            temps2[m]=(double)(apres - avant)/CLOCKS_PER_SEC;
            /* Affichage des temps des 2 tris */
            printf("Quick sort :%f Mon tri: %f\n", temps1[m], temps2[m]);
            m++;
        }
    }
    /* Liberation mémoire */
    free(t1);
    free(t2);
}

void Test()
{
    int i;
    double tas[] = {85, 71, 36, 55, 49, 26, 27, 20, 14, 32, 90};
    /*Le dernier élément n'est pas trié*/
    int size = sizeof(tas) / sizeof(double);

    printf("Test\n");

    Affiche_tas(tas, size);
    Augmente_tas (tas, size);
    Affiche_tas(tas, size);
    Construction_tas(tas,size);
    printf("««««");
    Affiche_tas(tas, size);
    printf("««««");
    for (i=size; i>0; i--) {
        printf("%d i ", i);
        Suppression_tas(tas, i);
    }
    Affiche_tas(tas, size);

    printf("Fin test\n");
}

int main()
{

    Test();
    /*Benchmark();*/
    return 0;
}


