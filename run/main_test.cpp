#include "../include/Game.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {

    Game* game = new Game();

    game->setupBoard();
    game->setupPlayers();

    Game* initialGame = new Game(game);
    delete game;
    int nturns = 5;
    int nmoves = 50;

    vector<pair<Move,int> > stats;

    for(int j=0; j<nmoves; ++j) {
        Game* test = new Game(initialGame);
        // delete game;
        // game = test;
        vector<Move> moves;
        for(int i=0; i<nturns; ++i) {
            moves.push_back(test->takeMove(0));
            test->takeMove(1);
            test->takeMove(2);
            test->takeMove(3);
    	}

        pair<Move,int> eval;
        eval.first = moves[0];
        eval.second = game->boardSummary();
        stats.push_back(eval);
    }

    int bestscore = 0;
    Move bestmove;

    for(vector<pair<Move,int> >::const_iterator it = stats.begin(); it != stats.end(); ++it) {
        if( (*it).second > bestscore ) {
            bestscore = (*it).second;
            bestmove = (*it).first;
        }
    }
    cout << "Best move is from " << bestmove.where.first << " to " << bestmove.where.second << " with a score of " << bestscore << endl;

    return 0;
}
