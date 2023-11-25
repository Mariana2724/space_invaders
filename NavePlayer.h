#ifndef NAVEPLAYER_H
#define NAVEPLAYER_H
#include "Ship.h"
using namespace std;

class NavePlayer:public Ship {
public:
	NavePlayer();
	NavePlayer(int x, int y);
	NavePlayer(int x, int y, int speed);
	void movementPlayer (int key);
	void draw();
};

#endif
