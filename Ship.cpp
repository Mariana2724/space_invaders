#include "Ship.h"
#include <iostream>
#include <list>
using namespace std;

Ship::Ship(){
	//Ship* s;
	//this->

}
Ship::Ship(int x, int y): x(x),y(y){

}
Ship::Ship(int x, int y, int speed) : x(x), y(y), speed(speed) {

}
void Ship::moveLeft(){
	x--;
	if (x < 0) { //para nao sair do ecra fica na mesma posição
		x = 0;
	}
}

void Ship::moveRight(){
	x++;
	if (x > 100) { //para não sair do ecrã do lado direito
		x = 100 ;
	}
}

void Ship::moveDown(){
	y++;
	if (y > 100) { //para não sair do ecrã por baixo
		y = 100;
	}
}

bool Ship::checkCollisionBullet(){
	return false;
}

int Ship::Getx()
{
	return x;
}

int Ship::Gety()
{
	return y;
}

/*Coordenates Ship::position() const {
	return {x,y};
}*/
