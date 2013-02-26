#include "../include/Game.h"

using namespace std;

int main(int argc, char* argv[]) {

    Game* game = new Game();

    game->setupBoard();
    game->setupPlayers();

    game->takeMove(0);

    delete game;

    return 0;
}
