#pragma once
#include "Game.h"
#include <iostream>

class Barrier:public Game {
	int x, y;
public:
	Barrier(int x, int y);
};

class BarrierUI:public Barrier {
public:
	BarrierUI(int x, int y);
	void draw();
};
