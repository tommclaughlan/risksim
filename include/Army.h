#ifndef RISK_Army_H
#define RISK_Army_H

#include "Player.h"

class Army {

public:
	Army();

	int size() const { return size_; }
	void addInfantry(int n);
	void killMan();

private:
	int size_;

};

#endif // RISK_Army_H
