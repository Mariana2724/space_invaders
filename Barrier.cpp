#include "Barrier.h"
#include <iostream>

Barrier::Barrier(int x, int y) :x(x), y(y){
}

BarrierUI::BarrierUI(int x, int y):Barrier(x,y){
}

void BarrierUI::draw(){
    mvprintw(x,y , "  /\\  "); // Exemplo de desenho da nave (podemos ajustar isto)
    mvprintw( + 1, , " |==| ");
    mvprintw( + 2, , "  \\/  ");
}
