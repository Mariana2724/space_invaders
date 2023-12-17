#include "Enemies.h"
#include <curses.h> 
using namespace std;

int EnemiesUI::direction = 0;
Enemies::Enemies(int x, int y, int speed, int enemyType):Ship(x,y,speed),enemyType(enemyType){
}
int Enemies::getEnemyType() {
    return enemyType;
}
EnemiesUI::EnemiesUI(int x, int y, int speed, int enemyType):Enemies(x,y,speed,enemyType) {
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
            if (pos.x >= COLS - 10) { // Verifica se chegou ao limite direito
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
                pos.y = LINES - 10; // Ajusta para o limite inferior
                direction = 3;
            }
        }
        else if (direction == 2) { // Movimento para a esquerda
            moveLeft();
            if (pos.x == 0) { // Verifica se chegou ao limite esquerdo
                //pos.x = 0;
                direction = 1; // Muda a direção para a direita
            }
        }
        else if (direction == 3) {
            moveUp();
            if (pos.x == 0) {
                direction = 5;
            }
            else if (pos.x == COLS - 10) {
                direction = 4;
            }
            if (pos.y <= 5) { // Verifica se chegou ao limite inferior
                moveDown();
                moveRight();// Ajusta para o limite inferior
                direction = 0;
            }
        }
        else if (direction == 4) {
            moveLeft();
            if (pos.x <= 0) { // Verifica se chegou ao limite esquerdo
                pos.x = 0;
                direction = 3; // Muda a direção para cima
            }
        }
        else if (direction == 5) {
            moveRight();
            if (pos.x >= COLS - 10) { // Verifica se chegou ao limite esquerdo
                pos.x = COLS - 10;
                direction = 3; // Muda a direção para cima
            }
        }
        break;
    case 4:
        if (a == 0) {
            moveRight();
            if (pos.x >= COLS - 10) { // Chegou ao lado direito
                pos.x = COLS - 10; // Ajusta a posição para não sair do limite
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
            mvprintw(getY(), getX(), "  ");
            mvprintw(getY(), getX(), "\\ __ / ");
            break;
         case 2:
            mvprintw(getY(), getX(), "  ");
            mvprintw(getY(), getX(), "/__\\  ");
            break;
         case 3:
            mvprintw(getY(), getX(), "  ");
            mvprintw(getY(), getX(), "-__-");
            break;
         case 4:
            mvprintw(getY(), getX(), "  ");
            mvprintw(getY(), getX(), " @ __ @ ");
            break;
         case 5:
             mvprintw(getY(), getX(), "  ");
             break;
          default:
            break;
        }
    refresh();
}
//
//void EnemiesUI::shoot(list<BulletsUI*> bulletsEnemy) {
//   
//        if (rand() % 300 < 0.5) {
//            bulletsEnemy.emplace_back(new BulletsUI(Getx(), Gety(), 2, 2));
//        }
//    
//}

Enemies::~Enemies() {}
EnemiesUI::~EnemiesUI() {}
