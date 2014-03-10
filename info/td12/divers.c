#include <stdio.h>
#include <string.h>

/// compte le nombre de ligne dans un dictionnaire
int nbligne(char *fic) { FILE* fp; int c=0; char flag=0;
  if ( (fp=fopen(fic,"rt"))==NULL) return 0;
  else
    while (!feof(fp))
      if (fgetc(fp)=='\n') {if (flag) c++; flag=0;}
      else flag=1;
  fclose(fp);
  return c;
}

/// enleve tout les caractere invalide de mot
int lecture(FILE* fp, char* mot) {
  char inter[512];
  int i,j;
  if (fscanf(fp,"%[^\n -]s",mot)==EOF) return 0; 
  fscanf(fp,"%*c");
  for (i=j=0; mot[i]; i++)
    if (!ispunct(mot[i])) inter[j++]=mot[i];
    else if (mot[i]=='\'') j=0;
  inter[j]=0;
  strcpy(mot,inter);
  return 1;
}

int lectureLigneDico(char* mot, int n, FILE *fp) {
  if (fgets(mot,n,fp)==NULL) return 0;
  if (mot[strlen(mot)-1]<' ') mot[strlen(mot)-1]=0;
  return 1;
}
