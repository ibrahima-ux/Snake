#include "snake.h"

Jeux initialiser(){
    InfoJeux infos;
    Jeux game;
    Apple apples;
    Direction direction;
    Snake serpent;
    int i;

    InitialiserGraphique();
    infos.nbX=60;
    infos.nbY=40;
    infos.tailleCase=20;

    if (!CreerFenetre(50, 50, infos.nbX*infos.tailleCase + 20 * 2, infos.nbY*infos.tailleCase + 100 + 20*3)) {
        fprintf(stderr, "Erreur creation de feunetre\n");
        exit(1);
    }
    ChoisirTitreFenetre("Snake By Me");

    serpent.longueur=10;
    serpent.position[0].x = infos.nbX*infos.tailleCase / 2 + 20;
    serpent.position[0].y = infos.nbY*infos.tailleCase / 2 + 20;
    for (i = 1; i < serpent.longueur; i++){
        serpent.position[i].x = serpent.position[i-1].x+infos.tailleCase;
        serpent.position[i].y = serpent.position[0].y;
    }

    direction = GAUCHE;

    apples.nbPomme=5;
    for (i = 0; i < apples.nbPomme; i++){
        apples.position[i].x = -1;
        apples.position[i].y = -1;
    }
    
    game.apple=apples;
    game.direction=direction;
    game.infos=infos;
    game.snake=serpent;

    return game;
}

Snake deplacersnake(InfoJeux infos, Snake snake, Direction direction) {
    int i;
    Snake newSnake;
    newSnake=snake;
    newSnake.posLast.x=newSnake.position[newSnake.longueur - 1].x;
    newSnake.posLast.y=newSnake.position[newSnake.longueur - 1].y;
    for (i = snake.longueur - 1; i > 0; --i) {
        newSnake.position[i] = newSnake.position[i - 1];
    }

    switch (direction) {
        case DROITE:
            newSnake.position[0].x += infos.tailleCase;
        break;
        case GAUCHE:
            newSnake.position[0].x -= infos.tailleCase;
        break;
        case HAUT:
            newSnake.position[0].y -= infos.tailleCase;
        break;
        case BAS:
            newSnake.position[0].y += infos.tailleCase;
        break;
    }
    return newSnake;
}

void initialiserSnake(InfoJeux infos, Snake snake, Apple apple, Direction direction){
    int taillePlateauX = infos.nbX*infos.tailleCase;
    int taillePlateauY = infos.nbY*infos.tailleCase;
    int tailleFenetreX = taillePlateauX+20*2;
    int tailleFenetreY = taillePlateauY+100+20*3;
    int i;
    ChoisirCouleurDessin(CouleurParComposante(45, 45, 45));
    RemplirRectangle(0, 0, tailleFenetreX, tailleFenetreY);
    ChoisirCouleurDessin(CouleurParComposante(24, 140, 24));
    RemplirRectangle(20, 20, taillePlateauX, taillePlateauY);

    /*Serpent*/
    ChoisirCouleurDessin(CouleurParComposante(70, 70, 70));
    for (i = 0; i < snake.longueur; i++) {
        RemplirRectangle(snake.position[i].x, snake.position[i].y, infos.tailleCase, infos.tailleCase);
    }

    ChargerImage("infos-bar.png", 20, 20+taillePlateauY+20, 0, 0, taillePlateauX, 100);

    AfficherFenetre();
}

int checkDeplacement(InfoJeux infos, Snake snake) {
    int i;
    if (snake.position[0].x < 20 || snake.position[0].x >= infos.nbX*infos.tailleCase+20*2 ||
        snake.position[0].y < 20 || snake.position[0].y >= infos.nbY*infos.tailleCase+20) {
        return 1;
    }

    for (i = 1; i < snake.longueur; i++) {
        if (snake.position[0].x == snake.position[i].x && snake.position[0].y == snake.position[i].y) {
            return 1;
        }
    }

    return 0;
}

void majSnake(InfoJeux infos, Snake snake, Apple apple, Direction direction){
    /*Snake*/
    ChoisirCouleurDessin(CouleurParComposante(24, 140, 24));
    RemplirRectangle(snake.posLast.x, snake.posLast.y, infos.tailleCase, infos.tailleCase);
    ChoisirCouleurDessin(CouleurParComposante(70, 70, 70));
    RemplirRectangle(snake.position[0].x, snake.position[0].y, infos.tailleCase, infos.tailleCase);
}

