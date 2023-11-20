#include "NavePlayer.h"
#include <iostream>
using namespace std;
NavePlayer::NavePlayer(): Ship(){
   // ships.push_back(this);
}
NavePlayer::NavePlayer(int x, int y) : Ship(x, y) {
}
NavePlayer::NavePlayer(int x, int y, int speed) : Ship(x, y, speed) {
}
void NavePlayer::movementPlayer(char direction){
    if (direction == 'L') {
        moveLeft(); // movimento para a esquerda
    }
    else if (direction == 'R') {
        moveRight(); // movimento para a direita
    }
}
void NavePlayer::draw() { //override??
    cout << "NAVEDRAW" << endl;
}