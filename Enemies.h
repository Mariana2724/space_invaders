#pragma once
#include "Ship.h"
#include <list>

class Enemies : public Ship {
	static int direction;
protected:
	int enemyType;
public:
	Enemies(int x, int y, int speed, int enemyType);
	void movement();
	int getEnemyType();
	virtual ~Enemies();
};

class EnemiesUI : public Enemies {
	
public:
	EnemiesUI(int x,int y,int speed, int enemyType);
	void draw();
	
	bool collided=false;
	~EnemiesUI();
};