#include "bibli.h"

void initialise_biblio(Biblio **b){
    *b = (Biblio *) malloc(sizeof(Biblio));
    (*b)->L = NULL;
    (*b)->nbliv=0;
}

void ajouter_livre(Biblio *b, s_livre *l){
    l->suiv = b->L;
    b->L = l;
    b->nbliv++;
}

s_livre *creer_livre(int num, char *titre, char *auteur){
    s_livre *l = (s_livre *) malloc(sizeof(s_livre));
    l->num = num;
    l->titre = strdup(titre);
    l->auteur = strdup(auteur);
    l->suiv = NULL;
    return l;
}

void lecture_n_entree(char *nom_fichier, int nb_lignes, Biblio *b){
    FILE *f = fopen(nom_fichier,"r");
    int i;
    int num;
    char titre[50];
    char auteur[50];
    s_livre * l;
    for(i=0; i<nb_lignes; i++){
        num = GetEntier(f);
        GetChaine(f,50,titre);
        GetChaine(f,50,auteur);
        if(strlen(titre) == 0){
            //fin du fichier
            break;
        }
        l = creer_livre(num,titre,auteur);
        ajouter_livre(b,l);
        SkipLine(f);
    }
    fclose(f);
}

void afficher_livre(s_livre *l){
    printf("Livre numéro %d, Titre : %s, Auteur : %s\n", l->num, l->titre, l->auteur);
}

s_livre *recherche_par_numero(int n, Biblio *b, int appel_exp){ 
    /*l'argument appel sert à n'afficher que le livre n'est pas disponible uniquement si la fonction
      est appelée explicitement depuis le menu */
    s_livre *l = b->L;
    while(l != NULL && l->num != n){
        l = l->suiv;
    }
    if(l!=NULL){
        afficher_livre(l);
    }else if(appel_exp){
        printf("Il n'y a pas de livre numéro %d\n", n);
    }
    return l;
}

s_livre *recherche_par_titre(char *titre, Biblio *b){
    s_livre *l = b->L;
    while(l != NULL && strcmp(titre,l->titre) != 0){
        l = l->suiv;
    }
    if(l!=NULL){
        afficher_livre(l);
    }else{
        printf("Il n'y a pas de livre titré %s\n", titre);
    }
    return l;
}

void recherche_auteur(char *auteur, Biblio *b){
    s_livre *l = b->L;
    int nb_livres = 0;
    while(l != NULL){
        if(strcmp(auteur, l->auteur) == 0){
            nb_livres++;
            afficher_livre(l);
        }
        l = l->suiv;
    }
    switch(nb_livres){
        case 0:
            printf("Pas de livre de %s\n", auteur);
            break;
        case 1:
            printf("Un seul livre de %s\n", auteur);
            break;
        default:
            printf("%d livres de %s\n",nb_livres, auteur);
    }
}

void supprimer_livre(int num, Biblio *b){
    s_livre *l = b->L;
    s_livre *prec = NULL;
    while(l != NULL && l->num != num){
        prec = l;
        l = l->suiv;
    }

    //supression en tête de liste
    if(prec == NULL){
        b->L = l->suiv;
        afficher_livre(l);
        free(l);
        printf("Suppresion effectuée avec succès!\n");
    }else if(l == NULL){
        printf("Ce numéro ne correspond à aucun livre dans la bibliothèque");
    }else{
        prec->suiv = l->suiv;
        afficher_livre(l);
        free(l);
        printf("Suppresion effectuée avec succès!\n");
    }
}

s_livre *recherche_doublons(Biblio *b){
    s_livre *cpt1;
    s_livre *cpt2;
    s_livre *liste = malloc(sizeof(s_livre));
    liste->suiv = NULL;
    liste->num = -1; //pour identifier la première insertion
    s_livre *buffer = NULL;
    int cpt_doublons = 0;

    for(cpt1=b->L; cpt1 != NULL; cpt1=cpt1->suiv){
        for(cpt2=cpt1->suiv; cpt2 != NULL; cpt2 = cpt2->suiv){
            //printf("Comparaisons des livres %d et %d\n", cpt1->num, cpt2->num);
            if((strcmp(cpt1->titre,cpt2->titre) == 0) && (strcmp(cpt1->auteur,cpt2->auteur) == 0)){
                if(liste->num == -1){ //première insertion
                    *liste = *cpt1;
                }else{
                buffer = creer_livre(cpt1->num, cpt1->titre, cpt1->auteur);
                buffer->suiv = liste;
                liste = buffer;
                }
                cpt_doublons++;
                break;
            }
        }
    }
    printf("Il y a %d doublons (un livre présent 3 fois est considéré comme 2 doublons)\n", cpt_doublons);
    return liste;
}