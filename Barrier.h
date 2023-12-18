#pragma once
#include "Shapes.h"
#include <iostream>
struct CoordB {
	int x, y;
};
class Barrier:public Shapes {
	CoordB position;
protected:
	int score;
public:
	Barrier(int x, int y, int score);
	int getX();
	int getY();
	int wasShot();
	void movement() {};
};

class BarrierUI:public Barrier {
public:
	BarrierUI(int x, int y);
	bool destroyed;
	void draw();
};
