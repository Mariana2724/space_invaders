#include "NavePlayer.h"
#include "Game.h"
#include <iostream>
#include <curses.h>
using namespace std;

NavePlayer::NavePlayer(): Ship(){}
NavePlayer::NavePlayer(int x, int y) : Ship(x, y) {}
NavePlayer::NavePlayer(int x, int y, int speed) : Ship(x, y, speed) {}
void NavePlayer::movementPlayer(int key) {
    switch (key) {
    case KEY_LEFT:
        moveLeft(); // movimento para a esquerda
        break;
    case KEY_RIGHT:
        moveRight(); // movimento para a direita
        break;
        // Adiciona mais casos conforme necessário para outras teclas
    }
}
NavePlayerUI::NavePlayerUI(int x, int y, int speed) :NavePlayer(x, y, speed) {}
void NavePlayerUI::draw()  { //override??
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    switch (Game::SpaceShip) {
    case 0:
        mvprintw(getY(), getX(), "  /\\  ");
        mvprintw(getY() + 1, getX(), " |==| ");
        mvprintw(getY() + 2, getX(), "  \\/  ");
        break;
    case 1:
        attron(COLOR_PAIR(1));
        mvprintw(getY(), getX(), "  \\/  ");
        mvprintw(getY() + 1, getX(), "  /\\ ");
        mvprintw(getY() + 2, getX(), "  \\/  ");
        attroff(COLOR_PAIR(1));
        break;
    case 2:
        attron(COLOR_PAIR(2));
        mvprintw(getY(), getX(), " \\|/  ");
        mvprintw(getY() + 1, getX(), " ||| ");
        mvprintw(getY() + 2, getX(), " /|\\  ");
        attroff(COLOR_PAIR(2));
        break;
    default: 
        mvprintw(getY(), getX(), "  /\\  ");
        mvprintw(getY() + 1, getX(), " |==| ");
        mvprintw(getY() + 2, getX(), "  \\/  ");
        break;
    }
   

    refresh(); // Atualiza o ecrã
}
