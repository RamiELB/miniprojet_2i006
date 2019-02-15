#ifndef B_H_H
#define B_H_H
#include "menu.h"
#include <math.h>

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
    cell_t ** T ; /*table de hachage avec resolution des collisions par chainage */
} tableHachage_t ;


tableHachage_t* initTableHachage(int m); //initialise une table de hachage de taille m

int fonctionClef(char *nom); //fonction définissant la clef d'un livre en fonction de l'auteur

int fonctionHachage(int clef, int m);

cell_t * creer_cell(int num, char*titre, char*auteur);

void insert_cell(tableHachage_t *th, cell_t *c);

void lecture_n_entree_hachage(char *nom_fichier, int nb_lignes, tableHachage_t *th);

#endif