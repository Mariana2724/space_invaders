#pragma once
#include "Ship.h"
#include <list>

//Enemy 1,2,3 movem-se em conjunto
class Enemy_1 :public Ship { //o que está mais perto do jogador
	public:
		Enemy_1(int x, int y, int speed);
		void draw();
};
class Enemy_2 :public Ship { //acima do Enemy_1
	public:
		Enemy_2(int x, int y, int speed);
		void draw();
};
class Enemy_3 :public Ship { //acima do Enemy_2
	public:
		Enemy_3(int x, int y, int speed);
		void draw();
};
class Enemy_4 :public Ship { //acima de todos os Enemies, passa pelo ecrã
	public:
		Enemy_4(int x, int y, int speed);
		void draw();
		void movement();
};



class Enemies {
public:
	//Enemies(int x, int y, int speed,int enemyType);
	//void movementEnemies(int key);
	void addEnemy(Ship* newEnemy);
	void moveAllEnemies();
	void drawAllEnemies();
private:
	list <Ship*> enemy;
};
