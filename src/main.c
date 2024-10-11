#include "header.h"

void afficher_niveau(const char *nom_fichier, char plateau[10][10],  int *joueur_x, int *joueur_y, int *box_x, int *box_y, int *objectif_x, int *objectif_y) {
    FILE *Niveau = fopen(nom_fichier, "r");
    if (Niveau == NULL) {
        printf("Erreur : Impossible de lire le fichier du niveau.\n");
        exit(1);
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
           plateau[i][j] = fgetc(Niveau);
            if (plateau[i][j] == '\n')
            {
                plateau[i][j] = ' ';
                j--;
            }
            if (plateau[i][j] == 'O') {
                *joueur_x = i;
                *joueur_y = j;
            } else if (plateau[i][j] == 'X') {
                *box_x = i;
                *box_y = j;
            }else if (plateau[i][j] == '.')
            {
                *objectif_x = i;
                *objectif_y = j;
            }
        }
        fgetc(Niveau);
    }

    fclose(Niveau);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c", plateau[i][j]);
        }
        printf("\n");
    }
}

void afficher_position(int *joueur_x, int *joueur_y, int box_x, int box_y) {
    printf("Joueur : %d %d\n", *joueur_x, *joueur_y);
    printf("Boite  : %d %d\n", box_x, box_y);
}

int main(){
    char plateau[10][10];
    int joueur_x = 0, joueur_y = 0;
    int box_x = 0, box_y = 0;
    int objectif_x = 0, objectif_y = 0;

    const char *liste_niveau[] = {
        "Niveau/niveau_1.txt",
        "Niveau/niveau_2.txt",
        "Niveau/niveau_3.txt",
        "Niveau/niveau_4.txt",
        "Niveau/niveau_5.txt"
    }; 

    int nombre_niveau = sizeof(liste_niveau) / sizeof(liste_niveau[0]);

    const char *niveau_choisi = choix_niveau(liste_niveau, nombre_niveau);
    printf("Vous avez choisi : %s\n", niveau_choisi);
    
    afficher_niveau(niveau_choisi, plateau, &joueur_x, &joueur_y, &box_x, &box_y, &objectif_x, &objectif_y);

    int victoire = 0;
     while (!victoire) {
        afficher_position(&joueur_x, &joueur_y, box_x, box_y);

        mouvement_joueur(plateau, &joueur_x, &joueur_y, &box_x, &box_y);

        afficher_plateau(plateau);

        victoire = condition_victoire(plateau, &box_x, &box_y, &objectif_x, &objectif_y); 
    }
    return 0;
}