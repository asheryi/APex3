// 318225851
// Yishay Asher

#ifndef EX2_STDGAMELOGIC_H
#define EX2_STDGAMELOGIC_H


#include "GameLogic.h"
#include "Board.h"
#include "Player.h"
#include "Directions.h"

// StdGameLogic implements the GameLogic interface .

class StdGameLogic : public GameLogic {
private:

    const Directions directions;

    /**
     * Checking every direction and generating the eating path of a move . if the path is empty than this move is not
     * legitimic .
     * @param board - the board to check with .
     * @param move - the move to make .
     * @param color - the color of the player making the move.
     * @return true if the move is valid , false otherwise .
     */
    Path *theEatingPathOfMove(const Board &board, const Cell &move, Color color) const;

    /**
    * @param point - to check .
    * @param board - the board to check with .
    * @return true if the point is out of bounds , false otherwise.
    */
    bool isOutOfBounds(const Board &board, const Cell &point) const;

    /**
     * Checks the direction completely , and updates the path to include this direction completly.
     * @param board - the board to check with .
     * @param direction - the direction to check .
     * @param move - the cell starting to check from .
     * @param color - the color of the move maker.
     * @return as described , the validity of the direction .
     */
    void updatePathBasedOnDirection(const Board &board, const Cell &direction, const Cell &move, Color color,
                                    Path *path) const;

public:
    StdGameLogic();

    std::vector<Path *> *validMovePaths(const Board &board, Color color) const;

    GameStatus
    currGameStatus(const Board &board, bool currPlayerhasMoves, const Color &currPlayerColor, int blacks, int whites);
};


#endif //EX2_STDGAMELOGIC_H
