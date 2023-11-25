#include <stdio.h>
#include<iostream>
#include <curses.h>
#include <exception>
#include <stdexcept>
using namespace std;

void initGame() {
		initscr(); // Initialize the curses library
		noecho(); // Don't echo user input to the screen
		cbreak(); // Disable line buffering
		keypad(stdscr, TRUE); // Enable special keys
		//timeout(100);
}