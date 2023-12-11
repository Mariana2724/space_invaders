#pragma once
#include<list>
#include "Game.h"
#include "Enemies.h"
#include "Barrier.h"
using namespace std;

//bulletType 1 = bala da Nave
//bulletType 2 = bala do Enemy

class Bullets :public Game {
	private:
		float xbullet, ybullet, speed;
		int bulletType;
		list <EnemiesUI*> enemies;
		list <Bullets*> bulletNave; // fazer de inimigos e player
	public:
		Bullets(float xbullet, float ybullet, int speed, int bulletType);
		int getX();
		int getY();
		bool checkCollisionNave();
		bool checkCollisionEnemies(list<EnemiesUI*> enemies);
		bool checkCollisionBarriers(list<BarrierUI*> barrier);
		bool checkCollisionBullets();
		void moveBullet(); 
		
};
class BulletsUI :public Bullets {
public:
	BulletsUI(float xbullet, float ybullet, int speed,int bulletType);
	void draw();
};
