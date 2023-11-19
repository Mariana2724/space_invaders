#pragma once
#include "Ship.h"

class NavePlayer:public Ship {
public:
	NavePlayer();
	void movementPlayer(char direction);

};
