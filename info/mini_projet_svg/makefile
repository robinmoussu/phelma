DIRSDL=/users/prog1a/C/librairie/2011

CFLAGS=-g -O2 -I$(DIRSDL)/include -std=c89 -ansi -Wall -Wextra -pedantic
LDFLAGS=$(LFLMAC) -g -L$(DIRSDL)/lib -L/usr/local/lib -lSDLmain -lSDL -lSDL_ttf -lSDL_image -lSDL_draw -lSDL_phelma

demo1: demo1.o inpaint.o
	gcc -o $@ $^ $(LDFLAGS)

%.o : %.c 
	gcc -c $(CFLAGS) $< 

clean :
	rm *.o demo1

