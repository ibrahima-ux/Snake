#ifndef SNAKE_H
#define SNAKE_H

#define CYCLE 100000L
#define SEC 1000000L

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef enum {
    DROITE, GAUCHE, HAUT, BAS
} Direction;

typedef enum {
    BASIC, ULTRA, LARGE
} Type;

typedef struct {
    int x, y, sprites;
    Type types;
    Direction dir;
} Position;

typedef struct {
    int nbX, nbY, tailleCase, timerGame, score;
} InfoJeux;

typedef struct {
    Position position[1000];
    Position posLast;
    int longueur;
} Snake;

typedef struct {
    Position position[5];
    int nbPomme;
} Apple;

typedef struct {
    Direction direction;
    Snake snake;
    Apple apple;
    InfoJeux infos;
} Jeux;

Jeux initialiser();
Snake deplacersnake(InfoJeux infos, Snake snake, Direction direction);
void initialiserSnake(InfoJeux infos, Snake snake, Apple apple, Direction direction);
int checkDeplacement(InfoJeux infos, Snake snake);
void majSnake(InfoJeux infos, Snake snake, Apple apple, Direction direction);
void majText(InfoJeux infos, Snake snake, Apple apple, Direction direction);
void gameOver(int score);
int gameStart(InfoJeux infos, Snake snake, Apple apple, Direction direction);

#endif
