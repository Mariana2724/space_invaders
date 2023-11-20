#include<iostream>
#include "Game.h"


int Game::GameScore = 0;
int Game::LivesPlayer = 10;

int Game::LivesP() {
	return LivesPlayer;
}
int Game::Score() {
	return GameScore;
}