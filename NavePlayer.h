#pragma once
#include "Ship.h"

class NavePlayer:public Ship {
public:
	NavePlayer();
	NavePlayer(int x, int y);
	NavePlayer(int x, int y, int speed);
	void movementPlayer(char direction);

};
