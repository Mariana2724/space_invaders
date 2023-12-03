#include <stdio.h>
#include<iostream>
#include <curses.h>
#include <thread>
#include <chrono>
#include <exception>
#include <stdexcept>
using namespace std;
#include "Game.h"
#include "Naveplayer.h"
#include "Ship.h"
#include "Enemies.h"
#include "Bullets.h"

/*
void moveEnemyAutomatically(Enemies& enemyGroup) {
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(200)); // Ajuste o intervalo de tempo conforme necessário

		// Move o Enemy_4 automaticamente
		enemyGroup.moveAllEnemies(); // Método para mover todos os inimigos
	}
}*/

int main() {

	Game myGame;
	myGame.start();

	return 0;
}
