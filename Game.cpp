#include<iostream>
#include "Game.h"
#include <curses.h>
#include "NavePlayer.h"
#include "Enemies.h"
#include "Bullets.h"
#include "Barrier.h"
#include <list>
#include<string>
#include <chrono>
#include<thread>
using namespace std;

int Game::GameScore = 0;
int Game::LivesPlayer = 10;
int Game::SpaceShip = 0;
int Game::GameState = 0;

Game::Game() {
	run_Game = true;
}

void Game::start(void){
	initscr(); // Initialize the curses library
	noecho(); // Don't echo user input to the screen
	cbreak(); // Disable line buffering
	bool isRunning = true;
	while (isRunning) {
		switch (GameState) {
		case 0:
			menu();
			break;
		case 1:
			run();
			break;
		default:
			isRunning = false;
			break;
		}
	}
	endwin();
}

int Game::menu(void) {
	int xMax, yMax;
	getmaxyx(stdscr, yMax, xMax);
	start_color();

	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	

	// COLOCAR  attron(COLOR_PAIR(1)); NO INICIO E attroff(COLOR_PAIR(1)); NO FIM
	// PARA USAR A COR 1 NESSE INTERVALO

	attron(COLOR_PAIR(1));
	mvprintw(5, 15, "  _________                           .___                         .___                   ");
	mvprintw(6, 15, " /   _____/__________    ____  ____   |   | _______  _______     __| _/___________  ______");
	mvprintw(7, 15, " \\_____  \\____ \\__  \\ _/ ___\\/ __ \\   |   |/    \\  \\/ /\\__  \\   / __ |/ __ \\_  __ \\/  ___/");
	mvprintw(8, 15, " /        \\  |_> > __ \\\\  \\__\\  ___/  |   |   |  \\   /  / __ \\_/ /_/ \\  ___/|  | \\/\\___ \\ ");
	mvprintw(9, 15, "/_______  /   __(____  /\\___  >___  > |___|___|  /\\_/  (____  /\\____ |\\___  >__|  /____  >");
	mvprintw(10, 15, "        \\/|__|       \\/     \\/    \\/           \\/           \\/      \\/    \\/           \\/ ");
	attroff(COLOR_PAIR(1));

	//WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);

	WINDOW* menu_win = newwin(yMax / 4, xMax / 4, yMax / 2, xMax / 2 - 15);
	box(menu_win, 4, 0);
	refresh();
	wrefresh(menu_win);
	keypad(menu_win, true);

	string UserChoice[3] = { "PLAY", "CHOOSE SPACESHIP","EXIT" };
	int choice;
	int highlight = 0;
//Para as opções do menu
	while (run_Game) {
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
			if (highlight == -1)
				highlight = 0;
			break;
		case KEY_DOWN:
			highlight++;
			if (highlight == 3)
				highlight = 2;
			break;
		case 10:
			if (highlight == 0) {
				refresh();
				wrefresh(menu_win);
				wclear(menu_win);
				delwin(menu_win);
				GameState = 1;
				return 0;
			}
			else if (highlight == 1) {
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

					while (true) {
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
							break;
						}
					}

				}

			}
			else {
				run_Game = false;
				GameState = -1;
				return 0;
				//endwin();
				break;
			}
		default:
			break;
		}
	}
	run_Game = true;
	endwin();
}
int Game::run(void) {
	nodelay(stdscr, true);    // Configurar o terminal para o modo sem espera por entrada
	keypad(stdscr, TRUE); // Enable special keys
	int ch = 0;
	NavePlayerUI nave(57, 25,2);
	list<EnemiesUI*> enemies;
	list<BulletsUI*> bullets;
	list<BarrierUI*> barriers;
	for (int i = 0; i < 4; i++) {
		barriers.emplace_back(new BarrierUI(10+i*30,21));
	}
	for (int i = 0; i < 5; ++i) {
		enemies.emplace_back(new EnemiesUI(i * 7, 7, 5, 1));
	}
	for (int i = 0; i < 7; i++) {
		enemies.emplace_back(new EnemiesUI(i * 5, 5, 5, 2));
	}
	for (int i = 0; i < 7; i++) {
		enemies.emplace_back(new EnemiesUI(i * 5, 9, 5, 3));
	}
	enemies.emplace_back(new EnemiesUI(1, 1, 2, 4));
	
while (run_Game && ch!='q') { //flag
		clear();
		nave.draw();
		for (BarrierUI* barrier : barriers) {
			barrier->draw();
		}
		for (EnemiesUI* enemy : enemies) {
			enemy->draw();
			enemy->movement();
		}
		for (BulletsUI* bullet : bullets) {
			bullet->draw();
			bullet->moveBullet();
		}
		for (auto it = bullets.begin(); it != bullets.end(); ) {
			if ((*it)->checkCollisionEnemies(enemies)) {
				it = bullets.erase(it);
			}else {
				++it;
			}
			enemies.erase(remove_if(enemies.begin(), enemies.end(), [](EnemiesUI* enemy) { return enemy->collided; }), enemies.end());
		}
		int key = getch();
		if (key != ERR) {
			ch = key;
			nave.movementPlayer(ch);
			if (ch == 32) {
				bullets.emplace_back(new BulletsUI(nave.Getx()+1, nave.Gety(), 2)); // Criar uma nova bala na posição da nave
			}
		}
		noecho();
		refresh();
		this_thread::sleep_for(chrono::milliseconds(20));
	}
	GameState = 0;
	clear();
	endwin();

	return 0;
}

int Game::LivesP() {
	return LivesPlayer;
}
int Game::Score() {
	return GameScore;
}
