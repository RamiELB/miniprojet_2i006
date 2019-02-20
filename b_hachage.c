#include "b_hachage.h"


tableHachage_t* initTableHachage(int m){
    tableHachage_t * th = malloc(sizeof(tableHachage_t));
    th->T = malloc(m * sizeof(cell_t*));
    th->nE = 0;
    th->m = m;
    th->nb_collisions = 0;
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
    if(th->T[i] != NULL){
        th->nb_collisions = th->nb_collisions+1;
    }
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
        if(strlen(titre) == 0){
            //fin du fichier
            break;
        }
        c = creer_cell(num,titre,auteur);
        insert_cell(th,c);
        SkipLine(f);
    }
    fclose(f);
}

cell_t *h_recherche_par_numero(tableHachage_t *th, int num){
    int i;
    cell_t *c;
    for(i=0;i<th->m;i++){
        c = th->T[i];
        while(c != NULL){
            if(c->num == num){
                afficher_cellule(c);
                return c;
            }
            c = c->suiv;
        }
    }
    printf("Il n'y a pas de livre numéro %d\n", num);
    return NULL;
}

cell_t *h_recherche_par_titre(tableHachage_t *th, char* titre){
    int i;
    cell_t *c;
    for(i=0;i<th->m;i++){
        c = th->T[i];
        while(c != NULL){
            if(strcmp(c->titre,titre) == 0){
                afficher_cellule(c);
                return c;
            }
            c = c->suiv;
        }
    }
    printf("Il n'y a pas de livre titré %s\n", titre);
    return NULL;
}

void h_recherche_par_auteur(tableHachage_t *th, char* auteur){
    int position = fonctionHachage(fonctionClef(auteur),th->m);
    cell_t *c = th->T[position];
    while(c != NULL){
        if(strcmp(c->auteur, auteur) == 0){
            afficher_cellule(c);
        }
        c=c->suiv;
    }
}

void h_supprimer_livre(tableHachage_t *th, int num){
    int m = th->m;
    int i;
    cell_t *c;
    cell_t *prec;
    for(i=0;i<m;i++){
        c = th->T[i];
        prec = NULL;
        while(c != NULL){
            if(c->num == num){
                if(prec == NULL){ //suppression en tête
                    th->T[i] = c->suiv;
                }else{
                    prec->suiv = c->suiv;
                }
                free(c);
                i=m+1;
            }
            prec = c;
            c = c->suiv;
        }
    }
    if(i == m){
        printf("Il n'y a pas de livre numéro %d\n", num);
    }
}

void afficher_cellule(cell_t* c){
    printf("Livre numéro %d, Titre : %s, Auteur : %s\n", c->num, c->titre, c->auteur);
}

void lire_case_table(tableHachage_t *th, int i){
    printf("\n\n----- CASE %d -----\n", i);
    cell_t *c = th->T[i];
    while(c){
        afficher_cellule(c);
        c=c->suiv;
    }
}

void lire_table(tableHachage_t *th){
    int i;
    for(i=0;i<th->m;i++){
        lire_case_table(th, i);
    }
}

cell_t *h_recherche_doublons(tableHachage_t *th){
    cell_t *cpt1;
    cell_t *cpt2;
    cell_t *liste = malloc(sizeof(cell_t));
    liste->num = -1; //pour identifier la première insertion
    liste->suiv = NULL;
    cell_t *buffer = NULL;
    int cpt_doublons = 0;
    int i;
    for(i=0;i<th->m;i++){
        for(cpt1=th->T[i]; cpt1 != NULL; cpt1=cpt1->suiv){
            for(cpt2=cpt1->suiv; cpt2 != NULL; cpt2 = cpt2->suiv){
                if(strcmp(cpt1->titre,cpt2->titre) == 0 && strcmp(cpt1->auteur,cpt2->auteur) == 0){
                    if(liste->num == -1){ //première insertion
                        *liste = *cpt1;
                        liste->suiv = NULL;
                    }else{
                    buffer = creer_cell_d(cpt1->num, cpt1->titre, cpt1->auteur, cpt1->clef);
                    buffer->suiv = liste;
                    liste = buffer;
                    }
                    cpt_doublons++;
                    break;
                }
            }
        }
    }
    printf("Il y a %d doublons (un livre présent 3 fois est considéré comme 2 doublons)\n", cpt_doublons);
    return liste;
}

cell_t *creer_cell_d(int num, char*titre, char*auteur, int clef){
    /* presque identique à creer_cell, mais ne fait pas appel à la fonction de hachage puisque l'on a déjà la clef*/
    cell_t *c = (cell_t *) malloc(sizeof(cell_t));
    c->num = num;
    c->titre = strdup(titre);
    c->auteur = strdup(auteur);
    c->clef = clef;
    c->suiv = NULL;
    return c;
}