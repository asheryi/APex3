#include <iostream>
#include <string>
#include <vector>
#include "PlayerController.h"
#include "TypesOf.h"
#include "Path.h"
#include "Counter.h"

#ifndef PLAYER_H_
#define PLAYER_H_

using namespace std;

class Player {
protected:
    Color color;
    PlayerController *controller;
    Counter *discsCounter;

    Player(PlayerController *controller, Counter *discsCounter, Color color);

    Color getRivalColor();

public:
    /*****************************************************************************
    *function name:updateScore
    *operation function:updates the score of the player
    *NOTE:
    *****************************************************************************/
    void updateScore(int newScore);

    /*****************************************************************************
    *function name:getScore
    *operation function:returns the player score
    *NOTE:
    *****************************************************************************/
    int getScore() const;

    /*****************************************************************************
    *function name:getColor
    *operation function:returns the player color
    *NOTE:
    *****************************************************************************/
    Color getColor() const {
        return color;
    }

    virtual void update(const Cell &cell) {
        controller->update(cell);
    }

    void modifyPlayerColor(Color color, Counter *discsCounter);

    /*****************************************************************************
    *function name:chooseAndReturnMove
    *operation function:returns a move from the player
    *NOTE:
    *****************************************************************************/
    virtual Cell *chooseAndReturnMove(const std::vector<Path *> &availableMovePaths)=0;

    virtual ~Player();
};

#endif /* PLAYER_H_ */
