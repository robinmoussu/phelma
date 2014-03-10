DIRSDL=/users/prog1a/C/librairie/2011

CFLAGS=-g -O2 -I$(DIRSDL)/include 
LDFLAGS=$(LFLMAC) -g -L$(DIRSDL)/lib -L/usr/local/lib -lSDLmain -lSDL -lSDL_ttf -lSDL_image -lSDL_draw -lSDL_phelma

demo1: demo1.o 
	gcc -o demo1 demo1.o $(LDFLAGS)

demo1.o : demo1.c
	gcc -c $(CFLAGS)  demo1.c

