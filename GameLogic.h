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
#include "Board.h"
// GameLogic interface of logic .

class GameLogic {
public:
    /**
     * Return valid moves , each move with it's path - it's trajectories to "eat" on the board .
     *
     * @param board - the board to check the player in the given color's moves.
     * @param color - of the player .
     * @return all of the valid moves available for the player which color was given .
     */
    virtual std::vector<Path *> *validMovePaths(const Board &board, Color color) const = 0;

    /**
     * Returns the current Game Status which could be : noValidMoves , whitwWon , blackWon , passTurn(the player cannot
     * play but the other one can play ) and tie .
     * @param currPlayerColor .
     * @param blacks - how many blacks are there on the board .
     * @param whites - how many whites are there on the board .
     * @return the curr game status as described .
     */
    virtual GameStatus
    currGameStatus(const Board &board, bool currPlayerhasMoves, const Color &currPlayerColor, int blacks,
                   int whites) = 0;
};


#endif //EX2_GAMELOGIC_H
