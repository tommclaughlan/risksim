#ifndef RISK_Country_H
#define RISK_Country_H

#include <vector>
#include <string>

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
	int getArmy() const { return army_; }
	int getPlayer() const { return player_; }
	void setPlayer(int p);
	void addInfantry(int a);
	void removeInfantry(int a);

    bool operator<(const Country& rhs) const { return getIndex() < rhs.getIndex(); }

private:
	int army_;
	int index_;
	int player_;

};

#endif // RISK_Country_H
