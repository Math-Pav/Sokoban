#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <stdlib.h>

const char *choix_niveau(const char *liste_niveau[], int nombre_niveau);
void mouvement_joueur(char plateau[10][10], int *joueur_x, int *joueur_y, int *box_x, int *box_y);
void afficher_niveau(const char *nom_fichier, char plateau[10][10], int *joueur_x, int *joueur_y, int *box_x, int *box_y, int *objectif_x, int *objectif_y);
void afficher_plateau(char plateau[10][10]);
int condition_victoire(char plateau[10][10], int *box_x, int *box_y,  int *objectif_x, int *objectif_y);
void deplacement_box_haut(char plateau[10][10], int *box_x, int *box_y, int *joueur_x, int *joueur_y);
void deplacement_joueur_haut(char plateau[10][10], int *joueur_x, int *joueur_y);
void deplacement_box_bas(char plateau[10][10], int *box_x, int *box_y, int *joueur_x, int *joueur_y);
void deplacement_joueur_bas(char plateau[10][10], int *joueur_x, int *joueur_y);
void deplacement_box_gauche(char plateau[10][10], int *box_x, int *box_y, int *joueur_x, int *joueur_y);
void deplacement_box_droite(char plateau[10][10], int *box_x, int *box_y, int *joueur_x, int *joueur_y);
void deplacement_joueur_gauche(char plateau[10][10], int *joueur_x, int *joueur_y);
void deplacement_joueur_droite(char plateau[10][10], int *joueur_x, int *joueur_y);

#endif