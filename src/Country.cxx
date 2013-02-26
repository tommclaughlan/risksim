#include "Country.h"
#include "Army.h"
#include "Player.h"

Country::Country() {
}

Country::Country(int c) : 
	index_(c) {
	army_ = new Army();
}
void Country::addInfantry(int n) {
	army_->addInfantry(n);
}

void Country::setPlayer(Player* p) {
	player_ = p;
}