#DIRSDL=/users/prog1a/C/librairie/2011
#DIRSDL=/home/robin_arch/cour/1ere\ année\ phelma/info/sdl_phelma
DIRSDL=/usr

SRC=image.c  SDL_audio_manip.c  SDL_courbes.c  SDL_phelma.c  SDL_tab.c
OBJ=$(SRC:.c=.o)


CFLAGS=-I.  -I$(DIRSDL)/include -I$(DIRSDL)/include/SDL

libSDL_phelma: $(OBJ)
	ar rv  $@.a $(OBJ)
	mv $@.a $(DIRSDL)/lib
	cp *.h  $(DIRSDL)/include
	rm *.o

%.o: %.c
	$(CC) -c $< $(CFLAGS)


