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

	for(int i=0; i<countries_.size(); ++i) {
		Country* c = new Country(i);
		country_objects_.push_back(c);
	}
}

Game::~Game() {
	for(vector<Player*>::iterator p = players_.begin(); p != players_.end(); ++p)
		delete *p;
	players_.clear();

	for(vector<pair<Country*, vector<Country*> > >::iterator it = board_.begin(); it != board_.end(); ++it) {
		delete it->first;
		it->second.clear();
	}
	board_.clear();


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
			Country* newc = country_objects_[elem-1];
			c.push_back(newc);
		}

		Country* home = c[0];
		c.erase(c.begin());
		pair<Country*, vector<Country*> > p;
		p.first = home;
		p.second = c;
		board_.push_back(p);
	}
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
		player->addCountry(random[i]);
		//cout << "Player " << p.first->getPlayer()->getName() << " drew " <<  countries_[p.first->getIndex()] << endl;
	}

	for(vector<Player*>::iterator pl = players_.begin(); pl != players_.end(); ++pl) {
		int menRemaining = menPerPlayer;

		set<int> cs = (*pl)->getCountries();

		for(set<int>::const_iterator it = cs.begin(); it != cs.end(); ++it){
			board_[(*it)].first->addInfantry(1);
			menRemaining--;
		}

		while(menRemaining>0) {
			for(set<int>::const_iterator it = cs.begin(); it != cs.end(); ++it){
				int m = rand() % 2;
				m = m > menRemaining ? 0 : m;
				board_[(*it)].first->addInfantry(m);
				menRemaining-=m;
			}
		}
	}
	// for(vector<pair<Country*, vector<Country*> > >::iterator it = board_.begin(); it != board_.end(); ++it) {
	// 	cout << "Player " << it->first->getPlayer()->getName() << "'s country " << countries_[it->first->getIndex()] << " has " << it->first->getArmy()->size() << " men" << endl;
	// }

	
}

Move Game::takeMove(int pl) {

	Player* player = players_[pl];

	int r = rand() % player->getCountries().size();

	set<int>::const_iterator it;
	int from = -1;
	int to = from;

	bool validMoveExists = false;
	while(!validMoveExists) {
		r = rand() % player->getCountries().size();
		it = player->getCountries().begin();
		advance(it,r);
		from = *it;
		to = from;
		vector<Country*> possibles = board_[from].second;
		for(vector<Country*>::const_iterator cit = possibles.begin(); cit != possibles.end(); ++cit) {
			if((*cit)->getPlayer()->getName() != player->getName() && board_[from].first->getArmy()->size() > 1)
				validMoveExists = true;
		}
	}

	to = board_[from].second[rand() % board_[from].second.size()]->getIndex();

	cout << "From " << countries_[from] << " (Player " << player->getName() << ")" << endl;
	cout << "To " << countries_[to] << " (Player " << board_[to].first->getPlayer()->getName() << ")" << endl;

	Move turn;
	pair<int,int> p;
	p.first = from;
	p.second = to;
	turn.where = p;
	turn.success = attack(board_[from].first, board_[to].first);

	if(turn.success)
		cout << "Move from " << countries_[from] << " to " << countries_[to] << " was successful!" << endl;
	else
		cout << "Move from " << countries_[from] << " to " << countries_[to] << " was not successful! :(" << endl;

	return turn;
}

bool Game::attack(Country* from, Country* to) {
	Army* attackers = from->getArmy();
	Army* defenders = to->getArmy();
	while (defenders->size() > 0 && attackers->size() > 1) {
		int attackDie = attackers->size() > 3 ? 3 : attackers->size() - 1;
		int defDie = defenders->size() > 2 ? 2 : defenders->size();

		cout << attackDie << " vs " << defDie << endl;

		vector<int> defendersRoll;
		vector<int> attackersRoll;

		for(int d=0; d<defDie; ++d) {
			defendersRoll.push_back((rand() % 6) + 1);
		}
		for(int d=0; d<attackDie; ++d) {
			attackersRoll.push_back((rand() % 6) + 1);
		}

		sort(attackersRoll.rbegin(), attackersRoll.rend());
		sort(defendersRoll.rbegin(), defendersRoll.rend());

		for(int d=0; d<defendersRoll.size(); ++d) {
			if(attackersRoll[d] > defendersRoll[d])
				defenders->killMan();
			else
				attackers->killMan();
			cout << defenders->size() << endl;
		}
	}

	if(defenders->size() == 0)
		return true;
	
	return false;
}