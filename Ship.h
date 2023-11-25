#pragma once
#include <list>
#include "Game.h"
using namespace std; // também é preciso para a list
struct Coordenates {
	int x, y;
};
 
class Ship :public Game{
protected:
	int x, y;
	int speed;
//protected:
	//static list<Ship*> ships;
public:
	
	Ship();
	Ship(int x, int y);
	Ship(int x, int y, int speed);
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	bool checkCollisionBullet();
	//Coordenates position() const;
	int Getx();
	int Gety();
};
