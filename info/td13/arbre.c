#include "arbre.h"

/*
  Fonction de creation d'un noeud a partir d'une chaine de caracteres contenant:
  Role :
     - alloue un espace memoire nŽcessaire a un oeoud
     - alloue et copie la chaine dans le noeud (champ val)
     - met a jour le type du noeud en fonction de la chaine 
          - variable
          - constante
          - operateur unaire (sin, cos, tan, sqrt, ...)
          - operateur binaire (+,-,*,/,^^)
*/

ARBRE creernoeud(char *c) {
  ARBRE r; double x;
  if (c==NULL || *c=='\0') { puts("Erreur de syntaxe"); exit(1); }
	/* Allocation memoire d'un noeud */
  r=calloc(1,sizeof(*r));
  if (r==NULL) { puts("Plus assez de memoire "); exit(1); }
	/* Copie de la chaine sur le noeud */
  r->val=strdup(c);
        /* Recherche du type de noeud */
	/* Est ce un nombre ? */
  if (sscanf(c,"%lf",&x)==1) { r->type=VALEUR; return r;}
  switch(*c) {
	/* Est ce un operateur classique? */
    case '+' : case '-': case '*': case '/' : case'^':
         r->type=OPERATEUR_BINAIRE; return r;
	/* Est ce une variable ? */
    case 'x': case 'y' :
          r->type=VARIABLE; return r; 
  } 
	/* Est ce une fonction connue ? */
  if (!strcasecmp(c,"sin") || !strcasecmp(c,"cos") || !strcasecmp(c,"tan") || !strcasecmp(c,"sqrt")
      || !strcasecmp(c,"exp") ) { r->type=OPERATEUR_UNAIRE; return r; }
  printf("%s : fonction non implantee\n",c);
  exit(1);;
}

/* 
   Focntion construisant un arbre a partir d'une chaine decoupee en mots

   Algo :
     recupere le premier mot de la chaine par la fonction strtok(NULL," ")
     si ce mot est
       - une constante ou une variable : construit et retourne le noued contenant cette constante ou cette variable
       - un operateur unaire : 
               construit le noued contenant cet operateur; 
               Le fils droit de ce noeud est vide.
               le fils gauche de ce noeud est le sous arbre obtenu par le reste de l'expression en cours d'analyse 
               retourne le noued ainsi obtenu
       - un operateur binaire : 
               construit le noued contenant cet operateur; 
               le fils gauche de ce noeud est le sous arbre obtenu par le reste de l'expression en cours d'analyse. Cette analyse s'arrete a la fin de l'expression contenant le fils gauche car les expressions sont bien construites 
               Le fils droit de ce noeud est le sous arbre obtenu par le reste de l'expression en cours d'analyse
               retourne le noued ainsi obtenu
*/

ARBRE construitarbre(char *c) {
  ARBRE r; 
  r=creernoeud(c);
  switch(r->type) {
    case OPERATEUR_BINAIRE:
         r->fg=construitarbre(strtok(NULL," ")); r->fd=construitarbre(strtok(NULL," "));
         return r;
    case OPERATEUR_UNAIRE :
         r->fg=construitarbre(strtok(NULL," ")); return r;
    case VARIABLE: case VALEUR:
         return r;
  }
  return NULL;
}

/*
  Fonction qui construit un arbre a partir d'une expression.
  Elle decoupe la chaine en suite de mot (fonction strtok). Les appels suivants a strtok permettront de recuperer les mots les uns apres les autres.
  Elle appelle ensuite la creation d'un arbre a partir d'une suite de mots
*/
ARBRE lire(char *s) {
  char *c = strtok(s," ");
  return construitarbre(c);
}

/*
  Fonction qui libere la memoire alloue pour un arbre
*/
ARBRE libere(ARBRE r) { 
  if (r!=NULL) { libere(r->fg); libere(r->fd); free(r->val); r->val=NULL; r->fg=r->fd=NULL; free(r); return NULL;}
}

/*
	recherche un noeud de type VALEUR dont tout le chemin comporte des neoud de meme type ie + ou * 
 	Permet alors de simplifier les expressions en regroupant les constantes
*/
ARBRE perefeuillecte(ARBRE r, char t) { ARBRE c1, c2; 
  if (r==NULL) return r;
  else if (r->type == OPERATEUR_BINAIRE && r->val[0]==t) 
          if (r->fd->type == VALEUR|| r->fg->type == VALEUR) return r; 
          else { ARBRE c1=perefeuillecte(r->fg,t), c2=perefeuillecte(r->fd,t);
            if (c1) return c1;
            if (c2) return c2;
            return NULL;
         }
  return NULL; 
}    

#define SWAP(x,y,type) { type inter; inter=(x); (x)=(y); (y)=inter; }

ARBRE simplifie1(ARBRE r);

void affiche2(ARBRE r)  { if (r) { printf("%s ",r->val); affiche2(r->fg); if (r->type==OPERATEUR_BINAIRE) affiche2(r->fd); }}


