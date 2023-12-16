#include "GameStatus.h"
#include "Game.h"
#include <iostream>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <curses.h>
#include <string>
using namespace std;

int GameStatus::GameScore = 0;
int GameStatus::LivesPlayer = 10;
int GameStatus::xMax = 0;
int GameStatus::yMax = 0;
char GameStatus::name[20] = {};
GameStatus::GameStatus() {}

int GameStatus::Score() {	
	return GameScore;
}

int GameStatus::LivesP() {
	return LivesPlayer;
}

void GameStatus::ScoreListInsert() {
	
	size_t originalSize = sizeof(name) / sizeof(name[0]);

	// Inicializa um índice para o novo array
	size_t newIndex = 0;

	// Modifica o array removendo espaços em branco
	for (size_t i = 0; i < originalSize; ++i) {
		if (!isspace(name[i])) {
			name[newIndex++] = name[i];
		}
	}
	name[newIndex] = '\0';

	string nome (name);
	ofstream OScoreTable("Score.txt", ios::app);
	if (!OScoreTable.is_open()) {
		throw runtime_error("not open");
	}
	else {
		OScoreTable << nome <<"\t"<<GameScore << endl;
	}
	OScoreTable.close();

}

void GameStatusUI::ScoreListShow() {
	GameWindow();
	bool newW = true;

	while (newW) {
		WINDOW* insert = newwin(yMax / 4, xMax / 4 - 3, yMax / 2 - 5, xMax / 2 - 13);
		box(insert, 4, 0);

	ifstream IScoreTable("Score.txt", ios::in);
	if (!IScoreTable.is_open()) {
		throw runtime_error("not open");
	}
	else {
		int score;
		string nom;
		while (!IScoreTable.eof()) {
			IScoreTable >> nom >> score;
			//cout << nom << score<<endl;
		}
	}
	IScoreTable.close();
	//newW = false;
	}
	endwin();
	Game::GameState = 0;
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