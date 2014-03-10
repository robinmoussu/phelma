#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SDL_phelma.h>

/* variables globales, il y a surement moyen d'ameliorer cela en passant par SDL_AudioSpec.userdata */
/* Les données du fichier son a jouer*/
static Uint8 * sounddata;
/* La taille du fichier son, en octets */
static Uint32 soundlength;
/* Position courante de lecture dans le fichier son */
static Uint32 soundpos;



/* Fonction qui copie les données sonores dans le tampon audio. 
Cette fonction est passée en parametre dans la structure SDL_AudioSpec 

	- void * userdata : donnees passées en paramètre à la fonction de rappel
	- Uint8 * stream : données à jouer
	- int len : taille des données à jouer
*/
void mixaudio(void * userdata, Uint8 * stream, int len){
  /* definition des donnees a copier avec verification de debordement */
  Uint32 tocopy = soundlength - soundpos > len ? len : soundlength - soundpos; 

  /* Copie des données dans le tampon audio */
  memcpy(stream, sounddata + soundpos, tocopy); 

  /* Mise à jour de la position de lecture */
  soundpos += tocopy;
}

/*	Fonction qui convertie des données audio d'un format vers un autre (par exemple celui du peripherique audio de la machine). 
	- void* son_in : données audio d'entree
	- int taille_in : taille des données d'entrée
	- SDL_AudioSpec input : format audio des données d'entrée
	- Uint8** son_out : données de sortie converties
	- Uint32* taille_out : taille des données converties
	- SDL_AudioSpec output : format des données converties
	
	renvoit 0 si succès
*/
int convert_input_output(void* son_in, int taille_in, SDL_AudioSpec input, Uint8** son_out, Uint32* taille_out, SDL_AudioSpec output) {
	/* on declare un Audio Conversion Structure pour convertir le son a jouer vers le format du péripherique */
	SDL_AudioCVT cvt; 

	/* creation du convertisseur audio */
  	if (SDL_BuildAudioCVT(&cvt, input.format, input.channels, input.freq, output.format, output.channels, output.freq) < 0) {
    		printf("Impossible de construire le convertisseur audio: %s\n", SDL_GetError());
    		return 1;
  	}

  	/* Création du tampon utilisé pour la conversion et copie des donnees a convertir*/
  	cvt.len = taille_in;
  	cvt.buf = malloc(cvt.len * cvt.len_mult);
  	memcpy(cvt.buf, son_in, cvt.len);

  	/* Conversion */
  	if (SDL_ConvertAudio(&cvt) != 0) { printf("Erreur lors de la conversion du fichier audio: %s\n", SDL_GetError()); return 1; }

  	/* copie des données dans le son de sortie et liberation de la memoire utilisée par la conversion */
  	*son_out = realloc(*son_out,cvt.len_cvt);
  	memcpy(*son_out, cvt.buf, cvt.len_cvt);
  	free(cvt.buf);
  	*taille_out = cvt.len_cvt;
  	return 0;
}

int joue_son(unsigned char* son, int nb_samples, int frequence){
  	return affiche_joue_son(son,nb_samples,frequence,NULL,0);
}


/* Joue le son donné à la frequence passee en parametre 
	- unsigned char* son : les données sous forme d'un tableau de unsigned char
	- int nb_samples : la taille du son (en nombre d'échantillons)
	- int frequence : la frequence d'enchantillonnage du son

	renvoit 0 si succès
*/
int affiche_joue_son( unsigned char* son, int nb_samples, int frequence, SDL_Surface*f, int coul){

	/* on declare les specifications du son a jouer et joue au final*/
	SDL_AudioSpec input, output;
	
	setInternalAudioFormat(&input, frequence); 

  	/* la fonction qui sera appeler lors de la lecture du son */
  	input.callback = &mixaudio;

	return play_draw_sound(input, son, nb_samples,f,coul);
}


/* Joue le son a partir du fichier wav donné 
	- char* filename : le nom du fichier à jouer

	renvoit 0 si succès
*/
int joue_son_wav(char* filename){
	/* unsigned chargement du fichier .wav */
	SDL_AudioSpec input; 
	
  	if (SDL_LoadWAV(filename, &input, &sounddata, &soundlength) == NULL) {
    	printf("Erreur lors du unsigned chargement du fichier son: %s\n", SDL_GetError());
    	return 1;
  	}
	input.userdata = NULL;
  	/* la fonction qui sera appelee lors de la lecture du son */
  	input.callback = &mixaudio;	

	return play_sound(input, sounddata, (int) soundlength);	
}

int play_sound(SDL_AudioSpec input, void *son, int taille_son){
  return play_draw_sound(input,son,taille_son,NULL,0); 
}


