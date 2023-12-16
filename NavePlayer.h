#pragma once
#include "Ship.h"
#include "Game.h"
using namespace std;

class NavePlayer:public Ship {
public:
	NavePlayer();
	NavePlayer(int x, int y);
	NavePlayer(int x, int y, int speed);
	void movementPlayer (int key);
	void movement() {};
};

class NavePlayerUI :public NavePlayer {
public:
	NavePlayerUI(int x, int y, int speed);
	void draw();
	
};
