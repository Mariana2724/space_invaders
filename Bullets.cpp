#include "Bullets.h"
#include <curses.h>
#include <list>

void Bullets::moveBullet(){
	ybullet--;
}
Bullets::Bullets(float xbullet, float ybullet, int speed) :xbullet(xbullet), ybullet(ybullet),speed(speed) {}

int Bullets::getX(){
	return xbullet;
}

int Bullets::getY(){
	return ybullet;
}
bool Bullets::checkCollisionEnemies(list<EnemiesUI*> enemies) {
    for (EnemiesUI* enemy : enemies) {
        if (!enemy->collided && xbullet <= enemy->Getx()+3 &&xbullet>= enemy->Getx() - 3 && ybullet >= enemy->Gety() && ybullet <= enemy->Gety()) {
            enemy->collided = true;
            return true;
        }
    }
    return false;
}
bool Bullets::checkCollisionBarriers(){



    return false;
}
BulletsUI::BulletsUI(float xbullet, float ybullet, int speed): Bullets(xbullet,ybullet,speed){
}
void BulletsUI::draw(){
	mvprintw(getY(), getX(), "  ");
	mvprintw(getY(), getX(), " | ");

	refresh(); // Atualiza o ecrã
}