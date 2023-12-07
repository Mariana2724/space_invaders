#pragma once
#include<list>
#include "Game.h"
using namespace std;

class Bullets :public Game {
	private:
		float xbullet, ybullet, speed;
		list <Bullets*> bullet; // fazer de inimigos e player
	public:
		Bullets(float xbullet, float ybullet, int speed);
		int getX();
		int getY();
		bool checkCollisionNave();
		bool checkCollisionEnemies();
		bool checkCollisionBarriers();
		bool checkCollisionBullets();
		void moveBullet(); 

};
class BulletsUI :public Bullets {
public:
	BulletsUI(float xbullet, float ybullet, int speed);
	void draw();
};
