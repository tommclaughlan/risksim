#ifndef RISK_Country_H
#define RISK_Country_H

#include <vector>
#include <string>
#include "Army.h"
class Player;

enum Group {
	NorthAmerica,
	SouthAmerica,
	Europe,
	Africa,
	Asia,
	Australia
};
class Country {

public:
	Country();
	Country(int c);
	Group getGroup();
	int getIndex() const {return index_; }
	std::string getName() const {return name_; }
	Army* getArmy() const { return army_; }
	Player* getPlayer() const { return player_; }
	void addInfantry(int n);
	void setPlayer(Player* p);

    bool operator<(const Country& rhs) const { return getIndex() < rhs.getIndex(); }

private:
	Army* army_;
	int index_;
	Player* player_;
	std::string name_;

};

#endif // RISK_Country_H
