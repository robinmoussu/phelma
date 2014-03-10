CFLAGS=-g -O2 -Wall -Wextra
#CFLAGS=-g -O2 -std=c89 -ansi -Wall -Wextra -pedantic
LDFLAGS=
CIBLE=test_liste

all: test_liste test_liste2

run: $(CIBLE)
	./$(CIBLE)

clean:
	rm -f *.o $(CIBLE)

rebuild: clean all


test_liste2: test_liste2.o liste.o carte.o
	gcc  -o $@ $^ $(LDFLAGS)

test_liste: test_liste.o liste.o carte.o
	gcc  -o $@ $^ $(LDFLAGS)

%.o: %.c
	gcc -c $(CFLAGS) $<

