#include "../include/Game.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    Game* game = new Game();

    game->setupBoard();
    game->setupPlayers();

    game->saveState("state.dat");

    delete game;

    int nturns = 5;
    int nmoves = 50;

    vector<pair<Move,int> > stats;

    for(int j=0; j<nmoves; ++j) {
        Game* initialGame = new Game("state.dat");
        vector<Move> moves;
        for(int i=0; i<nturns; ++i) {
            moves.push_back(initialGame->takeMove(0));
            initialGame->takeMove(1);
            initialGame->takeMove(2);
            initialGame->takeMove(3);
    	}

        pair<Move,int> eval;
        eval.first = moves[0];
        eval.second = initialGame->boardSummary();
        stats.push_back(eval);
        delete initialGame;
    }

    int bestscore = 0;
    Move bestmove;

    for(vector<pair<Move,int> >::const_iterator it = stats.begin(); it != stats.end(); ++it) {
        if( (*it).second > bestscore && (*it).first.where.first != -1) {
            bestscore = (*it).second;
            bestmove = (*it).first;
        }
    }
    cout << "Best move is from " << bestmove.where.first << " to " << bestmove.where.second << " with a score of " << bestscore << endl;

    return 0;
}
