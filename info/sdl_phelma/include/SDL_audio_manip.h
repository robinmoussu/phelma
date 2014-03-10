#ifndef _SDL_audio_manip
#define _SDL_audio_manip

int joue_son(unsigned char* son, int nb_samples, int frequence);
int affiche_joue_son(unsigned char* son, int nb_samples, int frequence,SDL_Surface* f,int coul);

int joue_son_wav(char* filename);

int play_sound(SDL_AudioSpec input, void *son, int taille);
int play_draw_sound(SDL_AudioSpec input, void *son, int taille,SDL_Surface* f,int coul);

void mixaudio(void* userdata, Uint8 * stream, int len);

int convert_input_output(void* son_in, int taille_in, SDL_AudioSpec input, Uint8** son_out, Uint32* taille_out, SDL_AudioSpec output);

int get_son_wav_stat(char* filename, unsigned char * son, int taille, int* freq, int * nb_samples);

unsigned char* get_son_wav_dyn(char* filename, int* freq, int * nb_samples);

void setInternalAudioFormat(SDL_AudioSpec* input, int frequence);

#endif
