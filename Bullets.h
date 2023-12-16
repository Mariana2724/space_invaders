#pragma once
#include<list>
#include "Game.h"
#include "Enemies.h"
#include "Barrier.h"
#include "NavePlayer.h"
using namespace std;

//bulletType 1 = bala da Nave
//bulletType 2 = bala do Enemy

class Bullets :public Game {
	private:
		int xbullet, ybullet, speed;
		int bulletType;
		list <EnemiesUI*> enemies;
	public:
		Bullets(int xbullet, int ybullet, int speed, int bulletType);
		int getX();
		int getY();
		bool checkCollisionNave(NavePlayerUI Nave);
		int checkCollisionEnemies(list<EnemiesUI*> enemies);
		int checkCollisionBarriers(list<BarrierUI*> barrier);
		
		void moveBullet(); 
		
};
class BulletsUI :public Bullets {
public:
	bool checkCollisionBullets(list<BulletsUI*>bulletsO);
	BulletsUI(int xbullet, int ybullet, int speed,int bulletType);
	void draw();
};
