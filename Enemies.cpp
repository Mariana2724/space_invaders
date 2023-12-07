#include "Enemies.h"
#include <curses.h> 

Enemies::Enemies(int x, int y, int speed, int enemyType):Ship(x,y,speed),enemyType(enemyType){}

EnemiesUI::EnemiesUI(int x, int y, int speed, int enemyType):Enemies(x,y,speed,enemyType), direction(0) {
}

void EnemiesUI::movement(){
    switch (enemyType) {
        case 1:
            if (direction == 0) { // Movimento para a direita
                x++;
                if (x >= COLS - 10) { // Verifica se chegou ao limite direito
                    x = COLS - 10;
                    direction = 1; // Muda a dire��o para baixo
                }
            }
            else if (direction == 1) { // Movimento para baixo
                moveDown();
                direction = 2;
                if (y >= LINES - 12) { // Verifica se chegou ao limite inferior
                    y = LINES - 12; // Ajusta para o limite inferior
                    direction = 2; // Muda a dire��o para a esquerda
                }
            }
            else if (direction == 2) { // Movimento para a esquerda
                moveLeft();
                if (x <= 0) { // Verifica se chegou ao limite esquerdo
                    x = 0;
                    moveDown();
                    direction = 0; // Muda a dire��o para a direita
                }
            }
            break;
        case 2:
            if (direction == 0) { // Movimento para a direita
                x++;
                if (x >= COLS - 10) { // Verifica se chegou ao limite direito
                    x = COLS - 10;
                    direction = 1; // Muda a dire��o para baixo
                }
            }
            else if (direction == 1) { // Movimento para baixo
                moveDown();
                direction = 2;
                if (y >= LINES - 12) { // Verifica se chegou ao limite inferior
                    y = LINES - 12; // Ajusta para o limite inferior
                    direction = 2; // Muda a dire��o para a esquerda
                }
            }
            else if (direction == 2) { // Movimento para a esquerda
                moveLeft();
                if (x <= 0) { // Verifica se chegou ao limite esquerdo
                    x = 0;
                    moveDown();
                    direction = 0; // Muda a dire��o para a direita
                }
            }
            break;
        case 3:
            if (direction == 0) { // Movimento para a direita
                x++;
                if (x >= COLS - 10) { // Verifica se chegou ao limite direito
                    x = COLS - 10;
                    direction = 1; // Muda a dire��o para baixo
                }
            }
            else if (direction == 1) { // Movimento para baixo
                moveDown();
                direction = 2;
                if (y >= LINES - 12) { // Verifica se chegou ao limite inferior
                    y = LINES - 12; // Ajusta para o limite inferior
                    direction = 2; // Muda a dire��o para a esquerda
                }
            }
            else if (direction == 2) { // Movimento para a esquerda
                moveLeft();
                if (x <= 0) { // Verifica se chegou ao limite esquerdo
                    x = 0;
                    moveDown();
                    direction = 0; // Muda a dire��o para a direita
                }
            }
            break;
        case 4:
            moveRight();
            if (x >= COLS - 10) { // Chegou ao lado direito
                x = 0; // Ajusta a posi��o para n�o sair do limite
            }
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



