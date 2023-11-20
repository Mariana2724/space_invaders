#include <stdio.h>
#include<iostream>
#include <curses.h>
#include <exception>
#include <stdexcept>
using namespace std;
#include "Game.h"
#include "Naveplayer.h"

void initGame();
int main() {
	initGame();
	 
	int height = 10;
	int width = 20;
	int x = (COLS - width) / 2; // Center the object horizontally
	int y = (LINES - height) / 2; // Center the object vertically
	NavePlayer n(x, y);
	int ch = 0; // To store user input
	while (ch != 'q') {
		clear(); // Clear the screen
		mvprintw(y, x, "X"); // Print the object at the current position
		refresh(); // Refresh the screen
		ch = getch(); // Get user input
		// Check user input and update object position
		switch (ch) {
		case KEY_UP:
			if (y > 0) y--;
			break;
		case KEY_DOWN:
			if (y < LINES - 1) y++;
			break;
		case KEY_LEFT:
			if (x > 0) x--;
			break;
		case KEY_RIGHT:
			if (x < COLS - 1) x++;
			break;
		}
	}
	endwin(); // End the curses library
	return 0;
}
/*
void initGame() {
	try {
		initscr(); // Initialize the curses library
		noecho(); // Don't echo user input to the screen
		cbreak(); // Disable line buffering
		keypad(stdscr, TRUE); // Enable special keys
		throw runtime_error("Failed to initialize");
	}
	catch (runtime_error& e) {
		cout << e.what();
	}
}*/