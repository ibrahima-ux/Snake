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
    Position position[TAILLEMAX];
    int longueur;
} Snake;

typedef enum {
    DROITE, GAUCHE, HAUT, BAS
} Direction;


int nbY = 40, nbX = 60;
int tailleFenetreX, tailleFenetreY, taillePlateauX, taillePlateauY;
int tailleCase;
Snake snake;
Direction direction;
int nourritureX, nourritureY;
int vitesse;
int score = 0;
int help=1;

void initialiser() {
    InitialiserGraphique();
    tailleCase = 20;
    taillePlateauX = nbX*tailleCase;
    taillePlateauY = nbY*tailleCase;
    tailleFenetreX = taillePlateauX+150;
    tailleFenetreY = taillePlateauY;
    nourritureX = nourritureY = -1;
    vitesse = 100000;


    if (!CreerFenetre(50, 50, tailleFenetreX, tailleFenetreY)) {
        fprintf(stderr, "Erreur creation de feunetre\n");
        exit(1);
    }

    ChoisirTitreFenetre("Snake By Me");

    snake.longueur = 10;
    snake.position[0].x = taillePlateauX / 2 - snake.longueur/2;
    snake.position[0].y = taillePlateauY / 2;

    direction = DROITE;
}

void genererNourriture() {
    srand(time(NULL));

    nourritureX = (rand() % (taillePlateauX / tailleCase)) * tailleCase;
    nourritureY = (rand() % (taillePlateauY / tailleCase)) * tailleCase;
}

void deplacersnake() {
    for (int i = snake.longueur - 1; i > 0; --i) {
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
    EffacerEcran(CouleurParComposante(0, 0, 0));

    if (nourritureX == -1 && nourritureY == -1) {
        genererNourriture();
    }

    ChoisirCouleurDessin(CouleurParComposante(40, 40, 40));
    RemplirRectangle(0, 0, tailleFenetreX, tailleFenetreY);
    ChoisirCouleurDessin(CouleurParComposante(20, 255, 20));
    RemplirRectangle(0, 0, taillePlateauX, taillePlateauY);

    AfficherSprite(ChargerSprite("apple.png"), nourritureX, nourritureY);

    ChoisirCouleurDessin(CouleurParComposante(70, 70, 70));
    for (int i = 0; i < snake.longueur; ++i) {
        RemplirRectangle(snake.position[i].x, snake.position[i].y, tailleCase, tailleCase);
    }

    AfficherFenetre();
}

void gameOver() {
    FermerGraphique();
    printf("Game Over! avec un score de %d\n", score);
    exit(0);
}

int checkDeplacement() {
    if (snake.position[0].x < 0 || snake.position[0].x >= taillePlateauX ||
        snake.position[0].y < 0 || snake.position[0].y >= taillePlateauY) {
        return 1;
    }

    for (int i = 1; i < snake.longueur; ++i) {
        if (snake.position[0].x == snake.position[i].x && snake.position[0].y == snake.position[i].y) {
            return 1;
        }
    }

    return 0;
}

void jouer() {
    while (1) {
        if (ToucheEnAttente()) {
            KeySym touche = Touche();
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

        if (snake.position[0].x == nourritureX && snake.position[0].y == nourritureY) {
            snake.longueur+=2;
            score+=20;
            nourritureX = nourritureY = -1;
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