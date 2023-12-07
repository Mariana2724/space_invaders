#include "Barrier.h"
#include <iostream>
#include <curses.h>
Barrier::Barrier(int x, int y) :x(x), y(y){
}

int Barrier::getx(){
    return x;
}

int Barrier::gety(){
    return y;
}

BarrierUI::BarrierUI(int x, int y):Barrier(x,y){
}

void BarrierUI::draw(){
    
    mvprintw(gety(), getx(), "  ______  "); // Exemplo de desenho da nave (podemos ajustar isto)
    mvprintw(gety()+1, getx(), " |      | ");
    mvprintw(gety()+2, getx(), " |      | ");
}
