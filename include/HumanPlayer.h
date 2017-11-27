#ifndef EX1_HUMANPLAYER_H
#define EX1_HUMANPLAYER_H

#include "Player.h"
#include "PlayerController.h"
#include "Cell.h"

class HumanPlayer : public Player {

public:
    HumanPlayer(PlayerController *controller, Counter *scoreCounter, Color color);

    virtual Cell *chooseAndReturnMove(const std::vector<Path *> &availableMovePaths);
};


#endif //EX1_HUMANPLAYER_H
