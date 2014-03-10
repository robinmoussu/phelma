#DIRSDL=/users/prog1a/C/librairie/2011
DIRSDL=/home/robin_arch/cour/1ere_annee_phelma/info/sdl_phelma/

CFLAGS=-g -c -O3 -I$(DIRSDL)/include -I$(DIRSDL) -D_GNU_SOURCE=1 -D_THREAD_SAFE -I/usr/X11/include -DHAVE_OPENGL
LDFLAGS= -L$(DIRSDL) -L$(DIRSDL)/lib -lSDLmain -lSDL -lSDL_draw -lSDL_ttf -lSDL_image -lSDL_draw -lSDL_phelma

run : demo5
	./demo5

all : exemple demo5

exemple:exemple.o file.o pile.o carte.o  distribution.o graph2_visu.o
	gcc -o $@  $^  $(LDFLAGS)

#demo5: demo5.o file.o pile.o carte.o  distribution.o graph2_visu.o
demo5: demo5.o distribution.o graph2_visu.o
	gcc -o $@  $^  $(LDFLAGS)

%.o:%.c carte.h
	gcc $(CFLAGS) $< -o $@ -D MODEGRAPHIQUE


clean:
	rm *.o 


