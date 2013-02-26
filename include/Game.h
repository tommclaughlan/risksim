#ifndef RISK_Game_H
#define RISK_Game_H

#include <map>
#include <vector>
#include <set>

#include "Country.h"

class Player;

class Move {
public:
	std::pair<int, int> where;
	bool success;
};

class Game {

public:
	Game();
	~Game();
	void setupBoard();
	void setupPlayers();
	Move takeMove(int pl);
	bool attack(Country* from, Country* to);
private:
	std::vector<std::pair<Country*, std::vector<Country*> > > board_;
	std::vector<Player*> players_;	
	std::vector<std::string> countries_;
	std::vector<Country*> country_objects_;


};

#endif // RISK_Game_H
