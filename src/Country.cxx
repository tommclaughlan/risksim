#include "Country.h"

Country::Country() {
}

Country::Country(int c) : 
	index_(c) {
	army_ = 0;
}

void Country::setPlayer(int p) {
	player_ = p;
}

void Country::addInfantry(int a) {
	army_ += a;
}

void Country::removeInfantry(int a) {
	army_ -= a;
}