#ifndef MENU_H
#define MENU_H
#include <stdio.h>
#include <stdlib.h>
#include "bibli.h"

void affichage_menu();
void choix_menu(Biblio *b);
void afficher_liste_livres(s_livre *liste);
void clear_buffer();
void ajout_livre_utilisateur(Biblio *b);

#endif