CFLAGS=-g -Wall -lm

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

h_main: h_main.c b_hachage.o entree_sortie.o
	gcc -c $(CFLAGS) h_main.c
	gcc -o h_main $(CFLAGS) h_main.o b_hachage.o entree_sortie.o

clean:
	rm -rf *.o biblimain h_main
