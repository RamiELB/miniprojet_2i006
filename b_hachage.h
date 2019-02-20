#ifndef B_H_H
#define B_H_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entree_sortie.h"

typedef struct cell{
    int clef;
    int num;
    char *titre;
    char *auteur;
    struct cell *suiv;
} cell_t;

typedef struct{
    int nE; /*nombre d’elements contenus dans la table de hachage */
    int m ; /*taille de la table de hachage */
    int nb_collisions;
    cell_t ** T ; /*table de hachage avec resolution des collisions par chainage */
} tableHachage_t ;


tableHachage_t* initTableHachage(int m); //initialise une table de hachage de taille m

int fonctionClef(char *nom); //fonction définissant la clef d'un livre en fonction de l'auteur

int fonctionHachage(int clef, int m);

cell_t * creer_cell(int num, char*titre, char*auteur);

void insert_cell(tableHachage_t *th, cell_t *c);

void lecture_n_entree_hachage(char *nom_fichier, int nb_lignes, tableHachage_t *th);

cell_t *h_recherche_par_numero(tableHachage_t *th, int num);

cell_t *h_recherche_par_titre(tableHachage_t *th, char* titre);

void lire_case_table(tableHachage_t *th, int i);

void lire_table(tableHachage_t *th);

void afficher_cellule(cell_t* c);

cell_t *h_recherche_doublons(tableHachage_t *th);

cell_t *creer_cell_d(int num, char*titre, char*auteur, int clef); //fonction utile uniquement dans la recherche doublons

void h_recherche_par_auteur(tableHachage_t *th, char* auteur);

void h_supprimer_livre(tableHachage_t *th, int num);

#endif