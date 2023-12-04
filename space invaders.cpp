#include <stdio.h>
#include<iostream>
#include <curses.h>
#include <thread>
#include <chrono>
#include <exception>
#include <stdexcept>
using namespace std;
#include "Game.h"
#include "Naveplayer.h"
#include "Ship.h"
#include "Enemies.h"
#include "Bullets.h"

int main() {

	Game myGame;
	myGame.start();

	return 0;
}
