#include "Bullets.h"
#include"Game.h"
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
            switch (enemy->getEnemyType()) {
            case 1:
                GameScore += 50;
                break;
            case 2:
                GameScore += 20;
                break;
            case 3:
                GameScore += 10;
                break;
            case 4:
                GameScore += 100;
                break;
            default:
                GameScore += 10;
                break;
            }
            enemy->collided = true;
            return true;
        }
    }
    return false;
}
int Bullets::checkCollisionBarriers(list<BarrierUI*> barriers){
    for (BarrierUI* barrier : barriers) {
        if (xbullet <= barrier->getx() + 7 && xbullet >= barrier->getx()  && ybullet >= barrier->gety() && ybullet <= barrier->gety()) {
            barrier->collidedB = true;
            if (barrier->wasShot()) {
                return 0;
            }
            return 1;
        }
    }
    return 2;
}
bool Bullets::checkCollisionNave(NavePlayerUI Nave) {
    if (xbullet <= Nave.Getx() + 5 && xbullet >= Nave.Getx() && ybullet >= Nave.Gety() && ybullet <= Nave.Gety()) {
        LivesPlayer--;
        return true;
    }
    return false;

}
//bool BulletsUI::checkCollisionBullets(list<BulletsUI*>bulletsO) {
//    for (BulletsUI* bulletO : bulletsO) {
//        if (getX() <= bulletO->getX() && getX() >= bulletO->getX() && getY() >= bulletO->getY() && getY() <= bulletO->getY()) {
//            // bulletsO.erase(bulletO);
//            return true;
//        }
//    }
//    return false;
//}
BulletsUI::BulletsUI(float xbullet, float ybullet, int speed,int bulletType): Bullets(xbullet,ybullet,speed,bulletType){
}
void BulletsUI::draw(){
	mvprintw(getY(), getX(), "  ");
	mvprintw(getY(), getX(), " | ");

	refresh(); // Atualiza o ecrã
}