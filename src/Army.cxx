#include "Army.h"


Army::Army() : size_(0) {
}

void Army::addInfantry(int n) {
	size_+=n;
}

void Army::killMan() {
	size_--;
}