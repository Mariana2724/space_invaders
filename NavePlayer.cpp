#include "NavePlayer.h"

NavePlayer::NavePlayer(): Ship(){

}

void NavePlayer::movementPlayer(char direction){
    if (direction == 'L') {
        moveLeft(); // movimento para a esquerda
    }
    else if (direction == 'R') {
        moveRight(); // movimento para a direita
    }
}
