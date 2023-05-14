#include <iostream>
#include "Game.h"
#include <ctime>

int main() {

    srand(time(nullptr));
    Game game;
    while(game.running())
    {
        game.update();

        game.render();
    }

    return 0;
}
