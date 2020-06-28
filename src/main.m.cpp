#include <iostream>

#include "Game.h"

int main(int, char**) {

    std::srand(static_cast<unsigned>(time(NULL)));

    Game game;

    // Game loop
    while(game.running() && !game.getEndGame()) {

        game.update();

        game.render();
    }

    return 0;
}
