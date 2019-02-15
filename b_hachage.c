#include "b_hachage.h"


tableHachage_t* initTableHachage(int m){
    tableHachage_t * th = malloc(sizeof(tableHachage_t));
    th->T = malloc(m * sizeof(cell_t*));
    th->nE = 0;
    int i;
    for(i=0;i<m;i++){
        th->T[i] = NULL;
    }
    return th;
}

int fonctionClef(char *nom){
    int i = 0;
    int clef = 0;
    while(nom[i] != '\0'){
        clef += nom[i];
        i++;
    }
    return clef;
}

cell_t *creer_cell(int num, char*titre, char*auteur){
    cell_t *c = (cell_t *) malloc(sizeof(cell_t));
    c->num = num;
    c->titre = strdup(titre);
    c->auteur = strdup(auteur);
    c->clef = fonctionClef(auteur);
    c->suiv = NULL;
    return c;
}

int fonctionHachage(int clef, int m){
    double c = (double) clef;
    double A = (sqrt(5) - 1.0) / 2.0;
    c *= A;
    int res = (int) floor(m*(c-floor(c)));
    return res;
}

void insert_cell(tableHachage_t *th, cell_t *c){
    int i = fonctionHachage(c->clef, th->m);
    c->suiv = th->T[i];
    th->T[i] = c;
}

void lecture_n_entree_hachage(char *nom_fichier, int nb_lignes, tableHachage_t *th){
    FILE *f = fopen(nom_fichier,"r");
    int i;
    int num;
    char titre[50];
    char auteur[50];
    cell_t *c;
    for(i=0; i<nb_lignes; i++){
        num = GetEntier(f);
        GetChaine(f,50,titre);
        GetChaine(f,50,auteur);
        c = creer_cell(num,titre,auteur);
        insert_cell(th,c);
        SkipLine(f);
    }
    fclose(f);
}