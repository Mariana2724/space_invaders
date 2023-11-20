#pragma once
#include <list>
using namespace std; // tamb�m � preciso para a list
struct Coordenates {
	int x, y;
};
 
class Ship {
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
	bool checkCollisionBullet();
	virtual void draw();
	Coordenates position() const;
};
