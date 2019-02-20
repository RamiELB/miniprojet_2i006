#include "b_hachage.h"

int main(int argc, char **argv){
    if (argc != 3){
        printf("Erreur format\n 2 arguments attendus : NomFichier NbLignes TailleTableHachage\n");
        return 0;
    }
    char *nom_fichier;
    nom_fichier = strdup(argv[1]);
    int nb_lignes = atoi(argv[2]);
    int tailleTableHachage;
    if (nb_lignes < 1000){
        tailleTableHachage = nb_lignes;
    }else{
        tailleTableHachage = 1000 + ((nb_lignes-1000) / 10);
    }
    tableHachage_t *th = initTableHachage(tailleTableHachage);
    lecture_n_entree_hachage(nom_fichier, nb_lignes, th);
    h_recherche_doublons(th);
    //printf("Nombre de collisions : %d avec m = %d et %d ouvrages\n", th->nb_collisions, th->m, nb_lignes);
}