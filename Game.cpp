#include<iostream>
#include "Game.h"
#include <curses.h>
#include "NavePlayer.h"
#include "Enemies.h"
#include "Bullets.h"
#include "Barrier.h"
#include "GameStatus.h"


#include <vector>
#include <list>
#include <exception>
#include <stdexcept>
#include <fstream>
#include<string>
#include <chrono>
#include<thread>

using namespace std;


int Game::SpaceShip = 0;
int Game::GameState = 0;

Game::Game() {
	run_Game = true;
}

void Game::start(void){
	initscr(); 
	noecho(); 
	cbreak(); 

	bool isRunning = true;
	while (isRunning) {
		switch (GameState) {
		case 0:
			menu();
			break;
		case 1:
			ChooseSpaceship();
			break;
		case 2:
			run();
			break;
		case 3:
			GameIsOver();
			break;
		case 4:
			InsertName();
			break;
		case 5:
			ScoreListShow();
			break;
		case 6:
			WinGame();
			break;
		default:
			isRunning = false;
			break;
		}
	}
	endwin();
}
void Game::GameName(void) {
	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvprintw(5, 15, "  _________                           .___                         .___                   ");
	mvprintw(6, 15, " /   _____/__________    ____  ____   |   | _______  _______     __| _/___________  ______");
	mvprintw(7, 15, " \\_____  \\____ \\__  \\ _/ ___\\/ __ \\   |   |/    \\  \\/ /\\__  \\   / __ |/ __ \\_  __ \\/  ___/");
	mvprintw(8, 15, " /        \\  |_> > __ \\\\  \\__\\  ___/  |   |   |  \\   /  / __ \\_/ /_/ \\  ___/|  | \\/\\___ \\ ");
	mvprintw(9, 15, "/_______  /   __(____  /\\___  >___  > |___|___|  /\\_/  (____  /\\____ |\\___  >__|  /____  >");
	mvprintw(10, 15, "        \\/|__|       \\/     \\/    \\/           \\/           \\/      \\/    \\/           \\/ ");
	attroff(COLOR_PAIR(1));

}
int Game::menu(void) {
	GameWindow();
	curs_set(0);
	GameScore = 0;
	LivesPlayer = 3;
	GameStatus::Level = 1;
	GameName();
	WINDOW* menu_win = newwin(yMax / 4+1, xMax / 4, yMax / 2, xMax / 2 - 15);
	box(menu_win, 4, 0);
	refresh();
	wrefresh(menu_win);
	keypad(menu_win, true);

	string UserChoice[4] = { "PLAY", "CHOOSE SPACESHIP","SCORETABLE","EXIT" };
	int choice;
	int highlight = 0;

	while (run_Game) {
		for (int i = 0; i < 4; i++) {
			if (i == highlight) {
				wattron(menu_win, A_REVERSE);
			}
			if (i == 1) {
				mvwprintw(menu_win, i + 2, 7, UserChoice[i].c_str());
			}
			else if(i==2){
				mvwprintw(menu_win, i + 2, 10, UserChoice[i].c_str());
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
			if (highlight == -1)
				highlight = 0;
			break;
		case KEY_DOWN:
			highlight++;
			if (highlight == 4)
				highlight = 3;
			break;
		case 10:
			if (highlight == 0) {
				refresh();
				wrefresh(menu_win);
				wclear(menu_win);
				delwin(menu_win);
				GameState = 4;
				run_Game = false;
			}
			else if (highlight == 1) {
				GameState = 1;
				run_Game = false;
			}
			else if (highlight==2) {
				GameState = 5;
				run_Game = false;
			}
			else {
				run_Game = false;
				GameState = -1;
			}
		default:
			break;
		}
	}
	run_Game = true;
	endwin();
	return 0;
}
int Game::InsertName() {
	GameWindow();
	bool newW = true;

	while (newW) {
		WINDOW* insert = newwin(yMax / 4 - 2, xMax / 4 - 3, yMax / 2 - 5, xMax / 2 - 13);
		mvwprintw(insert, 0, 0, "_________________________");
		mvwprintw(insert, 4, 0, "_________________________");

		wrefresh(insert);
		keypad(insert, true);

		int ch, x = 0;;
	
		mvwprintw(insert, 2, 7, "YOUR NAME: ");
		mvwprintw(insert, 3, 2, "-> ");

		for (int i = 0; i < 20; i++) {
			name[i] = ' ';
		}

		while (true) {
			ch = wgetch(insert);
			if ((ch >= 65 && ch <= 122) || ch == 10||ch==8||ch==27){
				wattron(insert, A_REVERSE);
				waddch(insert, ch);
				name[x]=ch;
				if (ch == 8) {
					wdelch(insert);
					x--;
					name[x] = ' ';
					x--;
				}
				
				wattroff(insert, A_REVERSE);
				if (ch == 10) {
					GameState = 2;
					break;
				}
				if (ch == 27) {
					GameState = 0;
					break;
				}
				x++;
			}
        }
		newW = false;
		werase(insert);
		wrefresh(insert); 
		wclear(insert);
		delwin(insert);
    }
	endwin();
	return 0;
}

int Game::run() {
	nodelay(stdscr, true); 
	keypad(stdscr, TRUE); 
	curs_set(0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	LivesPlayer = 3;
	NavePlayerUI nave(57, 25);
	list<EnemiesUI*> enemies;
	list<BulletsUI*> bulletsNave;
	list<BulletsUI*> bulletsEnemy;
	list<BarrierUI*> barriers;

	int ch = 0;
	int keep = 0;

	for (int i = 0; i < 4; i++) {
		barriers.emplace_back(new BarrierUI(10+i*30,21));
	}
	for (int i = 1; i < (5 + GameStatus::Level); i++) {
		enemies.emplace_back(new EnemiesUI(i * 7, 5, 2));
		enemies.emplace_back(new EnemiesUI(i * 7, 7, 1));
	}
	for (int i = 1; i < (6 + GameStatus::Level); i++) {
		enemies.emplace_back(new EnemiesUI(i * 6, 9, 3));
	}
	enemies.emplace_back(new EnemiesUI(0, 11, 5));
	enemies.emplace_back(new EnemiesUI(1, 3, 4));
	refresh();
	ch = getch();
	run_Game = true;
while (run_Game) {
		clear();
		UpdateInfoScreen();

		if (LivesPlayer == 0) {
			GameState = 3;
			run_Game = false;
		}
		nave.draw();
		for (BarrierUI* barrier : barriers) {
			barrier->draw();
		}
		for (EnemiesUI* enemy : enemies) {
			enemy->draw();
			enemy->movement();
			if (rand() % 300 < GameStatus::Level+0.1) {			
				bulletsEnemy.emplace_back(new BulletsUI(enemy->getX(), enemy->getY(),2));
			}
		}
		for (BulletsUI* bulletNave : bulletsNave) {
			bulletNave->draw();
			bulletNave->movement();
		}
		for (BulletsUI* bulletEnemy : bulletsEnemy) {
			bulletEnemy->draw();
			bulletEnemy->movement();
		}
		for (auto it = bulletsNave.begin(); it != bulletsNave.end(); ) {
			keep = (*it)->checkCollisionEnemies(enemies);
			if (keep==1) {
				it = bulletsNave.erase(it);
			}
			else {
				++it;
			}
			for (auto it = enemies.begin(); it != enemies.end(); ++it) {
				if ((*it)->collided) {
					(*it)->collided = false;
					it = enemies.erase(it);
					break;
				}
			}
		}
		for (auto it = bulletsNave.begin(); it != bulletsNave.end(); ) {
			keep = (*it)->checkCollisionBarriers(barriers);
			if (keep==1) {
				it = bulletsNave.erase(it);
			}
			else if(keep==2) {
				++it;
			}
			else if (keep == 0) {
				it = bulletsNave.erase(it);
				for (auto it = barriers.begin(); it != barriers.end(); ++it) {
					if ((*it)->collidedB) {
						(*it)->collidedB = false;
						it=barriers.erase(it);
						break;
					}
				}
			}
		}	
		for (auto it = bulletsEnemy.begin(); it != bulletsEnemy.end(); ) {
			keep = (*it)->checkCollisionBarriers(barriers);
			if (keep == 1|| (*it)->checkCollisionNave(nave)) {
				it = bulletsEnemy.erase(it);
			}
			else if (keep == 2) {
				++it;
			}
			else if (keep == 0) {
				for (auto it = barriers.begin(); it != barriers.end(); ++it) {
					if ((*it)->collidedB) {
						(*it)->collidedB = false;
						it=barriers.erase(it);
						break;
					}
				}
			}

		}
		ch = getch();
		flushinp();
		if (ch != ERR) {
			nave.movementPlayer(ch);
			if (ch == 32) {
				bulletsNave.emplace_back(new BulletsUI(nave.getX()+1, nave.getY(),1)); // Criar uma nova bala na posição da nave
			}
		}
		if (ch == 'p') {
			if (GameIsPaused()) {
				continue;
			}
			else {
				GameState = 0;
				run_Game = false;
			}
		}
		if (isOver()) {
			GameState = 6;
			run_Game = false;
		}
		noecho();
		refresh();
		this_thread::sleep_for(chrono::milliseconds(40));
	}
  	clear();
	endwin();
	return 0;
}

int Game::ChooseSpaceship() {
	GameWindow();
	curs_set(0);
	bool newW = true;
	while (newW) {
		WINDOW* space = newwin(yMax / 4, xMax / 4, yMax / 2 + 6, xMax / 2 + 20);
		box(space, 0, 0);

		mvwprintw(space, 1, 1, "  /\\  "); // Exemplo de desenho da nave (podemos ajustar isto)
		mvwprintw(space, 2, 1, " |==| ");
		mvwprintw(space, 3, 1, "  \\/  ");
		mvwprintw(space, 1, 11, "  \\/  ");
		mvwprintw(space, 2, 11, "  /\\ ");
		mvwprintw(space, 3, 11, "  \\/  ");
		mvwprintw(space, 1, 21, "  \\|/  ");
		mvwprintw(space, 2, 21, "  ||| ");
		mvwprintw(space, 3, 21, "  /|\\  ");
		wrefresh(space);
		keypad(space, true);

		string ChooseSpaceShip[3] = { "(1)", "(2)", "(3)" };
		int ch;
		int SpaceHighlight = 0;
		int a = 1;
		bool choose = true;
		while (choose) {
			for (int i = 0; i < 3; i++) {
				if (i == SpaceHighlight) {
					wattron(space, A_REVERSE);
				}
				mvwprintw(space, 5, a, ChooseSpaceShip[i].c_str());
				a += 10;
				wattroff(space, A_REVERSE);
			}

			ch = wgetch(space);
			switch (ch) {
			case KEY_LEFT:
				SpaceHighlight--;
				if (SpaceHighlight == -1) {
					SpaceHighlight = 0;
				}
				break;
			case KEY_RIGHT:
				SpaceHighlight++;
				if (SpaceHighlight == 3) {
					SpaceHighlight = 2;
				}
				break;
			default:
				break;
			}
			a = 1;

			wrefresh(space);
			if (ch == 10) {
				SpaceShip = SpaceHighlight;
				wborder(space, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // Erase frame around the window
				newW = false;
				werase(space);
				wrefresh(space);
				delwin(space);
				endwin();
				choose = false;
			}
		}

	}
	GameState = 0;
	return 0;
}
bool Game::GameIsPaused() {
	GameWindow();
	curs_set(0);
	bool newW = true;
	int PauseHighlight = 0;
	while (newW) {
		WINDOW* pause = newwin(yMax / 4 - 2, xMax / 4 - 3, yMax / 2 - 15, xMax / 2 - 13);
		box(pause, 0, 0);
		wrefresh(pause);
		keypad(pause, true);
		string OptionPause[2] = { "RESUME", " QUIT " };
		int ch;
		mvwprintw(pause, 1, 7, "GAME IS PAUSED");
		bool isPaused = true;
		while (isPaused) {
			for (int i = 0; i < 2; i++) {
				if (i == PauseHighlight) {
					wattron(pause, A_REVERSE);
				}
				mvwprintw(pause, i + 2, 10, OptionPause[i].c_str());
				wattroff(pause, A_REVERSE);
			}
			ch = wgetch(pause);
			switch (ch) {
			case KEY_UP:
				PauseHighlight--;
				if (PauseHighlight == -1) {
					PauseHighlight = 0;
				}
				break;
			case KEY_DOWN:
				PauseHighlight++;
				if (PauseHighlight == 2) {
					PauseHighlight = 1;
				}
				break;
			default:
				break;
			}
			wrefresh(pause);
			if (ch == 10) {
				wborder(pause, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); 
				newW = false;
				werase(pause);
				wrefresh(pause);
				delwin(pause);
				endwin();
				if (PauseHighlight == 0)
					return 1;
				else if (PauseHighlight == 1) {
					ScoreListInsert();
					clear();
					return 0;
				}
			}
		}
	}
}
int Game::GameIsOver(void) {
	GameWindow();
	curs_set(0);
	bool newW = true;
	int OverHighlight = 0;
	while (newW) {
		WINDOW* over = newwin(yMax / 4 - 2, xMax / 4 - 3, yMax / 2 -5, xMax / 2 - 13);
		box(over, 0, 0);

		wrefresh(over);
		keypad(over, true);

		string OptionOver[2] = { "  MENU  ", "EXIT GAME" };
		int ch;

		mvwprintw(over, 1, 7, "YOU HAVE DIED !!!");
		bool gameOver = true;
		while (gameOver) {
			for (int i = 0; i < 2; i++) {
				if (i == OverHighlight) {
					wattron(over, A_REVERSE);
				}
				mvwprintw(over, i + 2, 10-i, OptionOver[i].c_str());
				wattroff(over, A_REVERSE);
			}

			ch = wgetch(over);
			switch (ch) {
			case KEY_UP:
				OverHighlight--;
				if (OverHighlight == -1) {
					OverHighlight = 0;
				}
				break;
			case KEY_DOWN:
				OverHighlight++;
				if (OverHighlight == 2) {
					OverHighlight = 1;
				}
				break;
			default:
				break;
			}

			wrefresh(over);
			if (ch == 10) {
				wborder(over, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				newW = false;
				clear();
				werase(over);
				wrefresh(over);
				delwin(over);
				endwin();
				gameOver = false;
				if (OverHighlight == 0) {
					GameState = 0;
				}
				else if (OverHighlight == 1) {
					GameState = -1;
				}

			}
		}

	}
	ScoreListInsert();
	return 0;
}
int Game::WinGame(void) {
	GameWindow();
	curs_set(0);
	bool newW = true;
	int WinHighlight = 0;
	while (newW) {
		WINDOW* win = newwin(yMax / 4 , xMax / 4 - 3, yMax / 2 - 5, xMax / 2 - 13);
		box(win, 0, 0);

		wrefresh(win);
		keypad(win, true);

		string OptionWin[3] = { " NEXT LEVEL ? ","    MENU  ", " EXIT GAME  " };
		int ch;

		if (GameStatus::Level < 3) {
			mvwprintw(win, 1, 5, "YOU WON LEVEL %d !!!", GameStatus::Level);
			WinHighlight = 0;
		}
		else {
			mvwprintw(win, 1, 5, "YOU WON THE GAME!!!");
			WinHighlight = 1;
		}
		bool flag = true;
		while (flag) {
			int i = 0;;

			if (GameStatus::Level < 3)
				i = 0;
			else 
				i = 1;
			for (i ; i < 3; i++) {
				if (i == WinHighlight) {
					wattron(win, A_REVERSE);
				}
				mvwprintw(win, i + 3, 8, OptionWin[i].c_str());
				wattroff(win, A_REVERSE);
			}

			ch = wgetch(win);
			switch (ch) {
			case KEY_UP:
				WinHighlight--;
				if (GameStatus::Level < 3) {
					if (WinHighlight == -1) {
						WinHighlight = 0;
					}
				}
				else {
					if (WinHighlight == 0) {
						WinHighlight = 1;
					}
				}
				break;
			case KEY_DOWN:
				WinHighlight++;
				if (WinHighlight == 3) {
					WinHighlight = 2;
				}
				break;
			default:
				break;
			}

			wrefresh(win);
			if (ch == 10) {
				newW = false;
				wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
				clear();
				werase(win);
				wrefresh(win);
				delwin(win);
				endwin();
				flag = false;
				if (WinHighlight == 0) {
					GameState = 2;
					if(GameStatus::Level<3)
						GameStatus::Level++;
				}
				else if (WinHighlight == 1) {
					GameState = 0;
					ScoreListInsert();
				}
				else if (WinHighlight == 2) {
					GameState = -1;
					ScoreListInsert();
				}
			}
		}
	}
	
	endwin();
	return 0;
}
