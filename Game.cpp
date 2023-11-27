#include<iostream>
#include "Game.h"
#include <curses.h>
#include "NavePlayer.h"
#include "Enemies.h"
#include <list>
using namespace std;
int Game::GameScore = 0;
int Game::LivesPlayer = 10;

Game::Game() {
	run_Game = true;
}
void Game::run(void) {
	initscr(); // Initialize the curses library
	noecho(); // Don't echo user input to the screen
	cbreak(); // Disable line buffering
	keypad(stdscr, TRUE); // Enable special keys
	//timeout(100);
	int ch = 0;
	NavePlayer nave(57, 25);
	list<Enemy_4*> enemyGroup;
	enemyGroup.push_back(new Enemy_4(0, 2, 1));
	
	while (run_Game && ch!='q') { //flag
		clear();
		nave.draw();
		for (auto it : enemyGroup) {
			it->draw();
		}
		ch = getch();//n acrescentar timeout; ver se retorna algo
		for (auto it : enemyGroup) {
			it->movement();
		}
		//enemyGroup.moveAllEnemies();
		nave.movementPlayer(ch);
		refresh();
	}

}

int Game::LivesP() {
	return LivesPlayer;
}
int Game::Score() {
	return GameScore;
}