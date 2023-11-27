#include "Enemies.h"
#include <curses.h> 

Enemy_1::Enemy_1(int x, int y, int speed) : Ship(x, y, speed) {}
Enemy_2::Enemy_2(int x, int y, int speed) : Ship(x, y, speed) {}
Enemy_3::Enemy_3(int x, int y, int speed) : Ship(x, y, speed) {}
Enemy_4::Enemy_4(int x, int y, int speed) : Ship(x, y, speed) {}
void Enemy_1::draw() {
    mvprintw(Gety(), Getx(), "  ");
    mvprintw(Gety(), Getx(), " \\ __ / "); 
    
    refresh(); // Atualiza o ecrã
}
void Enemy_2::draw() {
    mvprintw(Gety(), Getx(), "  ");
    mvprintw(Gety(), Getx(), " /__\\");

    refresh(); // Atualiza o ecrã
}
void Enemy_3::draw() {
    mvprintw(Gety(), Getx(), "  ");
    mvprintw(Gety(), Getx(), "-__- ");

    refresh(); // Atualiza o ecrã
}
void Enemy_4::draw() {
    mvprintw(Gety(), Getx(), "  ");
    mvprintw(Gety(), Getx(), " @ __ @ ");

    refresh(); // Atualiza o ecrã
}

void Enemy_4::movement() {
        moveRight();
        if (x >= COLS - 10) { // Chegou ao lado direito
            x = 0; // Ajusta a posição para não sair do limite
            movingRight = true; // Começa a mover para a esquerda
        }
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



/*
Enemies::Enemies(int x, int y, int speed, int enemyType){
    switch (enemyType) {
    case 1:
        enemy.push_back(new Enemy_1(x, y, speed));
        for (const auto& enemies : enemy) {
            enemies->draw(); 
        }
        break;
    case 2:
        enemy.push_back(new Enemy_2(x, y, speed));
        for (const auto& enemies : enemy) {
            enemies->draw();
        }
        break;
    case 3:
        enemy.push_back(new Enemy_3(x, y, speed));
        for (const auto& enemies : enemy) {
            enemies->draw();
        }
        break;
    case 4:
        enemy.push_back(new Enemy_4(x, y, speed));
        for (const auto& enemies : enemy) {
            enemies->draw();
            enemies->movement();
        }

        break;
    }
}*/
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

void Enemies::draw()
{
}
*/