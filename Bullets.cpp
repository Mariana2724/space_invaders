#include "Bullets.h"
#include <curses.h>
#include <list>

void Bullets::moveBullet(int key){
	if (key == 32) {
		ybullet--;
	}
}
Bullets::Bullets(float xbullet, float ybullet, int speed) :xbullet(xbullet), ybullet(ybullet),speed(speed) {}

int Bullets::getX(){
	return xbullet;
}

int Bullets::getY(){
	return ybullet;
}
void BulletsUI::draw(){
	mvprintw(getY(), getX(), "  ");
	mvprintw(getY(), getX(), " | ");

	refresh(); // Atualiza o ecrã
}