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
	 
	int height = 3;
	int width = 5;
	int x = (COLS - width) / 2; // Center the object horizontally
	int y = (LINES - height) / 2; // Center the object vertically
	NavePlayer nave(x, y);

	int ch = 0; // To store user input
	
	while (ch != 'q') {
		clear(); // Clear the screen
		nave.draw();
		refresh(); // Refresh the screen
		ch = getch(); // Get user input
		// Check user input and update object position
		nave.movementPlayer(ch);
	}
	endwin(); // End the curses library
	return 0;
}
