#include "Barrier.h"
#include <iostream>
#include <curses.h>
#include <string>
using namespace std;
Barrier::Barrier(int x, int y, int score=30) :x(x), y(y){
   this-> score = 20;
}

int Barrier::getx(){
    return x;
}

int Barrier::gety(){
    return y;
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
    mvprintw(gety(), getx(), "  ______  ");
    mvprintw(gety() + 1, getx() + 1, "|      |");
    attroff(COLOR_PAIR(1));
    mvprintw(gety() + 1, getx() + 4, to_string(score).c_str());
    attron(COLOR_PAIR(1));
    mvprintw(gety() + 2, getx(), " \\______/ ");
    attroff(COLOR_PAIR(1));
}

//static_cast<string>(score)

