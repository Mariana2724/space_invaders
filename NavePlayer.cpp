#include "NavePlayer.h"

NavePlayer::NavePlayer(): Ship(){
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
