#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "PlayerController.h"
#include "TypesOf.h"

#ifndef PLAYER_H_
#define PLAYER_H_

using namespace std;

class Player {
protected:
    int score;
    //-3='X' for black -2='O' for white
    //TODO:sould to be const?
    Color color;
    PlayerController *controller;
    string sign;
public:
    /*****************************************************************************
    *function name:setController
    *operation function:sets the player controller.
    *NOTE:
    *****************************************************************************/
    void setController(PlayerController *controller_);
    /*****************************************************************************
    *function name:Player
    *operation function:constructor gets color indicate and return player.
    *NOTE:
    *****************************************************************************/
    //TODO:need to free controller, but ~Player makes

    //~Player();
    string getSign() const;

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

    /*****************************************************************************
    *function name:getRivalColor
    *operation function:return the color of the rival
    *NOTE:
    *****************************************************************************/
    int getRivalColor() const;

    /*****************************************************************************
    *function name:makeMove
    *operation function:returns a move from the player
    *NOTE:
    *****************************************************************************/
    virtual Cell *makeMove()=0;

    virtual ~Player();
};

#endif /* PLAYER_H_ */
