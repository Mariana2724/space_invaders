#include "NavePlayer.h"
#include <iostream>
#include <curses.h>
using namespace std;

NavePlayer::NavePlayer(): Ship(){
   // ships.push_back(this);
}
NavePlayer::NavePlayer(int x, int y) : Ship(x, y) {
}
NavePlayer::NavePlayer(int x, int y, int speed) : Ship(x, y, speed) {
}
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
void NavePlayer::draw()  { //override??
    // Limpa a posição anterior
    mvprintw(Gety(), Getx(), "     "); // Apaga o que está na posição atual

    // Desenha a nave do jogador na nova posição
    mvprintw(Gety(), Getx(), "  /\\  "); // Exemplo de desenho da nave (podemos ajustar isto)
    mvprintw(Gety() + 1, Getx(), " |==| ");
    mvprintw(Gety() + 2, Getx(), "  \\/  ");

    refresh(); // Atualiza o ecrã
}
