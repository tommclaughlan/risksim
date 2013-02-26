#ifndef RISK_Country_H
#define RISK_Country_H

#include <vector>
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
	Country(int c);
	Group getGroup();
	int getIndex() const {return index_; }
	Army getArmy() const { return army_; }
	void addInfantry(Player p);

    bool operator<(const Country& rhs) const { return getIndex() < rhs.getIndex(); }

private:
	Army army_;
	int index_;

};

#endif // RISK_Country_H
