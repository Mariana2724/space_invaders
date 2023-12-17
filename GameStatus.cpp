#include "GameStatus.h"
#include "Game.h"
#include <iostream>
#include <exception>
#include <stdexcept>
#include <fstream>
#include <algorithm>

#include <curses.h>
#include <string>
#include<cstdio>
using namespace std;

int GameStatus::GameScore = 0;
int GameStatus::LivesPlayer = 3;
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

int GameStatusUI::ScoreListShow() {
	GameWindow();
	curs_set(0);
	OrganizeScore();
	bool newW = true;
	int ch;
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	while (newW) {
		
		int i = 2;
		WINDOW* show = newwin(yMax / 4 + 6, xMax / 4+2, yMax / 2-2, xMax / 2 - 16);
		wattron(show,COLOR_PAIR(1));
		wmove(show, 2, 2);
		mvwprintw(show, 1, 1, "POS.	     PLAYER      SCORE");
		mvwprintw(show, 11, 7, "PRESS ENTER TO LEAVE");
		wattroff(show,COLOR_PAIR(1));
		box(show, 0, 0);
		for (int a = 2; a < 9; a++) {
			mvwprintw(show, a+1, 2, to_string(a-1).c_str());
			mvwprintw(show, a + 1, 14, "---");
			mvwprintw(show, a + 1, 26, "---");
		}

		ifstream IScoreTable("Score.txt", ios::in);
		if (!IScoreTable.is_open()) {
			throw runtime_error("not open");
		}
		else {
			int score;
			string nom;
			while (IScoreTable >> nom >> score && i < 9) {
				mvwprintw(show, i + 1, 14, "    ");
				mvwprintw(show, i + 1, 26, "    ");
				mvwprintw(show, i + 1, 14, nom.c_str());
				mvwprintw(show, i + 1, 26, to_string(score).c_str());

				i++;
			}
		}

		IScoreTable.close();
		ch = wgetch(show);
		wrefresh(show);
		keypad(show, true);

		if (ch == 10) {
			wborder(show, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // Erase frame around the window
			newW = false;
			werase(show);
			wrefresh(show);
			delwin(show);
			break;
		}

		wrefresh(show);
		keypad(show, true);
	}
	dados.clear();
	endwin();
	Game::GameState = 0;
	return 0;
}
bool compararEmOrdemDecrescente(const PlayerData& a, const PlayerData& b) {
	return a.UserScore > b.UserScore;
}
void GameStatus::OrganizeScore() {
	ifstream IScoreTable("Score.txt", ios::in);
	if (!IScoreTable.is_open()) {
		throw runtime_error("not open");
	}
	else {
		int score;
		string nom;
		while (IScoreTable >> nom >> score) {
			PlayerData player;
			player.UserScore = score;
			player.UserName = nom;
			dados.push_back(player);
		}
	}
	IScoreTable.close();

	sort(dados.begin(), dados.end(), compararEmOrdemDecrescente);

	ofstream OScoreTable("Score.txt", ios::trunc);
	/*arquivo.close();
	
	ofstream OScoreTable("Score.txt", ios::app);*/
	if (!OScoreTable.is_open()) {
		throw runtime_error("not open");
	}
	else {
		for (const auto& dado : dados)
			OScoreTable << dado.UserName << "\t" << dado.UserScore<<endl;
	}
	dados.clear();
	OScoreTable.close();
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