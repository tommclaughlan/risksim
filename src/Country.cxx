#include "Country.h"
#include "Army.h"
#include "Player.h"

Country::Country(int c) : 
	index_(c) {
}

void Country::addInfantry(Player p) {
	if(army_.size() == 0)
		army_.setPlayer(p);

	army_.addInfantry();
}