#include<iostream>
#include "Game.h"
#include <curses.h>
#include "NavePlayer.h"
#include "Enemies.h"
#include "Bullets.h"
#include "Barrier.h"
#include "GameStatus.h"
#include "Strategy.h"

#include <list>
#include<string>
#include <chrono>
#include<thread>

using namespace std;


int Game::SpaceShip = 0;
int Game::GameState = 0;
string name[20]; // Buffer para armazenar o nome
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
	GameScore = 0;
	LivesPlayer = 10;
	GameName();
	//WINDOW *newwin(int nlines, int ncols, int begin_y, int begin_x);
	WINDOW* menu_win = newwin(yMax / 4, xMax / 4, yMax / 2, xMax / 2 - 15);
	box(menu_win, 4, 0);
	refresh();
	wrefresh(menu_win);
	keypad(menu_win, true);

	string UserChoice[3] = { "PLAY", "CHOOSE SPACESHIP","EXIT" };
	int choice;
	int highlight = 0;

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
				GameState = 4;
				run_Game = false;
			}
			else if (highlight == 1) {
				GameState = 1;
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

		int ch;
	
		mvwprintw(insert, 2, 7, "YOUR NAME: ");
		mvwprintw(insert, 3, 3, "->");
		
		char a;
		int x = 0;

		for (int i = 0; i < 20; i++) {
			name[i] = ' ';
		}

		while (true) {
			ch = wgetch(insert);
			if ((ch >= 65 && ch <= 122) || ch == 10||ch==8){
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
					break;
				}
				x++;
			}
        }
		newW = false;
		wrefresh(insert); // Atualiza a janela após o término do loop de entrada do nome
		wclear(insert);
		delwin(insert);
    }
	endwin();
	GameState = 2;
	
	return 0;
}



int Game::run(void) {
	nodelay(stdscr, true);    // Configurar o terminal para o modo sem espera por entrada
	keypad(stdscr, TRUE); // Enable special keys
	
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	
	/*Strategy objects;
	Shapes* nave = new NavePlayerUI(57, 25, 2);
	objects.add(nave);
*/
	NavePlayerUI nave(57, 25,2);
	list<EnemiesUI*> enemies;
	list<BulletsUI*> bulletsNave;
	list<BulletsUI*> bulletsEnemy;
	list<BarrierUI*> barriers;

	int ch = 0;
	int keep = 0;

	for (int i = 0; i < 4; i++) {
		barriers.emplace_back(new BarrierUI(10+i*30,21));
	}
	for (int i = 1; i < 6; i++) {
		enemies.emplace_back(new EnemiesUI(i * 7, 5, 5, 2));
	}
	for (int i = 1; i < 6; i++) {
		enemies.emplace_back(new EnemiesUI(i * 7, 7, 5, 1));
	}
	for (int i = 1; i < 7; i++) {
		enemies.emplace_back(new EnemiesUI(i * 6, 9, 5, 3));
	}
	enemies.emplace_back(new EnemiesUI(0, 11, 5, 5));
	enemies.emplace_back(new EnemiesUI(1, 3, 2, 4));
	refresh();
	ch = getch();

while (run_Game ) { //flag
		clear();
		UpdateInfoScreen();
		for (int i = 0; i < 20; i++) {
			mvprintw(1, 38+i, name[i].c_str());
		}
		if (LivesPlayer == 9) {
			GameState = 3;
			run_Game = false;
		}
		nave.draw();
		//refresh();
		for (BarrierUI* barrier : barriers) {
			barrier->draw();
		}
		for (EnemiesUI* enemy : enemies) {
			enemy->draw();
			enemy->movement();
			//enemy->shoot(bulletsEnemy);
			if (rand() % 300 < 0.5) {			
				bulletsEnemy.emplace_back(new BulletsUI(enemy->getX(), enemy->getY(),2,2));
			}
		}
		refresh();
		for (BulletsUI* bulletNave : bulletsNave) {
			bulletNave->draw();
			bulletNave->movement();
		}
		//refresh();
		for (BulletsUI* bulletEnemy : bulletsEnemy) {
			bulletEnemy->draw();
			bulletEnemy->movement();
		}
		//refresh();
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
		//refresh();
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
		//refresh();
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
		//refresh();
		ch = getch();
		flushinp();
		if (ch != ERR) {
			nave.movementPlayer(ch);
			if (ch == 32) {
				bulletsNave.emplace_back(new BulletsUI(nave.getX()+1, nave.getY(), 2,1)); // Criar uma nova bala na posição da nave
			}
		}
		//refresh();
		if (ch == 'p') {
			if (GameIsPaused()) {// se for 1
				continue;
			}
			else {
				GameState = 0;
				break;
			}
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

	GameState = 0;
	return 0;
}
bool Game::GameIsPaused() {
	//if (ch == 'p') {
		GameWindow();
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

			while (true) {
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
					if (PauseHighlight == 0) {
						wborder(pause, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // Erase frame around the window
						newW = false;
						werase(pause);
						wrefresh(pause);
						delwin(pause);
						endwin();
						return 1;
						break;
					}
					else if (PauseHighlight == 1) {
						wborder(pause, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // Erase frame around the window
						newW = false;
						clear();
						werase(pause);
						wrefresh(pause);
						delwin(pause);
						endwin();
						return 0;
					}

				}
			}

		}
	//}
}
int Game::GameIsOver(void) {
	GameWindow();
	bool newW = true;
	int PauseHighlight = 0;
	while (newW) {
		WINDOW* pause = newwin(yMax / 4 - 2, xMax / 4 - 3, yMax / 2 -5, xMax / 2 - 13);
		box(pause, 0, 0);

		wrefresh(pause);
		keypad(pause, true);

		string OptionPause[2] = { "  MENU  ", "EXIT GAME" };
		int ch;


		mvwprintw(pause, 1, 7, "YOU HAVE DIED !!!");

		while (true) {
			for (int i = 0; i < 2; i++) {
				if (i == PauseHighlight) {
					wattron(pause, A_REVERSE);
				}
				mvwprintw(pause, i + 2, 10-i, OptionPause[i].c_str());
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
				if (PauseHighlight == 0) {
					GameState = 0;
					wborder(pause, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // Erase frame around the window
					newW = false;
					clear();
					werase(pause);
					wrefresh(pause);
					delwin(pause);
					endwin();
					return 0;
					break;
				}
				else if (PauseHighlight == 1) {
					GameState = -1;
					wborder(pause, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // Erase frame around the window
					newW = false;
					clear();
					werase(pause);
					wrefresh(pause);
					delwin(pause);
					endwin();
					return 0;
				}

			}
		}

	}
}