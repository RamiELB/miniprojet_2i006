#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include <stdlib.h>
#include "bibli.h"

void affichage_menu(); //afficher le menu

void choix_menu(Biblio *b); //lis le choix du menu et fait appel aux fonctions correspondantes

void afficher_liste_livres(s_livre *liste); //affiche tous les livres d'une liste chainee

void clear_buffer(); //permet de ne pas avoir de bug, à utiliser apres un scanf

void ajout_livre_utilisateur(Biblio *b); //fonction permettant à l'utilisateur d'ajouter un livre

#endif