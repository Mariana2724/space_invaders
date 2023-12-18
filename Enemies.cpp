#include "Enemies.h"
#include <curses.h> 
using namespace std;

int EnemiesUI::direction = 1;
Enemies::Enemies(int x, int y, int enemyType):Ship(x,y),enemyType(enemyType){
}
int Enemies::getEnemyType() {
    return enemyType;
}
EnemiesUI::EnemiesUI(int x, int y, int enemyType):Enemies(x,y,enemyType) {
   direction = 0;
}
int a = 0;
void Enemies::movement() {
    switch (enemyType) {
    case 1:
    case 2:
    case 3:
    case 5:
        if (direction == 0) { // Movimento para a direita
            moveRight();
            if (pos.x >= COLS - 10) { 
                pos.x = COLS - 10;
                direction = 1;
            }
        }
        else if (direction == 1) { // Movimento para baixo
            moveDown();
            if (pos.x == 0) {
                direction = 0;
            }
            else if (pos.x == COLS - 10) {
                direction = 2;
            }
            if (pos.y >= LINES - 10) { // Verifica se chegou ao limite inferior
                pos.y = LINES - 10; 
                direction = 3;
            }
        }
        else if (direction == 2) { // Movimento para a esquerda
            moveLeft();
            if (pos.x == 0) { 
                direction = 1; 
            }
        }
        else if (direction == 3) { //Movimento para cima
            moveUp();
            if (pos.x == 0) {
                direction = 5;
            }
            else if (pos.x == COLS - 10) {
                direction = 4;
            }
            if (pos.y <= 5) { // Verifica se chegou ao limite superior
                moveDown();
                moveRight();
                direction = 0;
            }
        }
        else if (direction == 4) {
            moveLeft();
            if (pos.x <= 0) { 
                pos.x = 0;
                direction = 3; 
            }
        }
        else if (direction == 5) {
            moveRight();
            if (pos.x >= COLS - 10) { 
                pos.x = COLS - 10;
                direction = 3; 
            }
        }
        break;
    case 4:
        if (a == 0) {
            moveRight();
            if (pos.x >= COLS - 10) { 
                pos.x = COLS - 10;
                a = 1;
            }
        }
        else {
            moveLeft();
            if (pos.x == 0) {
                a = 0;
            }
        }
    default:
        break;
    }
}


void EnemiesUI::draw(){
     switch (enemyType){
         case 1:
            //mvprintw(getY(), getX(), "  ");
            mvprintw(getY(), getX(), "\\ __ /");
            break;
         case 2:
           // mvprintw(getY(), getX(), "  ");
            mvprintw(getY(), getX(), "/__\\");
            break;
         case 3:
            //mvprintw(getY(), getX(), "  ");
            mvprintw(getY(), getX(), "-__-");
            break;
         case 4:
           // mvprintw(getY(), getX(), "  ");
            mvprintw(getY(), getX(), " @ __ @ ");
            break;
         case 5:
             mvprintw(getY(), getX(), " ");
             break;
          default:
            break;
        }
    refresh();
}

Enemies::~Enemies() {}
EnemiesUI::~EnemiesUI() {}
