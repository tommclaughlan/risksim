#ifndef RISK_Game_H
#define RISK_Game_H

#include <map>
#include <vector>
#include <set>

#include "Country.h"

class Player;

class Game {

public:
	Game();
	void setupBoard();
	void setupPlayers();
private:
	std::map<Country, std::set<Country> > board_;
	std::vector<std::pair<Player,std::vector<Country> > > players_;	
	std::vector<std::string> countries_;


};

#endif // RISK_Game_H
