#DIRSDL=/users/prog1a/C/librairie/2011
DIRSDL=/home/robin_arch/cour/1ere_annee_phelma/info/sdl_phelma/

CFLAGS=-g -c -O2 -Wall -Wextra
LDFLAGS= 
CIBLE=test

run : ${CIBLE}
	./${CIBLE}

all : hash

test: hash.o test.o
	gcc -o $@  $^  $(LDFLAGS)
#./test

hash: divers.o liste.o main.o hash.o
	gcc -o $@  $^  $(LDFLAGS)

%.o:%.c
	gcc $(CFLAGS) $< -o $@

clean:
	rm *.o hash test


