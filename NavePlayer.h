#pragma once
#include "Ship.h"
using namespace std;

class NavePlayer:public Ship {
public:
	NavePlayer(int x, int y);
	void movementPlayer (int key);
	void movement() {};
};

class NavePlayerUI :public NavePlayer {
public:
	NavePlayerUI(int x, int y);
	void draw();
	
};
