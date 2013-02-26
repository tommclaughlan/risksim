#ifndef RISK_Player_H
#define RISK_Player_H

#include <vector>
#include <string>

class Army;

class Player {

public:
	Player();
	Player(const std::string& name);
	std::string getName() const {return name_; }

private:
	std::string name_;


};

#endif // RISK_Player_H
