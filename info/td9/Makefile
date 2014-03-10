CFLAGS=-g -O2 -std=c89 -ansi -Wall -Wextra -pedantic
LDFLAGS= -lm
CIBLE=tri

all: $(CIBLE)

run: all
	./$(CIBLE)

clean:
	rm -f *.o $(CIBLE)

rebuild: clean all

$(CIBLE): $(CIBLE).o
	gcc -o $(CIBLE) $(CIBLE).o $(LDFLAGS)

%.o: %.c
	gcc -c $(CFLAGS) $<


