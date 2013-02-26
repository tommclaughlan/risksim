#include "Game.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

Game::Game() {	
	vector<Country> s;
	players_.push_back(pair<Player,vector<Country> >(Player("A"),s));
	players_.push_back(pair<Player,vector<Country> >(Player("B"),s));
	players_.push_back(pair<Player,vector<Country> >(Player("C"),s));
	players_.push_back(pair<Player,vector<Country> >(Player("D"),s));

	countries_.push_back("Alaska");
	countries_.push_back("Alberta");
	countries_.push_back("Central America");
	countries_.push_back("Eastern US");
	countries_.push_back("Greenland");
	countries_.push_back("North Western Territories");
	countries_.push_back("Ontario");
	countries_.push_back("Quebec");
	countries_.push_back("Western US");
	countries_.push_back("Argentina");
	countries_.push_back("Brazil");
	countries_.push_back("Peru");
	countries_.push_back("Venezuela");
	countries_.push_back("Great Britain");
	countries_.push_back("Iceland");
	countries_.push_back("Northern Europe");
	countries_.push_back("Scandinavia");
	countries_.push_back("Southern Europe");
	countries_.push_back("Ukraine");
	countries_.push_back("Western Europe");
	countries_.push_back("Congo");
	countries_.push_back("East Africa");
	countries_.push_back("Egypt");
	countries_.push_back("Madagascar");
	countries_.push_back("North Africa");
	countries_.push_back("South Africa");
	countries_.push_back("Afghanistan");
	countries_.push_back("China");
	countries_.push_back("India");
	countries_.push_back("Irkutsk");
	countries_.push_back("Japan");
	countries_.push_back("Kamchatka");
	countries_.push_back("Middle East");
	countries_.push_back("Mongolia");
	countries_.push_back("Siam");
	countries_.push_back("Siberia");
	countries_.push_back("Ural");
	countries_.push_back("Yakutsk");
	countries_.push_back("East Australia");
	countries_.push_back("Indonesia");
	countries_.push_back("New Guinea");
	countries_.push_back("West Australia");
}

void Game::setupBoard() {

	ifstream readBoard("../res/board.dat");

	while(!readBoard.eof()) {
		string line;
		getline(readBoard, line, '\n');
		int elem;
		stringstream ss(line);
		vector<Country> c;

		while(ss >> elem) {
			c.push_back(Country(elem-1));
		}

		Country home = Country(c[0]);
		c.erase(c.begin());
		board_.insert(pair<Country,set<Country> >(home, set<Country>(c.begin(),c.end())));
	}

	// for(map<Countries,set<Countries> >::const_iterator it=board_.begin(); it != board_.end(); ++it) {
	// 	cout << (*it).first << endl;
	// 	set<Countries> tmp = (*it).second;
	// 	for(set<Countries>::const_iterator ct=tmp.begin(); ct != tmp.end(); ++ct) {
	// 		cout << "   " << (*ct) << endl;
	// 	}
	// }
}

void Game::setupPlayers() {

	int menPerPlayer = 40 - ((players_.size() - 2)*5);

	cout << "For " << players_.size() << " players, take " << menPerPlayer << " men each" << endl;

	//claim territories, random for now
	vector<int> random;
	for(int i=0; i<42; ++i) {
		random.push_back(i);
	}

	srand(time(0));
	random_shuffle(random.begin(), random.end());

	for(int i=0; i<42; ++i) {
		players_.at(i%4).second.push_back(Country(random.at(i)));
	}

	for(int i=0; i<players_.size(); ++i) {
		vector<Country> s = players_.at(i).second;
		for(vector<Country>::iterator it = s.begin(); it != s.end(); ++it) {
			cout << "Player " << players_.at(i).first.getName() << " drew " << countries_[(*it).getIndex()] << endl;
			it->addInfantry(players_.at(i).first);
		}


	}

	//now place troops in those territories, at least one in each

	
}