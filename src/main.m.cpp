#include <iostream>

#include "Game.h"

int main(int, char**) {
    Game game;

    // Game loop
    while(game.running()) {

        game.update();

        game.render();
    }

    return 0;
}
