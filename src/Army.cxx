#include "Army.h"


Army::Army() : size_(0) {
}

void Army::setPlayer(Player p) {
	player_ = p;
}

void Army::addInfantry() {
	size_++;
}