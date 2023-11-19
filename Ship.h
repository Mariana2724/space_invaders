#pragma once

struct Coordenates {
	int x, y;
};
 
class Ship {
	int x, y;
	int speed;
public:
	Ship();
	void moveLeft();
	void moveRight();
	void moveDown();
	bool checkCollisionBullet();
	Coordenates position() const;
};
