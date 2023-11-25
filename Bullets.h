#pragma once


class Bullets {
	private:
		int x, y, speed;
	public:
		bool checkCollisionNave();
		bool checkCollisionEnemies();
		bool checkCollisionBarriers();
		bool checkCollisionBullets();
};
