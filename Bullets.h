#pragma once
#include<list>
using namespace std;

class Bullets {
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
		void moveBullet(int key); 

};
class BulletsUI :public Bullets {
	void draw();
};
