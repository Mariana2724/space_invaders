#include "Enemies.h"
#include <curses.h> 

int EnemiesUI::Reached = 0;
int EnemiesUI::direction = 0;
int Enemies::numberOfEnemies = 0;
Enemies::Enemies(int x, int y, int speed, int enemyType):Ship(x,y,speed),enemyType(enemyType){
    numberOfEnemies++;
}

EnemiesUI::EnemiesUI(int x, int y, int speed, int enemyType):Enemies(x,y,speed,enemyType) {
    a = 0;
}

void EnemiesUI::movement(){
    
    switch (enemyType) {
        case 1:
        case 2:
        case 3:
           
        case 4:
            moveRight();
            if (x >= COLS - 10) { // Chegou ao lado direito
                x = 0; // Ajusta a posição para não sair do limite
            }
        default:
            break;
        }
}

void EnemiesUI::draw(){
     switch (enemyType){
         case 1:
            mvprintw(Gety(), Getx(), "  ");
            mvprintw(Gety(), Getx(), " \\ __ / ");
            break;
         case 2:
            mvprintw(Gety(), Getx(), "  ");
            mvprintw(Gety(), Getx(), " /__\\");
            break;
         case 3:
            mvprintw(Gety(), Getx(), "  ");
            mvprintw(Gety(), Getx(), "-__- ");
            break;
         case 4:
            mvprintw(Gety(), Getx(), "  ");
            mvprintw(Gety(), Getx(), " @ __ @ ");
            break;
          default:
            break;
        }
    refresh();
}



Enemies::~Enemies() {
    numberOfEnemies--;
}
EnemiesUI::~EnemiesUI() {

}