#include "Game.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

Game::Game() {
	Player* p1 = new Player("A");
	players_.push_back(p1);
	Player* p2 = new Player("B");
	players_.push_back(p2);
	Player* p3 = new Player("C");
	players_.push_back(p3);
	Player* p4 = new Player("D");
	players_.push_back(p4);

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
		vector<Country*> c;

		while(ss >> elem) {
			Country* newc = new Country(elem-1);
			c.push_back(newc);
		}

		Country* home = c[0];
		c.erase(c.begin());
		pair<Country*, vector<Country*> > p;
		p.first = home;
		p.second = c;
		board_.push_back(p);
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
		pair<Country*, vector<Country*> > p = board_.at(random[i]);
		Player* player = players_.at(i%players_.size());
		p.first->setPlayer(player);
		cout << "Player " << p.first->getPlayer()->getName() << " drew " <<  countries_[p.first->getIndex()] << endl;
	}

	for(vector<Player*>::iterator pl = players_.begin(); pl != players_.end(); ++pl) {
		cout << (*pl)->getName() << endl;
		int menRemaining = menPerPlayer;
		for(vector<pair<Country*, vector<Country*> > >::iterator it = board_.begin(); it != board_.end(); ++it) {
			cout << countries_[it->first->getIndex()] << " " << it->first->getPlayer()->getName() << endl;
			if((*it).first->getPlayer() == (*pl)) {
				(*it).first->addInfantry(1);
				menRemaining--;
				//cout << "Added 1 men to " << countries_[(*it).first->getIndex()] << endl;
			}
		}
		while(menRemaining > 0){
			cout << menRemaining << endl;
			for(vector<pair<Country*, vector<Country*> > >::iterator it = board_.begin(); it != board_.end(); ++it) {
				if((*it).first->getPlayer() == (*pl)) {
					int m = rand() % 2;
					m = m > menRemaining ? 0 : m;
					(*it).first->addInfantry(m);
					menRemaining-=m;
					//cout << "Added " << m << " men to " << countries_[(*it).first->getIndex()] << endl;
				}
			}
		}
	}
	for(vector<pair<Country*, vector<Country*> > >::iterator it = board_.begin(); it != board_.end(); ++it) {
		cout << "Player " << it->first->getPlayer()->getName() << "'s country " << countries_[it->first->getIndex()] << " has " << it->first->getArmy()->size() << " men" << endl;
	}

	
}