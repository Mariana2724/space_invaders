#pragma once
#include "Ship.h"
#include <list>

class Enemies : public Ship {
protected:
	int enemyType;
public:
	Enemies(int x, int y, int speed, int enemyType);
	//void movementEnemies(int key);
};

class EnemiesUI : public Enemies {
public:
	EnemiesUI(int x,int y,int speed, int enemyType);
	void movement();
	void draw();
};