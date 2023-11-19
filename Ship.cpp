#include "Ship.h"

Ship::Ship(){
}

void Ship::moveLeft(){
	x -= speed;
	if (x < 0) { //para nao sair do ecra fica na mesma posi��o
		x = 0;
	}
}

void Ship::moveRight(){
	x = x + speed;
	if (x > 1000) { //para n�o sair do ecr� do lado direito
		x = 1000 ;
	}
}

void Ship::moveDown(){
	y = y + speed;
	if (y > 1000) { //para n�o sair do ecr� por baixo
		y = 1000;
	}
}

bool Ship::checkCollisionBullet(){
	return false;
}

Coordenates Ship::position() const{
	return {x,y};
}
