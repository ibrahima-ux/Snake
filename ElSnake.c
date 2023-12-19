#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define TAILLEMAX 100
#define CYCLE 100000L
#define SEC 1000000L

typedef struct {
    int nbX, nbY, tailleCase;
} InfoJeux;

typedef enum {
    DROITE, GAUCHE, HAUT, BAS
} Direction;

typedef struct {
    int x, y, sprites;
    Direction dir;
} Position;

typedef struct {
    Position position[TAILLEMAX];
    int longueur;
} Snake;

typedef struct {
    Position position[5];
    int spriteNb[5];
    int nbPomme;
} Apple;

Snake snake;
Apple apple;
Direction direction;
InfoJeux infos;
int timerGame =0;


void genererNourriture(int z) {
    int test = 0;
    apple.position[z].x = (rand() % infos.nbX) * infos.tailleCase;
    apple.position[z].y = (rand() % infos.nbY) * infos.tailleCase;
}

void deplacersnake() {
    for (int i = snake.longueur - 1; i > 0; --i) {
        snake.position[i] = snake.position[i - 1];
    }

    switch (direction) {
        case DROITE:
            snake.position[0].x += infos.tailleCase;
        break;
        case GAUCHE:
            snake.position[0].x -= infos.tailleCase;
        break;
        case HAUT:
            snake.position[0].y -= infos.tailleCase;
        break;
        case BAS:
            snake.position[0].y += infos.tailleCase;
        break;
    }
}

void afficher(){
    for (int i = 0; i < apple.nbPomme; i++){
        LibererSprite(apple.spriteNb[i]);
    }
    /*for (int i = 0; i < snake.longueur; i++){
        LibererSprite(snake.position[i].sprites);
    }*/
    EffacerEcran(CouleurParComposante(0, 0, 0));

    srand(time(NULL));
    for (int i = 0; i < apple.nbPomme; i++){
        if (apple.position[i].x == -1 && apple.position[i].y == -1) {
            genererNourriture(i);
        }
    }

    int taillePlateauX = infos.nbX*infos.tailleCase;
    int taillePlateauY = infos.nbY*infos.tailleCase;
    int tailleFenetreX = taillePlateauX+150;
    int tailleFenetreY = taillePlateauY;

    ChoisirCouleurDessin(CouleurParComposante(40, 40, 40));
    RemplirRectangle(0, 0, tailleFenetreX, tailleFenetreY);
    ChoisirCouleurDessin(CouleurParComposante(20, 255, 20));
    RemplirRectangle(0, 0, taillePlateauX, taillePlateauY);

    /*ChoisirCouleurDessin(CouleurParComposante(255, 0, 0));
    RemplirRectangle(apple.position[0].x, apple.position[0].y, tailleCase, tailleCase);
    RemplirRectangle(apple.position[1].x, apple.position[1].y, tailleCase, tailleCase);
    RemplirRectangle(apple.position[2].x, apple.position[2].y, tailleCase, tailleCase);
    RemplirRectangle(apple.position[3].x, apple.position[3].y, tailleCase, tailleCase);
    RemplirRectangle(apple.position[4].x, apple.position[4].y, tailleCase, tailleCase);*/

    for (int i = 0; i < apple.nbPomme; i++){
        apple.spriteNb[i] = ChargerSprite("apple.png");
    }
    for (int i = 0; i < apple.nbPomme; i++){
        AfficherSprite(apple.spriteNb[i], apple.position[i].x, apple.position[i].y);
    }

    ChoisirCouleurDessin(CouleurParComposante(70, 70, 70));
    for (int i = 0; i < snake.longueur; i++) {
        RemplirRectangle(snake.position[i].x, snake.position[i].y, infos.tailleCase, infos.tailleCase);
    }

    /*switch (snake.position[0].dir){
        case GAUCHE:
            snake.position[0].sprites=ChargerSprite("snakeHeadG.png");
        break;
        case DROITE:
            snake.position[0].sprites=ChargerSprite("snakeHeadD.png");
        break;
        case HAUT:
            snake.position[0].sprites=ChargerSprite("snakeHeadH.png");
        break;
        case BAS:
            snake.position[0].sprites=ChargerSprite("snakeHeadB.png");
        break;
    }
    AfficherSprite(snake.position[0].sprites, snake.position[0].x, snake.position[0].y);
    for (int i = 0; i < snake.longueur-1; i++){    
        switch (snake.position[i].dir){
            case GAUCHE:
                snake.position[i].sprites=ChargerSprite("snakeBodyLine.png");
            break;
            case DROITE:
                snake.position[i].sprites=ChargerSprite("snakeBodyLine.png");
            break;
            case HAUT:
                snake.position[i].sprites=ChargerSprite("snakeBody.png");
            break;
            case BAS:
                snake.position[i].sprites=ChargerSprite("snakeBody.png");
            break;
        }
        AfficherSprite(snake.position[i].sprites, snake.position[i].x, snake.position[i].y);
    }
    switch (snake.position[snake.longueur-1].dir){
        case GAUCHE:
            snake.position[snake.longueur-1].sprites=ChargerSprite("snakeTailD.png");
        break;
        case DROITE:
            snake.position[snake.longueur-1].sprites=ChargerSprite("snakeTailG.png");
        break;
        case HAUT:
            snake.position[snake.longueur-1].sprites=ChargerSprite("snakeTailH.png");
        break;
        case BAS:
            snake.position[snake.longueur-1].sprites=ChargerSprite("snakeTailB.png");
        break;
    }
    AfficherSprite(snake.position[snake.longueur-1].sprites, snake.position[snake.longueur-1].x, snake.position[snake.longueur-1].y);
*/
    int minute = timerGame/60;
    int seconde = timerGame%60;
    char timeT[10];
    char *numM;
    char *numS;
    asprintf(&numM, "%d", minute);
    asprintf(&numS, "%d", seconde);
    strcat(timeT, numM);
    strcat(timeT, ":");
    strcat(timeT, numS);
    int xtimer=taillePlateauX  + ((tailleFenetreX-taillePlateauX-TailleChaineEcran(minute+":"+seconde, 2))/2);
    int ytimer=25;
    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    EcrireTexte(taillePlateauX+60, ytimer, timeT, 2);
}

