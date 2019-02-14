#include "menu.h"
#include "bibli.h"

void affichage_menu(){
    printf("\nQue voulez-vous faire?\n");
    printf("1. Chercher un livre par son numéro\n");
    printf("2. Chercher un livre par son titre\n");
    printf("3. Chercher tous les livres d'un auteur\n");
    printf("4. Ajouter un nouveau livre\n");
    printf("5. Supprimer un livre\n");
    printf("6. Chercher les livres présents au moins en double\n\n");
    printf("0. Sortir\n\n");

}

void choix_menu(Biblio *b){
    char choix = getchar();
    char lecture[126];
    switch(choix){
        case '1':
            printf("Entrez le numéro du livre à rechercher : ");
            scanf("%s", lecture);
            int numero = atoi(lecture);
            recherche_par_numero(numero, b,1);
            break;
        case '2':
            printf("Entrez le titre du livre à rechercher : ");
            scanf("%s", lecture);
            recherche_par_titre(lecture, b);
            break;
        case '3':
            printf("Entrez le nom de l'auteur : ");
            scanf("%s", lecture);
            recherche_auteur(lecture, b);
            break;
        case '4':
            ajout_livre_utilisateur(b);
            break;
        case '5':
            printf("Entrez le numéro du livre à rechercher : ");
            scanf("%s", lecture);
            int numero2 = atoi(lecture);
            supprimer_livre(numero2, b);
            break;
        case '6': ; //ce ; sert à enlever une erreur de compilation
            s_livre *liste = recherche_doublons(b);
            afficher_liste_livres(liste);
            break;
        case '0':
            exit(0);
        default:
            printf("Merci d'entrer un choix correct !\n");
            affichage_menu();
    }
    clear_buffer();
}

void afficher_liste_livres(s_livre *liste){
    s_livre *l;
    for(l=liste; l!=NULL; l=l->suiv){
        afficher_livre(l);
    }
}

void clear_buffer(){    
  while (getchar() != '\n');
}

void ajout_livre_utilisateur(Biblio *b){
    char titre[126];
    char auteur[126];
    char c_num[50];
    int numero = 0;
    
    while(numero == 0){
        printf("Quel est le numéro du livre à ajouter? (merci d'entrer un numero disponible et différent de 0\n");
        scanf("%s", c_num);
        clear_buffer();
        numero = atoi(c_num);
        s_livre *l = recherche_par_numero(numero, b,0);
        if (l != NULL){
            printf("Ce numéro n'est pas disponible malheuresement pas disponible\\nn");
            numero = 0;
        }
    }


    printf("Quel est le titre du livre à ajouter?\n");
    scanf("%s", titre);
    clear_buffer();


    printf("Qui est l'auteur du livre à ajouter?\n");
    scanf("%s", auteur);

    s_livre *l = creer_livre(numero, titre, auteur);
    ajouter_livre(b, l);
}