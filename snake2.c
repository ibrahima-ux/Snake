#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TAILLEMAX 100

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position position[5];
    int longueur;
} Snake;

typedef struct {
    Position position[5];
} Apple;

typedef enum {
    DROITE, GAUCHE, HAUT, BAS
} Direction;

int nbY = 40, nbX = 60;
int tailleFenetreX, tailleFenetreY, taillePlateauX, taillePlateauY;
int tailleCase;
Snake snake;
Apple apple;
Direction direction;
int vitesse;
int score = 0;
int help = 1;
int nbPomme = 5;

void initialiser() {
    int i;
    InitialiserGraphique();
    tailleCase = 20;
    taillePlateauX = nbX * tailleCase;
    taillePlateauY = nbY * tailleCase;
    tailleFenetreX = taillePlateauX + 150;
    tailleFenetreY = taillePlateauY;
    for (i = 0; i < nbPomme; i++) {
        apple.position[i].x = -1;
        apple.position[i].y = -1;
    }

    vitesse = 100000;

    if (!CreerFenetre(50, 50, tailleFenetreX, tailleFenetreY)) {
        fprintf(stderr, "Erreur creation de fenetre\n");
        exit(1);
    }

    ChoisirTitreFenetre("Snake By Me");

    snake.longueur = 10;
    snake.position[0].x = taillePlateauX / 2;
    snake.position[0].y = taillePlateauY / 2;

    direction = DROITE;
}

void genererNourriture(int z) {
    int test = 0;
    /*if (apple.position[z].x == -1 && apple.position[z].y == -1) {/
        srand(time(NULL));
        /*do {*/
        apple.position[z].x = (rand() % nbX) * tailleCase;
        apple.position[z].y = (rand() % nbY) * tailleCase;
        /*test = 0;
        for (int i = 0; i < nbPomme; i++) {
            if (i != z) {
                if (apple.position[z].x != apple.position[i].x || apple.position[z].y != apple.position[i].y) {
                    test++;
                }
            }
        }
        } while (test != nbPomme - 1);*/
        /*}*/
}

void deplacersnake() {
    int i;
    for (i = snake.longueur - 1; i > 0; --i) {
        snake.position[i] = snake.position[i - 1];
    }

    switch (direction) {
    case DROITE:
        snake.position[0].x += tailleCase;
        break;
    case GAUCHE:
        snake.position[0].x -= tailleCase;
        break;
    case HAUT:
        snake.position[0].y -= tailleCase;
        break;
    case BAS:
        snake.position[0].y += tailleCase;
        break;
    }
}

void afficher() {
    int i;
    EffacerEcran(CouleurParComposante(0, 0, 0));

    for (i = 0; i < nbPomme; i++) {
        if (apple.position[i].x == -1 && apple.position[i].y == -1) {
            genererNourriture(i);
        }
    }

    ChoisirCouleurDessin(CouleurParComposante(40, 40, 40));
    RemplirRectangle(0, 0, tailleFenetreX, tailleFenetreY);
    ChoisirCouleurDessin(CouleurParComposante(20, 255, 20));
    RemplirRectangle(0, 0, taillePlateauX, taillePlateauY);

    ChoisirCouleurDessin(CouleurParComposante(255, 0, 0));
    for (i = 0; i < nbPomme; i++) {
        RemplirRectangle(apple.position[i].x, apple.position[i].y, tailleCase, tailleCase);
    }

    ChoisirCouleurDessin(CouleurParComposante(255, 255, 0)); 
    for (i = 1; i < snake.longueur; i++) {
        DessinerSegment(snake.position[i - 1].x + tailleCase / 2, snake.position[i - 1].y + tailleCase / 2,
                        snake.position[i].x + tailleCase / 2, snake.position[i].y + tailleCase / 2);
    }

    AfficherFenetre();
}

void gameOver() {
    FermerGraphique();
    printf("Game Over! avec un score de %d\n", score);
    exit(0);
}

int checkDeplacement() {
    int i;
    if (snake.position[0].x < 0 || snake.position[0].x >= taillePlateauX ||
        snake.position[0].y < 0 || snake.position[0].y >= taillePlateauY) {
        return 1;
    }

    for (i = 1; i < snake.longueur; i++) {
        if (snake.position[0].x == snake.position[i].x && snake.position[0].y == snake.position[i].y) {
            return 1;
        }
    }

    return 0;
}

void jouer() {
    KeySym touche;
    while (1) {
        if (ToucheEnAttente()) {
            touche = Touche();
            switch (touche) {
            case XK_Right:
                if (direction != GAUCHE) {
                    direction = DROITE;
                }
                break;
            case XK_Left:
                if (direction != DROITE) {
                    direction = GAUCHE;
                }
                break;
            case XK_Up:
                if (direction != BAS) {
                    direction = HAUT;
                }
                break;
            case XK_Down:
                if (direction != HAUT) {
                    direction = BAS;
                }
                break;
            }
        }

        deplacersnake();
        if (checkDeplacement()) {
            gameOver();
        }
        int i;
        for (i = 0; i < nbPomme; i++) {
            if (snake.position[0].x == apple.position[i].x && snake.position[0].y == apple.position[i].y) {
                snake.longueur++;
                score += 20;
                apple.position[i].x = apple.position[i].y = -1;
            }
        }

        afficher();
        usleep(vitesse);
    }
}

int main(void) {
    initialiser();
    jouer();

    return EXIT_SUCCESS;
}


#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TAILLEMAX 100
#define CYCLE 10000L
#define SEC 10000L

// ... Vos structures, variables et fonctions existantes

void afficher() {
    // ... Votre code existant pour l'affichage du jeu

    // Affichage du minuteur
    int minute = timerGame / 60;
    int seconde = timerGame % 60;
    int xtimer = taillePlateauX + ((tailleFenetreX - taillePlateauX - TailleChaineEcran("00:00", 2)) / 2);
    int ytimer = 25;

    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    EcrireTexte(xtimer, ytimer, "Timer:", 2);
    EcrireTexte(xtimer, ytimer + 20, minute + ":" + seconde, 2);
    AfficherFenetre();
}

void jouer() {
    unsigned long suivantCycle = Microsecondes() + CYCLE;
    unsigned long suivantTimer = Microsecondes() + SEC;

    while (1) {
        if (ToucheEnAttente()) {
            KeySym touche = Touche();
            switch (touche) {
                // Votre code pour la gestion des touches
            }
        }

        if (Microsecondes() > suivantCycle) {
            suivantCycle = Microsecondes() + CYCLE;

            // Votre code pour le déplacement du serpent, la gestion des collisions, etc.
            deplacersnake();
            if (checkDeplacement()) {
                gameOver();
            }

            for (int i = 0; i < nbPomme; i++) {
                if (snake.position[0].x == apple.position[i].x && snake.position[0].y == apple.position[i].y) {
                    snake.longueur++;
                    score += 10;
                    apple.position[i].x = apple.position[i].y = -1;
                }
            }
        }

        if (Microsecondes() > suivantTimer) {
            suivantTimer = Microsecondes() + SEC;
            timerGame++;
            afficher(); // Mise à jour de l'affichage du minuteur à chaque seconde
        }

        afficher(); // Affichage du jeu à chaque itération de la boucle principale
    }
}

int main(void) {
    initialiser();
    jouer();

    return EXIT_SUCCESS;
}
