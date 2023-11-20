#pragma once

struct Coordenates {
	int x, y;
};
 
class Ship {
	int x, y;
	int speed;
public:
	Ship();
	Ship(int x, int y);
	Ship(int x, int y, int speed);
	void moveLeft();
	void moveRight();
	void moveDown();
	bool checkCollisionBullet();
	Coordenates position() const;
};
