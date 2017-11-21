#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(Color color){
    this->color=color;
}
 Cell* HumanPlayer::makeMove(){
    return controller->getLandingPoint();
}


