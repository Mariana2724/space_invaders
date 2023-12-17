#include "Bullets.h"
#include "Game.h"
#include "GameStatus.h"
#include <curses.h>
#include "NavePlayer.h"
#include <list>

void Bullets::movement(){
    switch (bulletType) {
    case 1:
        coord.ybullet--;
        break;
    case 2:
        coord.ybullet++;
        break;
    }
}
Bullets::Bullets(int xbullet, int ybullet, int speed, int bulletType) :speed(speed), bulletType(bulletType) {
    this->coord.xbullet = xbullet;
    this->coord.ybullet = ybullet;
}

int Bullets::getX(){
	return coord.xbullet;
}

int Bullets::getY(){
	return coord.ybullet;
}
int Bullets::checkCollisionEnemies(list<EnemiesUI*> enemies) {
    for (EnemiesUI* enemy : enemies) {
        if (!enemy->collided && coord.xbullet <= enemy->getX()+3 && coord.xbullet>= enemy->getX() - 3 && coord.ybullet >= enemy->getY() && coord.ybullet <= enemy->getY()) {
            switch (enemy->getEnemyType()) {
            case 1:
                GameStatus::GameScore += 50;
                break;
            case 2:
                GameStatus::GameScore += 20;
                break;
            case 3:
                GameStatus::GameScore += 10;
                break;
            case 4:
                GameStatus::GameScore += 100;
                break;
            default:
                GameStatus::GameScore += 10;
                break;
            }
            enemy->collided = true;
            return 1;
        }
    }
    return 0;
}
int Bullets::checkCollisionBarriers(list<BarrierUI*> barriers){
    for (BarrierUI* barrier : barriers) {
        if (coord.xbullet <= barrier->getX() + 7 && coord.xbullet >= barrier->getX()  && coord.ybullet >= barrier->getY() && coord.ybullet <= barrier->getY()) {
            if (barrier->wasShot()) {
                barrier->collidedB = true;
                return 0;
            }
            return 1;
        }
    }
    return 2;
}

bool Bullets::checkCollisionNave(NavePlayerUI Nave) {
    if (coord.xbullet <= Nave.getX() + 5 && coord.xbullet >= Nave.getX() && coord.ybullet >= Nave.getY() && coord.ybullet <= Nave.getY()) {
        GameStatus::LivesPlayer--;
        return true;
    }
    return false;

}
BulletsUI::BulletsUI(int xbullet, int ybullet, int speed,int bulletType): Bullets(xbullet,ybullet,speed,bulletType){
}
void BulletsUI::draw(){
    if (getY() > 2) {
        mvprintw(getY(), getX(), "  ");
        mvprintw(getY(), getX(), " | ");
    }
	

	refresh(); // Atualiza o ecrã
}