

#ifndef EX3_AIPLAYER_H
#define EX3_AIPLAYER_H


#include "Board.h"
#include "Player.h"
#include "Path.h"
#include "GameLogic.h"

class AIplayer : public Player {
    const Board &gameBoard;
    const GameLogic &gameLogic;
    const Counter &otherPlayerCounter;
private:
    /**
     * "eats" the entire path (of course , except the landing point) on the given board.
     * @param path - path of cells to "eat"
     * @param board
     */
    void attackThose(const Path *path, Board &board) const;

    /**
     * Finds the max score of the white player , all over his possible moves (movesPaths)
     * score = the other player's discd - this player's discs .
     * @param movePaths - the moves of the other player .
     * @return the max score .
     */
    int maxScore(const std::vector<Path *> &movePaths) const;

public:
    /**
     * Ai player constructor
     * @param controller - how to control it (input)
     * @param scoreCounter - it's discs Counter .
     * @param otherPlayerCounter - other player's discs counter - read only - used by the logic of AI .
     * @param gameBoard
     * @param gameLogic
     * @param color - color of this AI player.
     */
    AIplayer(PlayerController *controller, Counter *discsCounter, const Counter &otherPlayerCounter,
             const Board &gameBoard,
             const GameLogic &gameLogic, Color color);

    virtual Cell *chooseAndReturnMove(const std::vector<Path *> &availableMovePaths);

};


#endif //EX3_AIPLAYER_H
