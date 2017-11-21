// 318225851
// Yishay Asher

#ifndef EX2_DISPLAY_H
#define EX2_DISPLAY_H

#include "Cell.h"
#include "TypesOf.h"
#include <vector>
#include "Path.h"
class Display {
public:
    /**
     * Shows the current status of the board and moves .
     * @param moves - moves to show on the display .
     * @param currPlayerColor - the current player's color .
     * @param passTurn - true if the situation is that the current player have no moves and the other one does have .
     */
    virtual void show(const std::vector<Path *> &moves, const Color *currPlayerColor, bool passTurn) const = 0;

    /**
     * Shows the error given.
     * @param errorType,s
     */
    virtual void showError(Error errorType) const = 0;

    /**
     * Displays the game status given .
     * @param gameStatus
     */
    virtual void showEndGameStatus(GameStatus gameStatus) const = 0;

};


#endif //EX2_DISPLAY_H
