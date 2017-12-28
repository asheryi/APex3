

#ifndef EX2_CONSOLE_H
#define EX2_CONSOLE_H


#include "Display.h"
#include "Board.h"
#include "Cell.h"

class Console : public Display {
protected:
    /**
     * prints a broken line .
     * @param count - how many tiny lines to draw.
     */
    virtual void printBrokenLine(int count) const;

    /**
     * Converts the color as enum to the corresponding character to print on the board.
     * @param color .
     * @return the character as described above.
     */
    virtual char colorAsCharacter(Color color) const;

public:
    Console();

    virtual void showMenu() const;

    virtual void
    show(const Board &board, const std::vector<Path *> &moves, const Color &currPlayerColor, bool passTurn, int blacks,
         int whites) const;

    virtual void showError(Error errorType) const;

    virtual void showEndGameStatus(GameStatus gameStatus) const;

    virtual void showMoveDone(const Cell &cell, Color playerColor) const;

    virtual void showMessage(string message) const;
};


#endif //EX2_CONSOLE_H
