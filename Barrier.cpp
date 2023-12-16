#include "Barrier.h"
#include <iostream>
#include <curses.h>
#include <string>
using namespace std;
Barrier::Barrier(int x, int y, int score=20) {
   this-> score = 20;
   this->position.x = x;
   this->position.y = y;
}

int Barrier::getX(){
    return position.x;
}

int Barrier::getY(){
    return position.y;
}
int Barrier::wasShot() {
    --score;
    if (score== 0) {
        return 1;
    }
    else {
        return 0;
    }
}

BarrierUI::BarrierUI(int x, int y):Barrier(x,y){
}

void BarrierUI::draw() {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    //string a = to_string(score);
    attron(COLOR_PAIR(1));
    mvprintw(getY(), getX(), "  ______  ");
    mvprintw(getY() + 1, getX() + 1, "|      |");
    attroff(COLOR_PAIR(1));
    mvprintw(getY() + 1, getX() + 4, to_string(score).c_str());
    attron(COLOR_PAIR(1));
    mvprintw(getY() + 2, getX(), " \\______/ ");
    attroff(COLOR_PAIR(1));
}

//static_cast<string>(score)

