#include "GameStatus.h"
#include <curses.h>
#include <string>
using namespace std;

int GameStatus::GameScore = 0;
int GameStatus::LivesPlayer = 10;
int GameStatus::xMax = 0;
int GameStatus::yMax = 0;
GameStatus::GameStatus() {}

int GameStatus::Score() {	
	return GameScore;
}

int GameStatus::LivesP() {
	return LivesPlayer;
}

GameStatusUI::GameStatusUI():GameStatus(){}

void GameStatusUI::GameWindow() {
	getmaxyx(stdscr, yMax, xMax);
}

void GameStatusUI::UpdateInfoScreen(){
	mvprintw(1, 1, "GAMESCORE: ");
	mvprintw(1, 12, to_string(GameScore).c_str());
	mvprintw(1, 18, "LIVES: ");
	mvprintw(1, 25, to_string(LivesPlayer).c_str());
	mvprintw(1, 30, "PLAYER: ");
}