#include "snake.h"

int main(void) {
    Jeux jeuxSnake;
    srand(time(NULL));
    jeuxSnake = initialiser();

    initialiserSnake(jeuxSnake.infos, jeuxSnake.snake, jeuxSnake.apple, jeuxSnake.direction);
    gameOver(gameStart(jeuxSnake.infos, jeuxSnake.snake, jeuxSnake.apple, jeuxSnake.direction));

    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}
