#pragma once
#include "Ship.h"
#include <list>

class Enemies : public Ship {
	
protected:
	int enemyType;
	static int direction;
public:
	Enemies(int x, int y, int enemyType);
	void movement();
	int getEnemyType();
	virtual ~Enemies();
};

class EnemiesUI : public Enemies {
	
public:
	EnemiesUI(int x,int y, int enemyType);
	void draw();
	bool collided=false;
	~EnemiesUI();
};