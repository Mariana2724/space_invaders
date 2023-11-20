#include <stdio.h>
#include<iostream>
#include <curses.h>
#include <exception>
#include <stdexcept>
using namespace std;

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
}