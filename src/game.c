#include "header.h"

void mouvement_joueur(char plateau[10][10], int *joueur_x, int *joueur_y, int *box_x, int *box_y) {
    char direction;

    printf("Entrez une direction (Z = Haut, S = Bas, Q = Gauche, D = Droite) : ");
    scanf(" %c", &direction);

    switch (direction) {
        case 'Z':
        case 'z':
            if (plateau[*joueur_x - 1][*joueur_y] == 'X') {
                deplacement_box_haut(plateau, box_x, box_y, joueur_x, joueur_y);
            } else {
                deplacement_joueur_haut(plateau, joueur_x, joueur_y);
            }
            break;
        case 'S':
        case 's':
            if (plateau[*joueur_x + 1][*joueur_y] == 'X') {
                deplacement_box_bas(plateau, box_x, box_y, joueur_x, joueur_y);
            } else {
                deplacement_joueur_bas(plateau, joueur_x, joueur_y);
            }
            break;
        case 'Q':
        case 'q':
            if (plateau[*joueur_x][*joueur_y - 1] == 'X') {
                deplacement_box_gauche(plateau, box_x, box_y, joueur_x, joueur_y);
            } else {
                deplacement_joueur_gauche(plateau, joueur_x, joueur_y);
            }
            break;
        case 'D':
        case 'd':
            if (plateau[*joueur_x][*joueur_y + 1] == 'X') {
                deplacement_box_droite(plateau, box_x, box_y, joueur_x, joueur_y);
            } else {
                deplacement_joueur_droite(plateau, joueur_x, joueur_y);
            }
            break;
        default:
            printf("Direction invalide, veuillez entrer Z, S, Q ou D.\n");
            break;
    }
}


void deplacement_joueur_gauche(char plateau[10][10], int *joueur_x, int *joueur_y)
{
    if (plateau[*joueur_x][*joueur_y - 1] == '#') {
        printf("Vous avez touché un mur ! Vous avez perdu.\n");
        exit(0);
    }
    if(plateau[*joueur_x][*joueur_y - 1] != '#' && (plateau[*joueur_x][*joueur_y - 1] == ' ' || plateau[*joueur_x][*joueur_y - 1] == '.'))
    {
        plateau[*joueur_x][*joueur_y] = ' ';
        (*joueur_y)--;
        plateau[*joueur_x][*joueur_y] = 'O';
    }
}

void deplacement_joueur_droite(char plateau[10][10], int *joueur_x, int *joueur_y)
{   
    if (plateau[*joueur_x][*joueur_y + 1] == '#') {
        printf("Vous avez touché un mur ! Vous avez perdu.\n");
        exit(0);
    }
    if (plateau[*joueur_x][*joueur_y + 1] != '#' && (plateau[*joueur_x][*joueur_y + 1] == ' ' || plateau[*joueur_x][*joueur_y + 1] == '.'))
    {
        plateau[*joueur_x][*joueur_y] = ' ';
        (*joueur_y)++;
        plateau[*joueur_x][*joueur_y] = 'O';
    }
}

void deplacement_joueur_haut(char plateau[10][10], int *joueur_x, int *joueur_y)
{
    if (plateau[*joueur_x - 1][*joueur_y] == '#') {
        printf("Vous avez touché un mur ! Vous avez perdu.\n");
        exit(0);
    }
    if (plateau[*joueur_x - 1][*joueur_y] != '#' && (plateau[*joueur_x - 1][*joueur_y] == ' ' || plateau[*joueur_x - 1][*joueur_y] == '.'))
    {
        plateau[*joueur_x][*joueur_y] = ' ';
        (*joueur_x)--;
        plateau[*joueur_x][*joueur_y] = 'O';
    }
}

void deplacement_joueur_bas(char plateau[10][10], int *joueur_x, int *joueur_y)
{ 
    if (plateau[*joueur_x + 1][*joueur_y] == '#') {
        printf("Vous avez touché un mur ! Vous avez perdu.\n");
        exit(0);
    }  
    if (plateau[*joueur_x + 1][*joueur_y] != '#' && (plateau[*joueur_x + 1][*joueur_y] == ' ' || plateau[*joueur_x + 1][*joueur_y] == '.')) 
    {
        plateau[*joueur_x][*joueur_y] = ' '; 
        (*joueur_x)++;                               
        plateau[*joueur_x][*joueur_y] = 'O'; 
    }
}

