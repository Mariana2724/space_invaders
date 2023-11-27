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

void initGame();
/*
void moveEnemyAutomatically(Enemies& enemyGroup) {
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(200)); // Ajuste o intervalo de tempo conforme necessário

		// Move o Enemy_4 automaticamente
		enemyGroup.moveAllEnemies(); // Método para mover todos os inimigos
	}
}*/

int main() {
	/*initGame();
	-----Enemies enemyGroup;
	-----enemyGroup.addEnemy(new Enemy_4(0, 2, 1));
	//thread enemyThread(moveEnemyAutomatically, ref(enemyGroup));

	int height = 3;
	int width = 5;
	int x = (COLS - width) / 2; // Center the object horizontally
	int y = (LINES - height) / 2; // Center the object vertically

	---------NavePlayer nave(57, 25);
	Bullets bullet(57, 25.3,2);


	int ch = 0; // To store user input
	
	while (ch != 'q') {
		clear(); // Clear the screen
		//enemyGroup.moveAllEnemies();
		
		enemyGroup.drawAllEnemies();	
		enemyGroup.moveAllEnemies();
		bullet.moveBullet(ch);
		bullet.draw();
		---------nave.draw();
		
		------refresh(); // Refresh the screen
		--------ch = getch(); // Get user input
		// Check user input and update object position
		---------nave.movementPlayer(ch);
	}
	//enemyThread.join();*/
	Game Jogo;
	Jogo.run();
	endwin(); // End the curses library
	return 0;
}
