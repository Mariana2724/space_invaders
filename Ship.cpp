#include "Ship.h"
#include <iostream>
#include <list>
using namespace std;

Ship::Ship(){}
Ship::Ship(int x, int y){
	this->pos.x = x;
	this->pos.y = y;
}
Ship::Ship(int x, int y, int speed) :speed(speed) {
	this->pos.x = x;
	this->pos.y = y;
}
void Ship::moveLeft(){
	pos.x--;
	if (pos.x < 0) { //para nao sair do ecra fica na mesma posi��o
		pos.x = 0;
	}
}

void Ship::moveRight(){
	pos.x++;
	if (pos.x > 115) { //para n�o sair do ecr� do lado direito
		pos.x = 115 ;
	}
}

void Ship::moveDown(){
	pos.y ++;
	if (pos.y > 100) { //para n�o sair do ecr� por baixo
		pos.y = 100;
	}
}

void Ship::moveUp(){
	pos.y--;
	if (pos.y < 0) {
		pos.y = 0;
	}
}

bool Ship::checkCollisionBullet(){
	return false;
}

int Ship::getX(){
	return pos.x;
}

int Ship::getY(){
	return pos.y;
}