void deplacement_box_bas(char plateau[10][10], int *box_x, int *box_y, int *joueur_x, int *joueur_y)
{
    if (plateau[*box_x + 1][*box_y] == '#') {
        printf("Vous avez touché un mur ! Vous avez perdu.\n");
        exit(0);
    }
    if (plateau[*box_x + 1][*box_y] != '#' && (plateau[*box_x + 1][*box_y] == ' ' || plateau[*box_x + 1][*box_y] == '.')) 
    {
        plateau[*box_x][*box_y] = ' ';
        (*box_x)++;
        plateau[*box_x][*box_y] = 'X';
        plateau[*joueur_x][*joueur_y] = ' ';
        (*joueur_x)++;
        plateau[*joueur_x][*joueur_y] = 'O';
    }else
    {
        printf("Mouvement Impossible\n");
    } 
}

void deplacement_box_haut(char plateau[10][10], int *box_x, int *box_y, int *joueur_x, int *joueur_y)
{
    if (plateau[*box_x - 1][*box_y] == '#') {
        printf("Vous avez touché un mur ! Vous avez perdu.\n");
        exit(0);
    }
    if (plateau[*box_x - 1][*box_y] != '#' && (plateau[*box_x - 1][*box_y] == ' ' || plateau[*box_x - 1][*box_y] == '.')) 
    {   
        plateau[*box_x][*box_y] = ' ';
        (*box_x)--;
        plateau[*box_x][*box_y] = 'X';
        plateau[*joueur_x][*joueur_y] = ' ';
        (*joueur_x)--;
        plateau[*joueur_x][*joueur_y] = 'O';
    }else
    {
        printf("Mouvement Impossible\n");
    }
}

void deplacement_box_gauche(char plateau[10][10], int *box_x, int *box_y, int *joueur_x, int *joueur_y)
{
    if (plateau[*box_x][*box_y - 1] == '#') {
        printf("Vous avez touché un mur ! Vous avez perdu.\n");
        exit(0);
    }
     if (plateau[*box_x][*box_y - 1] != '#' && (plateau[*box_x][*box_y - 1] == ' ' || plateau[*box_x][*box_y - 1] == '.')) 
     {
        plateau[*box_x][*box_y] = ' '; 
        (*box_y)--;
        plateau[*box_x][*box_y] = 'X';
        plateau[*joueur_x][*joueur_y] = ' ';
        (*joueur_y)--;
        plateau[*joueur_x][*joueur_y] = 'O';
    }else
    {
        printf("Mouvement Impossible\n");
    } 
}

void deplacement_box_droite(char plateau[10][10], int *box_x, int *box_y, int *joueur_x, int *joueur_y)
{
    if (plateau[*box_x][*box_y - 1] == '#') {
        printf("Vous avez touché un mur ! Vous avez perdu.\n");
        exit(0);
    }
    if (plateau[*box_x][*box_y + 1] != '#' && (plateau[*box_x][*box_y + 1] == ' ' || plateau[*box_x][*box_y + 1] == '.')) 
    {
        plateau[*box_x][*box_y] = ' ';
        (*box_y)++;
        plateau[*box_x][*box_y] = 'X';
        plateau[*joueur_x][*joueur_y] = ' ';
        (*joueur_y)++;
        plateau[*joueur_x][*joueur_y] = 'O';
    }else
    {
        printf("Mouvement Impossible\n");
    } 
}

int condition_victoire(char plateau[10][10], int *box_x, int *box_y, int *objectif_x, int *objectif_y) 
{
    if (plateau[*box_x][*box_y] == plateau[*objectif_x][*objectif_y]) {
        printf("Bravo ! Vous avez gagné, la boîte est sur l'objectif.\n");
        return 1; 
    }
    return 0; 
}

void afficher_plateau(char plateau[10][10]) 
{
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c ", plateau[i][j]);
        }
        printf("\n");
    }
}

const char *choix_niveau(const char *liste_niveau[], int nombre_niveau)
{
    int choix;
    printf("Choisissez un niveau (0-%d) : ", nombre_niveau - 1);
    scanf("%d", &choix);
    if (choix < 0 || choix >= nombre_niveau) {
        printf("Choix invalide, retour au niveau par défaut.\n");
        choix = 0;
    }
    return liste_niveau[choix];
}