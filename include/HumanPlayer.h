#ifndef EX1_HUMANPLAYER_H
#define EX1_HUMANPLAYER_H

#include "Player.h"
#include "PlayerController.h"
#include "Cell.h"

class HumanPlayer : public Player {

public:
    HumanPlayer(PlayerController *controller, Counter *discsCounter, Color color);

    HumanPlayer(PlayerController *controller);

    virtual Cell *chooseAndReturnMove(const std::vector<Path *> &availableMovePaths);

    virtual int getMenuSelection();

    void modifyPlayerColor(Color color, Counter *discsCounter);
};


#endif //EX1_HUMANPLAYER_H
