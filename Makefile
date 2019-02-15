CFLAGS=-g -Wall

all: biblimain

biblimain: biblimain.c bibli.o entree_sortie.o menu.o
	gcc -c $(CFLAGS) biblimain.c
	gcc -o biblimain $(CFLAGS) entree_sortie.o bibli.o menu.o biblimain.o

bibli.o: bibli.c
	gcc -c $(CFLAGS) bibli.c

entree_sortie.o: entree_sortie.c
	gcc -c $(CFLAGS) entree_sortie.c

menu.o : menu.c
	gcc -c $(CFLAGS) menu.c

b_hachage.o : b_hachage.c
	gcc -c $(CFLAGS) b_hachage.c

clean:
	rm -rf *.o biblimain