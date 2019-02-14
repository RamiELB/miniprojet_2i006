#ifndef _bibli_h
#define _bibli_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entree_sortie.h"

typedef struct livre {
    int num ;
    char * titre ;
    char * auteur ;
    struct livre * suiv ;
} s_livre ;

typedef struct {
    s_livre * L ; /*Liste chainee des livres */
    int nbliv ; /* Nombre de livres dans la liste */
} Biblio ;

void initialise_biblio(Biblio *b);
void ajouter_livre(Biblio *b, s_livre *l);
s_livre *creer_livre(int num, char *titre, char *auteur);
void lecture_n_entree(char *nom_fichier, int nb_lignes, Biblio *b);

void afficher_livre(s_livre *l);

s_livre *recherche_par_numero(int n, Biblio *b, int appel);
s_livre *recherche_par_titre(char *titre, Biblio *b);
void recherche_auteur(char *auteur, Biblio *b);

void supprimer_livre(int num, Biblio *b);
s_livre *recherche_doublons(Biblio *b);
#endif