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
		float xbullet, ybullet, speed;
		int bulletType;
		list <EnemiesUI*> enemies;
		list <Bullets*> bulletNave; // fazer de inimigos e player
		list<Bullets*> bulletsEnemy;
	public:
		Bullets(float xbullet, float ybullet, int speed, int bulletType);
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
	BulletsUI(float xbullet, float ybullet, int speed,int bulletType);
	void draw();
};
