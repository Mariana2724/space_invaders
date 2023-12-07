#include "Enemies.h"
#include <curses.h> 

Enemies::Enemies(int x, int y, int speed, int enemyType):Ship(x,y,speed),enemyType(enemyType){}

EnemiesUI::EnemiesUI(int x, int y, int speed, int enemyType):Enemies(x,y,speed,enemyType){
}

void EnemiesUI::movement(){
    switch (enemyType) {
        case 1:
           /* if () {
                moveLeft();
            }
            else {
                if (x > 115) {
                    moveDown();
                }
                else {
                    if()
                }
            }*/
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            x++;
            if (x >= COLS - 10) { // Chegou ao lado direito
                x = 0; // Ajusta a posição para não sair do limite
            }
          //  timeout(10); fica mais lento -> podemos usar para mudar velocidades emtre movimentos
            break;
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



