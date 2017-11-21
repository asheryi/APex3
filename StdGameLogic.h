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

    const Board &board;
    const Directions directions;

    /**
     * Checking every direction and returning true if and only if the move is valid .
     * @param move - the move to make .
     * @param color - the color of the player making the move.
     * @return truw if the move is valid , false otherwise .
     */
    Path* isValidMove(const Cell &move, Color color)const;

    /**
    * @param point - to check .
    * @return true if the point is out of bounds , false otherwise.
    */
    bool isOutOfBounds(const Cell &point) const;

    /**
     * Checks the direction completely , and returns true if and only if the direction is valid . (meaning the move to
     * that direction is valid) .
     * @param direction - the direction to check .
     * @param move - the cell starting to check from .
     * @param color - the color of the move maker.
     * @return as described , the validity of the direction .
     */
    void isValidDirection(const Cell &direction, const Cell &move, Color color,Path* path)const;

    /**
     * Adds to the flip locations given , the ones on the given direction .
     * @param flipLocations - the flip locations so far , needs to be updated .
     * @param direction - direction to check .
     * @param startCell - the stating cell .
     * @param currPlayerColor - the color .
     */
    void updateFlipLocationsInThisDirection(std::vector<Cell *> &flipLocations, const Cell &direction,
                                            const Cell &startCell, Color currPlayerColor) const;

    /**
     * Deletes vector of cells .
     * @param moves - the vector to delete.
     */
    void deleteVector(std::vector<Path *> &moves);

public:
    StdGameLogic(const Board &b);

    std::vector<Path *> *validPathsOfMoves(Color color)const;

    GameStatus currGameStatus(const Color &currPlayerColor, int blacks, int whites);

};


#endif //EX2_STDGAMELOGIC_H
