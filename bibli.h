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


void initialise_biblio(Biblio *b); //initialise correctement les champs de la structure à des valeures nulles ou équivalentes

void ajouter_livre(Biblio *b, s_livre *l);  //ajouter d'un livre dans une bibliothèque

s_livre *creer_livre(int num, char *titre, char *auteur); //créée et renvoie un livre

void lecture_n_entree(char *nom_fichier, int nb_lignes, Biblio *b); //lis n lignes dans un fichier, créée les livres et les ajoutes dans la bibliothèque

void afficher_livre(s_livre *l); //affiche un livre

s_livre *recherche_par_numero(int n, Biblio *b, int appel); //recherche d'un livre par son numéro
/*l'argument appel sert à n'afficher que le livre n'est pas disponible uniquement si la fonction
      est appelée explicitement depuis le menu */

s_livre *recherche_par_titre(char *titre, Biblio *b); //recherche d'un livre par son titre

void recherche_auteur(char *auteur, Biblio *b); //recherche tous les livres d'un auteur et les affiches

void supprimer_livre(int num, Biblio *b); //supression d'un livre dans une bibliothèque par son numéro

s_livre *recherche_doublons(Biblio *b); // renvoie une lise chainee de tous les livres présents au moins en double

#endif