void majText(InfoJeux infos, Snake snake, Apple apple, Direction direction){
    int taillePlateauX = infos.nbX*infos.tailleCase;
    int taillePlateauY = infos.nbY*infos.tailleCase;
    int tailleFenetreX = taillePlateauX+20*2;
    int tailleFenetreY = taillePlateauY+100+20*3;
    int minute = infos.timerGame/60;
    int seconde = infos.timerGame%60;
    char timeT[10]="";
    char *numM="";
    char *numS="";
    char* lvl="";
    char* scores="";
    int xtimer, ytimer;

    /*Cut*/
    ChoisirCouleurDessin(CouleurParComposante(45, 45, 45));
    RemplirRectangle(20, 20+taillePlateauY+20+50, taillePlateauX, 50);

    /*Reecriture*/
    asprintf(&numM, "%02d", minute);
    asprintf(&numS, "%02d", seconde);
    strcat(timeT, numM);
    strcat(timeT, ":");
    strcat(timeT, numS);

    asprintf(&lvl, "%03d", snake.longueur-9);
    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    xtimer=tailleFenetreX/4*1 - TailleChaineEcran(lvl, 2)/2;
    ytimer=20+taillePlateauY+20+65;
    EcrireTexte(xtimer, ytimer, lvl, 2);

    asprintf(&scores, "%d", infos.score);
    xtimer=tailleFenetreX/4*2 - TailleChaineEcran(scores, 2)/2;
    EcrireTexte(xtimer, ytimer, scores, 2);

    xtimer=taillePlateauX/4*3 + (TailleChaineEcran(timeT, 2)/2);
    EcrireTexte(xtimer, ytimer, timeT, 2);
}

void gameOver(int score){
    int millier, centaine, dixaine, unite;
    int scoreX, scoreY;
    int millierS, centaineS, dixaineS, uniteS;
    EffacerEcran(CouleurParComposante(45, 45, 45));
    
    AfficherSprite(ChargerSprite("gameOver.png"), 20, 20);
    millier = (score/1000)%10;
    centaine = (score/100)%10;
    dixaine = (score/10)%10;
    unite = score%10;
    switch (millier){
        case 0:millierS=ChargerSprite("0.png"); break;
        case 1:millierS=ChargerSprite("1.png"); break;
        case 2:millierS=ChargerSprite("2.png"); break;
        case 3:millierS=ChargerSprite("3.png"); break;
        case 4:millierS=ChargerSprite("4.png"); break;
        case 5:millierS=ChargerSprite("5.png"); break;
        case 6:millierS=ChargerSprite("6.png"); break;
        case 7:millierS=ChargerSprite("7.png"); break;
        case 8:millierS=ChargerSprite("8.png"); break;
        case 9:millierS=ChargerSprite("9.png"); break;
    }
    switch (centaine){
        case 0:centaineS=ChargerSprite("0.png"); break;
        case 1:centaineS=ChargerSprite("1.png"); break;
        case 2:centaineS=ChargerSprite("2.png"); break;
        case 3:centaineS=ChargerSprite("3.png"); break;
        case 4:centaineS=ChargerSprite("4.png"); break;
        case 5:centaineS=ChargerSprite("5.png"); break;
        case 6:centaineS=ChargerSprite("6.png"); break;
        case 7:centaineS=ChargerSprite("7.png"); break;
        case 8:centaineS=ChargerSprite("8.png"); break;
        case 9:centaineS=ChargerSprite("9.png"); break;
    }
    switch (dixaine){
        case 0:dixaineS=ChargerSprite("0.png"); break;
        case 1:dixaineS=ChargerSprite("1.png"); break;
        case 2:dixaineS=ChargerSprite("2.png"); break;
        case 3:dixaineS=ChargerSprite("3.png"); break;
        case 4:dixaineS=ChargerSprite("4.png"); break;
        case 5:dixaineS=ChargerSprite("5.png"); break;
        case 6:dixaineS=ChargerSprite("6.png"); break;
        case 7:dixaineS=ChargerSprite("7.png"); break;
        case 8:dixaineS=ChargerSprite("8.png"); break;
        case 9:dixaineS=ChargerSprite("9.png"); break;
    }
    switch (unite){
        case 0:uniteS=ChargerSprite("0.png"); break;
        case 1:uniteS=ChargerSprite("1.png"); break;
        case 2:uniteS=ChargerSprite("2.png"); break;
        case 3:uniteS=ChargerSprite("3.png"); break;
        case 4:uniteS=ChargerSprite("4.png"); break;
        case 5:uniteS=ChargerSprite("5.png"); break;
        case 6:uniteS=ChargerSprite("6.png"); break;
        case 7:uniteS=ChargerSprite("7.png"); break;
        case 8:uniteS=ChargerSprite("8.png"); break;
        case 9:uniteS=ChargerSprite("9.png"); break;
    }

    scoreX = 1240/2 - 40;
    scoreY = 960/2 + 20;
    AfficherSprite(millierS, scoreX, scoreY);
    scoreX+=20;
    AfficherSprite(centaineS, scoreX, scoreY);
    scoreX+=20;
    AfficherSprite(dixaineS, scoreX, scoreY);
    scoreX+=20;
    AfficherSprite(uniteS, scoreX, scoreY);
}

