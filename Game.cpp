#include<iostream>
#include "Game.h"
#include <curses.h>
#include "NavePlayer.h"
#include "Enemies.h"
#include <list>
#include<string>
using namespace std;
int Game::GameScore = 0;
int Game::LivesPlayer = 10;

Game::Game() {
	run_Game = true;
}

void Game::start(void){
	initscr(); // Initialize the curses library
	noecho(); // Don't echo user input to the screen
	cbreak(); // Disable line buffering
	int xMax, yMax;
	getmaxyx(stdscr, yMax, xMax);
	mvprintw(5, 15, "  _________                           .___                         .___                   ");
	mvprintw(6, 15, " /   _____/__________    ____  ____   |   | _______  _______     __| _/___________  ______");
	mvprintw(7, 15, " \\_____  \\____ \\__  \\ _/ ___\\/ __ \\   |   |/    \\  \\/ /\\__  \\   / __ |/ __ \\_  __ \\/  ___/");
	mvprintw(8, 15, " /        \\  |_> > __ \\\\  \\__\\  ___/  |   |   |  \\   /  / __ \\_/ /_/ \\  ___/|  | \\/\\___ \\ ");
	mvprintw(9, 15, "/_______  /   __(____  /\\___  >___  > |___|___|  /\\_/  (____  /\\____ |\\___  >__|  /____  >");
	mvprintw(10, 15, "        \\/|__|       \\/     \\/    \\/           \\/           \\/      \\/    \\/           \\/ ");

	//WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
	WINDOW* menu_win = newwin(yMax/4, xMax/4, yMax/2,xMax/2-15 );
	box(menu_win, 0, 0);
	refresh();
	wrefresh(menu_win);
	keypad(menu_win, true);
	
	string UserChoice[3] = {"PLAY", "CHOOSE SPACESHIP","EXIT"};
	int choice;
	int highlight = 0;
	while (1) {
		for (int i = 0; i < 3; i++) {
			if (i == highlight) {
				wattron(menu_win, A_REVERSE);
			}
			if (i == 1) {
				mvwprintw(menu_win, i + 2, 7, UserChoice[i].c_str());
			}
			else {
				mvwprintw(menu_win, i + 2, 13, UserChoice[i].c_str());
			}
			
			wattroff(menu_win, A_REVERSE);
		}
		choice = wgetch(menu_win);
		switch (choice) {
		case KEY_UP:
			highlight--;
			if (highlight == -1) {
				highlight = 0;
			}
			break;
		case KEY_DOWN:
			highlight++;
			if (highlight == 3) {
				highlight = 2;
			}
			break;
		default:
			break;

		}
		if (choice == 10) {
			if (highlight == 0) {
				refresh();
				wrefresh(menu_win);
				wclear(menu_win);
				delwin(menu_win);
				//endwin();
				
				run();
				break;
			}else if(highlight==1){
				WINDOW* space = newwin(yMax / 4, xMax / 4, yMax / 2+6, xMax / 2+20);
				box(space, 0, 0);
				refresh();
				wrefresh(space);
				keypad(space, true);
				int ch = wgetch(space);
				if (ch == 'q') {
					wborder(space, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // Erase frame around the window
					endwin();
					refresh();
					wrefresh(space);
				}
				//break;
			}
			else {
				break;
			}
			
		}
	}
	endwin();
}
void Game::run(void) {
/*	initscr(); // Initialize the curses library
	noecho(); // Don't echo user input to the screen
	cbreak(); // Disable line buffering*/

	keypad(stdscr, TRUE); // Enable special keys
	int ch = 0;
	NavePlayerUI nave(57, 25,2);
	list<Enemy_4*> enemyGroup;
	enemyGroup.push_back(new Enemy_4(0, 2, 1));
	
	while (run_Game && ch!='q') { //flag
		clear();
		nave.draw();
		for (auto it : enemyGroup) {
			it->draw();
		}
		if (ch==ERR) {
			for (auto it : enemyGroup) {
				it->movement();
			}
		}
		ch = getch();//n acrescentar timeout; ver se retorna algo
		
		noecho();
		

		nave.movementPlayer(ch);
		refresh();
	}
	clear();
	//cout << "saiu";
	endwin();

}

int Game::LivesP() {
	return LivesPlayer;
}
int Game::Score() {
	return GameScore;
}