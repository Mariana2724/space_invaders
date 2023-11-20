#pragma once
#include "Ship.h"
using namespace std;

class NavePlayer:public Ship {
public:
	NavePlayer();
	void movementPlayer(char direction);

};
