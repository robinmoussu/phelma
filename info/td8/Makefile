#DIRSDL=/users/prog1a/C/librairie/2011
DIRSDL=/home/robin_arch/cour/1ere\ année\ phelma/info/sdl_phelma
CFLAGS=-g -O2 -I$(DIRSDL)/include/SDL -I$(DIRSDL)/include -std=c89 -ansi -Wall -Wextra -pedantic
LDFLAGS=-L$(DIRSDL)/lib -lSDLmain -lSDL -lSDL_ttf -lSDL_image -lSDL_phelma -lSDL_draw

all: koch1

run: all
	./koch1

clean: 
	rm -f *.o koch1

rebuild: clean all

koch1: koch1.o
	gcc -o koch1 koch1.o  $(LDFLAGS)

%.o: %.c
	gcc -c $(CFLAGS) $< 


