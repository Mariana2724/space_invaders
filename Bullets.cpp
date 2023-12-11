#include "Bullets.h"
#include <curses.h>
#include <list>

void Bullets::moveBullet(){
    switch (bulletType) {
    case 1:
        ybullet--;
        break;
    case 2:
        ybullet++;
        break;
    }
}
Bullets::Bullets(float xbullet, float ybullet, int speed, int bulletType) :xbullet(xbullet), ybullet(ybullet),speed(speed), bulletType(bulletType) {}

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
bool Bullets::checkCollisionBarriers(list<BarrierUI*> barriers){
    for (BarrierUI* barrier : barriers) {
        if (!barrier->collidedB && xbullet <= barrier->getx() + 7 && xbullet >= barrier->getx()  && ybullet >= barrier->gety() && ybullet <= barrier->gety()) {
            barrier->collidedB = true;
            barrier->wasShot();
            return true;
        }
    }
    return false;
}
BulletsUI::BulletsUI(float xbullet, float ybullet, int speed,int bulletType): Bullets(xbullet,ybullet,speed,bulletType){
}
void BulletsUI::draw(){
	mvprintw(getY(), getX(), "  ");
	mvprintw(getY(), getX(), " | ");

	refresh(); // Atualiza o ecrã
}