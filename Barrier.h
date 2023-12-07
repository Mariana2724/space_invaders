#pragma once
#include "Game.h"
#include <iostream>

class Barrier:public Game {
	int x, y;
protected:
	int score;
public:
	Barrier(int x, int y, int score);
	int getx();
	int gety();
};

class BarrierUI:public Barrier {
public:
	BarrierUI(int x, int y);
	void draw();
};
