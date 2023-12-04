#include "Enemies.h"
#include <curses.h> 

Enemies::Enemies(int x, int y, int speed, int enemyType):Ship(x,y,speed),enemyType(enemyType){}

EnemiesUI::EnemiesUI(int x, int y, int speed, int enemyType):Enemies(x,y,speed,enemyType){
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

/*

void Enemy_4::movement() {
        if (x >= COLS - 10) { // Chegou ao lado direito
            x = 0; // Ajusta a posição para não sair do limite
        }
    }

void Enemies::addEnemy(Ship* newEnemy) {
    enemy.push_back(newEnemy);
}
void Enemies::moveAllEnemies() {
    for (auto& enemies : enemy) {
        enemies->movement();
    }
}
void Enemies::drawAllEnemies() {
    for (const auto& enemies : enemy) {
            enemies->draw();
    }
    refresh();
}
*/

/*
void Enemies::movementEnemies(int key){
    switch (key) {
    case KEY_LEFT:
        moveLeft(); // movimento para a esquerda
        break;
    case KEY_RIGHT:
        moveRight(); // movimento para a direita
        break;
        // Adiciona mais casos conforme necessário para outras teclas
    case KEY_DOWN:
        moveDown();
        break;
    }
}

*/

