#pragma once
#include<list>
#include "Shapes.h"
#include "Enemies.h"
#include "Barrier.h"
#include "NavePlayer.h"
using namespace std;

//bulletType 1 = bala da Nave
//bulletType 2 = bala do Enemy

struct CoordBullets {
	int xbullet, ybullet;
};

class Bullets :public Shapes {
	private:
		CoordBullets coord;
		int bulletType;
		list <EnemiesUI*> enemies;
	public:
		Bullets(int xbullet, int ybullet, int bulletType);
		int getX();
		int getY();
		bool checkCollisionNave(NavePlayerUI Nave);
		int checkCollisionEnemies(list<EnemiesUI*> enemies);
		int checkCollisionBarriers(list<BarrierUI*> barrier);
		void movement(); 
		
};
class BulletsUI :public Bullets {
public:
	BulletsUI(int xbullet, int ybullet, int bulletType);
	void draw();
};
