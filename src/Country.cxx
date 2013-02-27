#include "Country.h"
#include "Army.h"
#include "Player.h"

Country::Country() {
}

Country::Country(int c) : 
	index_(c) {
	army_ = new Army();
}

void Country::setPlayer(Player* p) {
	player_ = p;
}

Army* Country::copyArmy() {
	Army* copy = new Army(*army_);
	return copy;
}

void Country::setArmy(Army* a) {
	army_ = a;
}