int gameStart(InfoJeux infos, Snake snake, Apple apple, Direction direction){
    unsigned long suivant, timer;
    int test=1;
    suivant = Microsecondes()+CYCLE;
    timer = Microsecondes()+SEC;
    infos.score=0;
    infos.timerGame=0;
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
                case XK_Escape:
                    return infos.score;
                break;
                case XK_space:
                    test=0;
                break;
            }
        }

        if (test==0){
            while (1){
                if (ToucheEnAttente()){
                    KeySym touches = Touche();
                    switch (touches) {
                        case XK_space:
                            break;
                        break;
                    }
                }
            }
        }
        if (Microsecondes()>suivant){
            int i;
            suivant= Microsecondes()+CYCLE;
            snake=deplacersnake(infos, snake, direction);
            for (i = 0; i < apple.nbPomme; i++){
                if (snake.position[0].x == apple.position[i].x && snake.position[0].y == apple.position[i].y) {
                    apple.position[i].x = -1;
                    apple.position[i].y = -1;

                    if (apple.position[i].types=BASIC){
                        snake.longueur+=2;
                        infos.score+=5;
                    }else if(apple.position[i].types=LARGE){
                        snake.longueur+=5;
                        infos.score+=5;
                    }else if(apple.position[i].types=ULTRA){
                        snake.longueur+=1;
                        infos.score+=100;
                    }

                    LibererSprite(apple.position[i].sprites);
                    majText(infos, snake, apple, direction);
                }
            }

            for (i = 0; i < apple.nbPomme; i++){
                if (apple.position[i].x == -1) {
                    int chance;
                    apple.position[i].x = (rand() % infos.nbX) * infos.tailleCase + 20;
                    apple.position[i].y = (rand() % infos.nbY) * infos.tailleCase + 20;
                    chance = (rand() % 100)+1;
                    if (chance<=85){
                        apple.position[i].types=BASIC;
                        apple.position[i].sprites = ChargerSprite("apple.png");
                    }else if(chance<=95){
                        apple.position[i].types=LARGE;
                        apple.position[i].sprites = ChargerSprite("apple-large.png");
                    }else if(chance>95){
                        apple.position[i].types=ULTRA;
                        apple.position[i].sprites = ChargerSprite("apple-ultra.png");
                    }
                    AfficherSprite(apple.position[i].sprites, apple.position[i].x, apple.position[i].y);
                    /*printf("pomme pos : %d|%d\n", apple.position[i].x,apple.position[i].y);*/
                }
            }

            if (checkDeplacement(infos, snake)){
                return infos.score;
            }
            majSnake(infos, snake, apple, direction);
        }

        if (Microsecondes()>timer){
            timer = Microsecondes()+SEC;
            infos.timerGame++;
            majText(infos, snake, apple, direction);
        }
    }
    return infos.score;
}
