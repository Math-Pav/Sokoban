#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SPRITE_SIZE 16  
#define PLATEAU_LARGEUR 10
#define PLATEAU_HAUTEUR 10

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *spriteSheet = NULL;

void init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n'a pas pu s'initialiser ! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("Sokoban", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, PLATEAU_LARGEUR * SPRITE_SIZE, PLATEAU_HAUTEUR * SPRITE_SIZE, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("La fenêtre n'a pas pu être créée ! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Le renderer n'a pas pu être créé ! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    IMG_Init(IMG_INIT_PNG);
    SDL_Surface *spriteSurface = IMG_Load("sprites.png");
    if (!spriteSurface) {
        printf("Erreur de chargement de l'image des sprites : %s\n", SDL_GetError());
        exit(1);
    }

    spriteSheet = SDL_CreateTextureFromSurface(renderer, spriteSurface);
    SDL_FreeSurface(spriteSurface);
}

void close_SDL() {
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void render_tile(int x, int y, int tileType) {
    SDL_Rect srcRect = { tileType * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE };
    SDL_Rect destRect = { x * SPRITE_SIZE, y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE };
    SDL_RenderCopy(renderer, spriteSheet, &srcRect, &destRect);
}

void afficher_plateau_SDL(char plateau[PLATEAU_HAUTEUR][PLATEAU_LARGEUR]) {
    SDL_RenderClear(renderer);
    
    for (int i = 0; i < PLATEAU_HAUTEUR; i++) {
        for (int j = 0; j < PLATEAU_LARGEUR; j++) {
            char element = plateau[i][j];
            int spriteIndex = 0;  
            switch (element) {
                case '#':
                    spriteIndex = 0; 
                    break;
                case ' ':
                    spriteIndex = 1; 
                    break;
                case '.':
                    spriteIndex = 2; 
                    break;
                case 'X':
                    spriteIndex = 3; 
                    break;
                case 'O':
                    spriteIndex = 4; 
                    break;
            }
            render_tile(j, i, spriteIndex);
        }
    }
    
    SDL_RenderPresent(renderer);
}

int peut_deplacer(char plateau[PLATEAU_HAUTEUR][PLATEAU_LARGEUR], int joueur_x, int joueur_y, int dx, int dy) {
    int nouvelle_x = joueur_x + dx;
    int nouvelle_y = joueur_y + dy;

    if (plateau[nouvelle_y][nouvelle_x] == '#') return 0;  

    if (plateau[nouvelle_y][nouvelle_x] == 'X') {
        int box_nouvelle_x = nouvelle_x + dx; 
        int box_nouvelle_y = nouvelle_y + dy;

        if (plateau[box_nouvelle_y][box_nouvelle_x] == ' ' || plateau[box_nouvelle_y][box_nouvelle_x] == '.') {
            return 1;  
        } else {
            return 0;  
        }
    }

    return 1;  
}

void deplacer_joueur(char plateau[PLATEAU_HAUTEUR][PLATEAU_LARGEUR], int *joueur_x, int *joueur_y, int dx, int dy, int *box_x, int *box_y) {
    if (peut_deplacer(plateau, *joueur_x, *joueur_y, dx, dy)) {
        plateau[*joueur_y][*joueur_x] = ' ';  
        *joueur_x += dx;  
        *joueur_y += dy;

        // Si le joueur pousse une boîte
        if (plateau[*joueur_y][*joueur_x] == 'X') {
            plateau[*box_y][*box_x] = ' ';  
            *box_x += dx;  
            *box_y += dy;
            plateau[*box_y][*box_x] = 'X';  
        }

        plateau[*joueur_y][*joueur_x] = 'O';  
        printf("Position du joueur : (%d, %d)\n", *joueur_x, *joueur_y); // Afficher la position du joueur
    }
}

int condition_victoire(int box_x, int box_y, int objectif_x, int objectif_y) {
    return (box_x == objectif_x && box_y == objectif_y);
}

const char *choix_niveau(const char *liste_niveau[], int nombre_niveau) {
    int choix;
    printf("Choisissez un niveau (0-%d) : ", nombre_niveau - 1);
    scanf("%d", &choix);
    if (choix < 0 || choix >= nombre_niveau) {
        printf("Choix invalide, retour au niveau par défaut.\n");
        choix = 0;
    }
    return liste_niveau[choix];
}

void afficher_niveau(const char *nom_fichier, char plateau[PLATEAU_HAUTEUR][PLATEAU_LARGEUR], int *joueur_x, int *joueur_y, int *box_x, int *box_y, int *objectif_x, int *objectif_y) {
    FILE *Niveau = fopen(nom_fichier, "r");
    if (Niveau == NULL) {
        printf("Erreur : Impossible de lire le fichier du niveau.\n");
        exit(1);
    }

    for (int i = 0; i < PLATEAU_HAUTEUR; i++) {
        for (int j = 0; j < PLATEAU_LARGEUR; j++) {
            plateau[i][j] = fgetc(Niveau);
            if (plateau[i][j] == '\n') {
                plateau[i][j] = ' ';
                j--;
            }
            if (plateau[i][j] == 'O') {
                *joueur_x = j;
                *joueur_y = i; 
            } else if (plateau[i][j] == 'X') {
                *box_x = j; 
                *box_y = i; 
            } else if (plateau[i][j] == '.') {
                *objectif_x = j;
                *objectif_y = i; 
            }
        }
        fgetc(Niveau);
    }

    fclose(Niveau);

    for (int i = 0; i < PLATEAU_HAUTEUR; i++) {
        for (int j = 0; j < PLATEAU_LARGEUR; j++) {
            printf("%c", plateau[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char* args[]) {
    char plateau[PLATEAU_HAUTEUR][PLATEAU_LARGEUR];

    int joueur_x, joueur_y, box_x, box_y, objectif_x, objectif_y;

    const char *liste_niveau[] = {
        "Niveau/niveau_0.txt",
        "Niveau/niveau_1.txt",
        "Niveau/niveau_2.txt",
        "Niveau/niveau_3.txt",
        "Niveau/niveau_4.txt"
    }; 

    int nombre_niveau = sizeof(liste_niveau) / sizeof(liste_niveau[0]);

    const char *niveau_choisi = choix_niveau(liste_niveau, nombre_niveau);
    printf("Vous avez choisi : %s\n", niveau_choisi);
    
    afficher_niveau(niveau_choisi, plateau, &joueur_x, &joueur_y, &box_x, &box_y, &objectif_x, &objectif_y);

    init_SDL();
    afficher_plateau_SDL(plateau);
    
    int quit = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        deplacer_joueur(plateau, &joueur_x, &joueur_y, 0, -1, &box_x, &box_y);
                        break;
                    case SDLK_DOWN:
                        deplacer_joueur(plateau, &joueur_x, &joueur_y, 0, 1, &box_x, &box_y);
                        break;
                    case SDLK_LEFT:
                        deplacer_joueur(plateau, &joueur_x, &joueur_y, -1, 0, &box_x, &box_y);
                        break;
                    case SDLK_RIGHT:
                        deplacer_joueur(plateau, &joueur_x, &joueur_y, 1, 0, &box_x, &box_y);
                        break;
                }
                afficher_plateau_SDL(plateau);
            }
        }
        SDL_Delay(100); 

        if (condition_victoire(box_x, box_y, objectif_x, objectif_y)) {
            printf("Vous avez gagné !\n");
            quit = 1;  
        }
    }

    close_SDL();
    return 0;
}












