#include "Player.h"
#include "Country.h"
#include "Army.h"

#include <iostream>

Player::Player() {
}

Player::Player(const std::string& name) : name_(name) {
	std::cout << "Init player " << name_ << std::endl;
}

void Player::addCountry(int c) {
	countries_.insert(c);
}

void Player::removeCountry(int c) {
	countries_.erase(countries_.find(c));
}