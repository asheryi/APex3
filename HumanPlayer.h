#ifndef EX1_HUMANPLAYER_H
#define EX1_HUMANPLAYER_H

#include "Player.h"
#include "PlayerController.h"
#include "Cell.h"

class HumanPlayer:public Player{

public:
    HumanPlayer(Color color);
    virtual Cell* makeMove();
};


#endif //EX1_HUMANPLAYER_H
