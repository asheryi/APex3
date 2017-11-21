// 318225851
// Yishay Asher

#ifndef EX2_CONSOLE_H
#define EX2_CONSOLE_H


#include "Display.h"
#include "Board.h"
#include "Cell.h"

class Console : public Display {
private:
    const Board &board;

    /**
     * prints a broken line .
     * @param count - how many tiny lines to draw.
     */
    void printBrokenLine(int count) const;

    /**
     * Converts the color as enum to the corresponding character to print on the board.
     * @param color .
     * @return the character as described above.
     */
    char colorAsCharacter(Color color) const;

public:
    Console(const Board &b);

    void show(const std::vector<Path *> &moves, const Color *currPlayerColor, bool passTurn) const;

    void showError(Error errorType) const;

    void showEndGameStatus(GameStatus gameStatus) const;
};


#endif //EX2_CONSOLE_H
