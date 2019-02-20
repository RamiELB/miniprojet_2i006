#include <stdio.h>
#include <stdlib.h>
#include "bibli.h"
#include "menu.h"

int main(int argc, char **argv){
    if (argc != 3){
        printf("Erreur format\n 2 arguments attendus : NomFichier NbLignes\n");
        return 0;
    }
    char *nom_fichier;
    nom_fichier = strdup(argv[1]);
    int nb_lignes = atoi(argv[2]);
    Biblio *B;
    initialise_biblio(&B);
    lecture_n_entree(nom_fichier, nb_lignes, B);
    while(1){
        affichage_menu();
        choix_menu(B);
    }
    free_livres(B->L);
    free(B);
    return 0;
}