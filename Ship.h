#pragma once
#include <list>
#include "Shapes.h"
using namespace std; // também é preciso para a list
struct Coordenates {
	int x, y;
};
 
class Ship :public Shapes {
protected:
	Coordenates pos;
	int speed;
public:
	Ship();
	Ship(int x, int y);
	Ship(int x, int y, int speed);
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	bool checkCollisionBullet();
	int getX();
	int getY();
};