/* joue le son en fonction des Spec passées en parametre 
	- SDL_AudioSpec input : le format du son à jouer
	- void *son : les données sous forme d'un tableau de unsigned char
	- int taille_son : la taille du son (en nombre d'échantillons)

	 renvoit 0 si succès
*/
int play_draw_sound(SDL_AudioSpec input, void *son, int taille_son, SDL_Surface* f, int coul){ SDL_AudioSpec output;
	
	/* init de SDL en mode audio */	
	if (SDL_Init(SDL_INIT_AUDIO) == -1) { printf("Erreur lors de l'initialisation de SDL!\n"); return 1; }

	/* ouverture du canal audio */ 
	if (SDL_OpenAudio(&input, &output) != 0) { printf("Erreur lors de l'ouverture du périphérique audio: %s\n", SDL_GetError()); return 1; } 

	/* convertion du format d'entree vers le format de sortie */ 
	convert_input_output(son, taille_son, input, &sounddata, &soundlength, output);

	/* mise a jour des variables gobales qui seront utilisees par la fonction de rappel*/
  	soundpos = 0;

	  /* On demarre la lecture (appel de la fonction rappel) */
  	SDL_PauseAudio(0);

  	/* On attend que la fonction ait fini la lecture */
  	while (soundpos < soundlength) { 
    		SDL_Delay(10);
		if (f!=NULL) CourbeTableau_char(f,son,taille_son,0,soundpos,0,255,coul);
  	}

   	/* On cesse d'appeler la fonction de rappel */
  	SDL_PauseAudio(1);

  	/* on ne laisse pas de salete en partant */
  	SDL_CloseAudio();
  	return 0;
}



/*    Lit un fichier son wav mono et remplit le tableau de unsigned char passe en parametre.
  - char* filename : le nom du fichier a jouer
  - int* freq : la frequence d'enchantillonnage du son
  - int* nb_samples : la taille du son (en nombre d'echantillons)

  renvoit NULL si echec, le tableau de son si succes
*/
unsigned char* get_son_wav_dyn(char* filename, int* freq, int* nb_samples){
  SDL_AudioSpec format_lu, format_interne;
  Uint8* donnees_converties = NULL;
  Uint32 taille_son;
  int i;
  unsigned char* son=NULL;

	/* unsigned chargement du fichier .wav */       
	if (SDL_LoadWAV(filename, &format_lu, &sounddata, &soundlength) == NULL) { printf("Erreur fichier son: %s\n", SDL_GetError()); return NULL; }

  	if (format_lu.channels>1){ printf("Erreur, seul le mono est pris en unsigned charge\n"); return NULL; }

	/* acquerir le format interne*/
	setInternalAudioFormat(&format_interne, format_lu.freq);

	/* convertion du format lu vers le format interne */ 
	convert_input_output(sounddata, soundlength, format_lu, &donnees_converties, &taille_son, format_interne);

	  /*on met a jour les variables */
	*freq =  format_interne.freq;
  	*nb_samples = taille_son;

  	/*on creer le son dans lequel on va stocker les donnees audio*/
  	son = (unsigned char*)calloc(*nb_samples,sizeof(*son));
  	for(i=0;i<*nb_samples;i++){ son[i] = (unsigned char) (donnees_converties[i]); } 

	/* on fait le menage*/
	free(donnees_converties);

  	return son;
} 


/*    Lit un fichier son wav mono et remplit le tableau de unsigned char passe en parametre.
  - char* filename : le nom du fichier a jouer
  - unsigned char * son : les donnees sous forme d'un tableau de unsigned char
  - int taille : taile du tableau précédent. Taille doit etre supérieure ou egale  au nombre d'echantillon du son à jouer
  - int* freq : la frequence d'enchantillonnage du son
  - int * nb_samples : la taille du son (en nombre d'echantillons)

  renvoit 0 si succes
*/
int get_son_wav_stat(char* filename, unsigned char* son, int taille, int* freq, int * nb_samples){
	SDL_AudioSpec format_lu, format_interne;
  	Uint8* donnees_converties = NULL;
  	Uint32 taille_son;
  	int i;

	/* unsigned chargement du fichier .wav */      
	if (SDL_LoadWAV(filename, &format_lu, &sounddata, &soundlength) == NULL) { printf("Erreur fichier son: %s\n", SDL_GetError()); return 1; }

     	if (taille * (format_lu.format&0x00FF) / 8 < soundlength)  { printf("Taille du tableau trop petit pour contenir ce son !!\n"); return 2; }

  	if (format_lu.channels>1){ printf("Erreur, seul le mono est pris en unsigned charge\n"); return 1; }

	/* acquerir le format interne*/
	setInternalAudioFormat(&format_interne, format_lu.freq);

	/* convertion du format lu vers le format interne */ 
	convert_input_output(sounddata, soundlength, format_lu, &donnees_converties, &taille_son, format_interne);

  /*on met a jour les variables */       
	*freq =  format_interne.freq;
  	*nb_samples = taille_son;

  	for(i=0;i<*nb_samples;i++){ son[i] = (unsigned char) (donnees_converties[i]); }

	/* on fait le menage*/
	free(donnees_converties);

  	return 0;
}

/*
	remplit le SDL_AudioSpec avec les options par defaut compatible avec le format du son utilise en interne
	- SDL_AudioSpec* format : le format a remplir
	- int frequence : la frequence d'enchantillonnage du son
*/
void setInternalAudioFormat(SDL_AudioSpec* format, int frequence){
	/* definition du format desire toujour un seul canal en unsigned char*/
  	format->freq = frequence;
  	format->samples = 512;
  	format->format = AUDIO_U8;
  	format->channels = 1;
  	format->userdata = NULL;
	format->silence = 0;
	format->size = 0;

}
