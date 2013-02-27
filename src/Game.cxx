#include "Game.h"
#include "Player.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

Game::Game() {
	init();
	cout << "Game::Game() init done" << endl;
}

Game::Game(const string& state) {

	init();
	setupBoard();

	ifstream existing("state.dat");

	while(!existing.eof()) {
		string line;
		getline(existing, line, '\n');
		int elem;
		stringstream ss(line);

		int country = -1;
		int player = -1;
		int army = -1;

		ss >> country;
		ss >> player;
		ss >> army;

		if(existing.eof())
			break;

		board_[country].first->setPlayer(player);
		players_[player]->addCountry(country);
		board_[country].first->addInfantry(army);
	}
	existing.close();
	cout << "Read state from file" << endl;
	for(vector<pair<Country*, vector<Country*> > >::iterator it = board_.begin(); it != board_.end(); ++it) {
		cout << "Player " << players_[it->first->getPlayer()]->getName() << "'s country " << countries_[it->first->getIndex()] << " has " << it->first->getArmy() << " men" << endl;
	}


}

void Game::init() {
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

void Game::saveState(const string& name) {

	ofstream state(name.c_str());

	for(vector<pair<Country*, vector<Country*> > >::iterator it = board_.begin(); it != board_.end(); ++it) {
		int country = (*it).first->getIndex();
		int player = (*it).first->getPlayer();
		int army = (*it).first->getArmy();

		state << country << " " << player << " " << army << endl;
	}

	state.close();
}

void Game::setupBoard() {

	cout << "setupBoard() start" << endl;
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
	readBoard.close();
	cout << "setupBoard() done" << endl;
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
		p.first->setPlayer(i%players_.size());
		player->addCountry(random[i]);
		//cout << "Player " << p.first->getPlayer()->getName() << " drew " <<  countries_[p.first->getIndex()] << endl;
	}

	for(vector<Player*>::iterator pl = players_.begin(); pl != players_.end(); ++pl) {
		int menRemaining = menPerPlayer;

		set<int> cs = (*pl)->getCountries();

		for(set<int>::const_iterator it = cs.begin(); it != cs.end(); ++it){
			board_[(*it)].first->addInfantry(1);
			//cout <<(*it) << endl;
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
	for(vector<pair<Country*, vector<Country*> > >::iterator it = board_.begin(); it != board_.end(); ++it) {
		cout << "Player " << players_[it->first->getPlayer()]->getName() << "'s country " << countries_[it->first->getIndex()] << " has " << it->first->getArmy() << " men" << endl;
	}
	cout << "Done" << endl;
	
}

Move Game::takeMove(int pl) {

	Player* player = players_[pl];

	int r = rand() % player->getCountries().size();
	int from = -1;
	int to = from;
	
	set<int> cs = player->getCountries();
	r = rand() % cs.size();
	int n = 0;
	
	vector<int> froms;

	for(set<int>::const_iterator it = cs.begin(); it != cs.end() && n < r+1; ++it, ++n) {
		if(board_[(*it)].first->getArmy() > 1)
			froms.push_back(*it);
	}
	if(froms.size() == 0){
		Move turn;
		pair<int,int> p;
		p.first = -1;
		p.second = -1;
		turn.where = p;
		turn.success = false;
		return turn;
	}
	else
		from = froms[rand() % froms.size()];
	
	to = board_[from].second[rand() % board_[from].second.size()]->getIndex();


	// cout << "From " << countries_[from] << " (Player " << player->getName() << ")" << endl;
	// cout << "To " << countries_[to] << " (Player " << players_[board_[to].first->getPlayer()]->getName() << ")" << endl;

	Move turn;
	pair<int,int> p;
	p.first = from;
	p.second = to;
	turn.where = p;
	if(player->getName() == players_[board_[to].first->getPlayer()]->getName())
		turn.success = true;
	else
		turn.success = attack(board_[from].first, board_[to].first);

	// if(turn.success)
	// 	cout << "Move from " << countries_[from] << " to " << countries_[to] << " was successful!" << endl;
	// else
	// 	cout << "Move from " << countries_[from] << " to " << countries_[to] << " was not successful! :(" << endl;

	if(turn.success) {
		if(pl != board_[to].first->getPlayer()) {
			players_[board_[to].first->getPlayer()]->removeCountry(to);
			player->addCountry(to);
			board_[to].first->setPlayer(pl);
		}
		int f = board_[from].first->getArmy();
		int t = board_[to].first->getArmy();
		int movers = rand() % (f-1) + 1;
		board_[from].first->removeInfantry(movers);
		board_[to].first->addInfantry(movers);
	}

	return turn;
}

bool Game::attack(Country* from, Country* to) {
	int attackers = from->getArmy();
	int defenders = to->getArmy();
	while (defenders > 0 && attackers > 1) {
		int attackDie = attackers > 3 ? 3 : attackers - 1;
		int defDie = defenders > 2 ? 2 : defenders;

		//cout << attackDie << " vs " << defDie << endl;

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
				to->removeInfantry(1);
			else
				from->removeInfantry(1);

			attackers = from->getArmy();
			defenders = to->getArmy();
			//cout << defenders->size() << endl;
		}

		if(attackers <= defenders && rand() % 100 < 80)
			break;
	}

	if(defenders == 0)
		return true;
	
	return false;
}

int Game::boardSummary() {
	set<int> Acs = players_[0]->getCountries();
	int score = Acs.size();
	for(set<int>::const_iterator it = Acs.begin(); it != Acs.end(); ++it){
		score += country_objects_[*it]->getArmy();
	}

	// for(vector<Player*>::iterator pl = players_.begin(); pl != players_.end(); ++pl) {
	// 	set<int> cs = (*pl)->getCountries();

	// 	for(set<int>::const_iterator it = cs.begin(); it != cs.end(); ++it){
	// 		cout << "Player " << (*pl)->getName() << " owns " << countries_[board_[(*it)].first->getIndex()] << endl;
	// 	}
	// }

	return score;
}