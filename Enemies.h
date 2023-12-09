#pragma once
#include "Ship.h"
#include <list>

class Enemies : public Ship {
protected:
	int enemyType;
	static int numberOfEnemies;
public:
	Enemies(int x, int y, int speed, int enemyType);
	//void movementEnemies(int key);
	virtual ~Enemies();
};

class EnemiesUI : public Enemies {
	static int direction;
	static int Reached;
	int a;
public:
	EnemiesUI(int x,int y,int speed, int enemyType);
	void movement();
	void draw();
	bool collided=false;
	~EnemiesUI();
};