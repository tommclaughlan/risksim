#ifndef RISK_Player_H
#define RISK_Player_H

#include <vector>
#include <set>
#include <string>

class Army;

class Player {

public:
	Player();
	Player(const std::string& name);
	std::string getName() const {return name_; }
	void addCountry(int c);
	void removeCountry(int c);
	std::set<int> getCountries() const {return countries_; }

private:
	std::string name_;
	std::set<int> countries_;


};

#endif // RISK_Player_H
