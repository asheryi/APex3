// 318225851
// Yishay Asher

#ifndef EX2_GAMELOGIC_H
#define EX2_GAMELOGIC_H


#include "Cell.h"
#include "Player.h"
#include "TypesOf.h"
#include <iostream>
#include <vector>
#include "Path.h"
// GameLogic interface of logic .

class GameLogic {
public:
    /**
     * @param color - of the
     * @return all of the valid moves available for the player which color was given .
     */
    virtual std::vector<Path *> *validPathsOfMoves(Color color) const = 0;

    /**
     * Returns the current Game Status which could be : noValidMoves , whitwWon , blackWon , passTurn(the player cannot
     * play but the other one can play ) and tie .
     * @param currPlayerColor .
     * @param blacks - how many blacks are there on the board .
     * @param whites - how many whites are there on the board .
     * @return the curr game status as described .
     */
    virtual GameStatus
    currGameStatus(const Color &currPlayerColor, int blacks, int whites) = 0;
};


#endif //EX2_GAMELOGIC_H
