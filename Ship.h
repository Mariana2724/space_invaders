#pragma once
#include <list>
#include "Shapes.h"
using namespace std; 
struct Coordenates {
	int x, y;
};
 
class Ship :public Shapes {
protected:
	Coordenates pos;
public:
	Ship(int x, int y);
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	int getX();
	int getY();
};
