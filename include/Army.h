#ifndef RISK_Army_H
#define RISK_Army_H

#include "Player.h"

class Army {

public:
	Army();

	int size() const { return size_; }
	Player getPlayer() const { return player_; }
	void setPlayer(Player p);
	void addInfantry();

private:
	int size_;
	Player player_;



};

#endif // RISK_Army_H