int arrangecste(ARBRE r, char oper) {
  if (r!=NULL && r->type==OPERATEUR_BINAIRE &&  r->val[0]==oper ) { 
      ARBRE c3=perefeuillecte(r->fg,oper);
      ARBRE c4=perefeuillecte(r->fd,oper);
      if (c3 && c4) { 
        if (c3->fd->type==VALEUR)
           if (c4->fd->type==VALEUR) SWAP(c3->fd,c4->fg,ARBRE)
           else SWAP(c3->fd,c4->fd,ARBRE)
        else if (c4->fd->type==VALEUR) SWAP(c3->fg,c4->fg,ARBRE)
              else SWAP(c3->fg,c4->fd,ARBRE)
        return 1;
     }
  }
  return 0;
}


ARBRE simplifie1(ARBRE r) {
  if (r!=NULL) { 
    switch(r->type) {
      case VALEUR: case VARIABLE : return r;
      case OPERATEUR_UNAIRE: r->fg=simplifie1(r->fg); return r;
      case OPERATEUR_BINAIRE : r->fd=simplifie1(r->fd); r->fg=simplifie1(r->fg);
        if (r->fd && r->fd->type==VALEUR && r->fg && r->fg->type==VALEUR) { char s[512]; int i;
          double x=eval(r,0); sprintf(s,"%lf",x); for(i=strlen(s)-1; i>0 && s[i]=='0'; i--) s[i]=0; libere(r); return creernoeud(s);
        }
        if(r->val[0]=='+' ) { ARBRE c1=r->fd, c2=r->fg, c=NULL;
          if((c1->type==VALEUR && atof(c1->val)==0 && (c=c1)!=NULL) || (c2->type==VALEUR && atof(c2->val)==0&& (c=c2)!=NULL)){ 
             free(r->val); free(r); free(c->val); free(c); return simplifie1(c==c2? c1 : c2); 
          }
          if(c1->type==VALEUR && (c=perefeuillecte(r->fg,'+'))) {
             if (c->fd->type==VALEUR) SWAP(r->fd,c->fg,ARBRE) else SWAP(r->fd,c->fd,ARBRE)
             return simplifie1(r);
          }
          if(c2->type==VALEUR && (c=perefeuillecte(r->fd,'+'))) {
             if (c->fd->type==VALEUR) SWAP(r->fg,c->fg,ARBRE) else SWAP(r->fg,c->fd,ARBRE)
             return simplifie1(r);
          }
          else { return (r); }
        }
        else if(r->val[0]=='-') { ARBRE c1=r->fd, c2=r->fg;
          if(c1->type==VALEUR && atof(c1->val)==0) { free(r->val); free(r); free(c1->val); free(c1); return simplifie1(c2); }
          else { return (r); }
        }
        else if (r->val[0]=='*') { ARBRE c1=r->fd, c2=r->fg, c3=NULL, c=NULL;
          if(c1->type==VALEUR && atof(c1->val)==0) { libere(r); return creernoeud("0"); }
          if(c2->type==VALEUR && atof(c2->val)==0) { libere(r); return creernoeud("0"); }
          if(c1->type==VALEUR && atof(c1->val)==1) { free(r->val); free(r); free(c1->val); free(c1); return simplifie1(c2); }
          if(c2->type==VALEUR && atof(c2->val)==1) { free(r->val); free(r); free(c2->val); free(c2); return simplifie1(c1); }
          if(c1->type==VALEUR && (c=perefeuillecte(r->fg,'*'))) {
             if (c->fd->type==VALEUR) SWAP(r->fd,c->fg,ARBRE) else SWAP(r->fd,c->fd,ARBRE)
             return simplifie1(r);
          }
          if(c2->type==VALEUR && (c=perefeuillecte(r->fd,'*'))) {
             if (c->fd->type==VALEUR) SWAP(r->fg,c->fg,ARBRE) else SWAP(r->fg,c->fd,ARBRE)
             return simplifie1(r);
          }
          return (r); 
        }
        else if (r->val[0]=='/') { ARBRE c1=r->fd, c2=r->fg;;
          if(c1->type==VALEUR && atof(c1->val)==1) { free(r->val); free(r);; free(c1->val); free(c1); return simplifie1(c2); }
          else { return (r); }
        }
        else if (r->val[0]=='^') { ARBRE c1=r->fd, c2=r->fg;;
          if(c1->type==VALEUR && atof(c1->val)==1) { free(r->val); free(r);; free(c1->val); free(c1); return simplifie1(c2); }
          if(c1->type==VALEUR && atof(c1->val)==0) { libere(r); return(creernoeud("1")); }
          else { return (r); }
        }
        else { return r; }
    }
  }
  return NULL;
}


ARBRE  simplifie(ARBRE r) {
  do { 
    r=simplifie1(r);
  } while (arrangecste(r,'*')==1 || arrangecste(r,'+')==1);
  return (r);
}