void gameOver(int score) {
    FermerGraphique();
    printf("Game Over! avec un score de %d\n", score);
    exit(0);
}

int checkDeplacement() {
    if (snake.position[0].x < 0 || snake.position[0].x >= infos.nbX*infos.tailleCase ||
        snake.position[0].y < 0 || snake.position[0].y >= infos.nbY*infos.tailleCase) {
        return 1;
    }

    for (int i = 1; i < snake.longueur; i++) {
        if (snake.position[0].x == snake.position[i].x && snake.position[0].y == snake.position[i].y) {
            return 1;
        }
    }

    return 0;
}

int playCycle(){
    unsigned long suivant, timer;
    suivant = Microsecondes()+CYCLE;
    timer = Microsecondes()+SEC;
    int score=0, timerGame=0;
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

        if (Microsecondes()>suivant){
            suivant= Microsecondes()+CYCLE;
            deplacersnake(direction, snake, infos);
            if (checkDeplacement(snake, infos)) {
                gameOver(score);
            }

            for (int i = 0; i < apple.nbPomme; i++){
                if (snake.position[0].x == apple.position[i].x && snake.position[0].y == apple.position[i].y) {
                    snake.longueur++;
                    score+=10;
                    apple.position[i].x = apple.position[i].y = -1;
                }
            }

            afficher(snake, apple, infos, timerGame);
        }

        if (Microsecondes()>timer){
            timer = Microsecondes()+SEC;
            timerGame++;
            afficher(snake, apple, infos, timerGame);
        }
    }

    return score;
}

int main(void) {
    InitialiserGraphique();
    int tailleCase;
    int vitesse;
    int score = 0;
    int help=1;
    apple.nbPomme=5;

    infos.tailleCase = 20;
    infos.nbY = 40, infos.nbX = 60;
    int taillePlateauX = infos.nbX*tailleCase;
    int taillePlateauY = infos.nbY*tailleCase;
    int tailleFenetreX = taillePlateauX+150;
    int tailleFenetreY = taillePlateauY;
    for (int i = 0; i < apple.nbPomme; i++){
        apple.position[i].x = -1;
        apple.position[i].y = -1;
    }

    if (!CreerFenetre(150, 150, tailleFenetreX, tailleFenetreY)) {
        fprintf(stderr, "Erreur creation de feunetre\n");
        exit(1);
    }

    ChoisirTitreFenetre("Snake By Me");

    snake.longueur = 10;
    snake.position[0].x = taillePlateauX / 2;
    snake.position[0].y = taillePlateauY / 2;
    for (int i = 1; i < snake.longueur; i++){
        snake.position[i].x = snake.position[i-1].x + tailleCase;
        snake.position[i].y = snake.position[0].y;
    }

    direction = GAUCHE;
    afficher();

    playCycle();

    return EXIT_SUCCESS;
}