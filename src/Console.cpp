//
// Created by walter on 11/28/17.
//

#include "../include/Console.h"

using namespace std;

void Console::show(const std::vector<Path *> &moves, const Color *currPlayerColor, bool passTurn, int blacks,
                   int whites) const {
    // counting how many tiny lines needed in order to print the broken line .
    int count = 2;

    cout << " | ";
    for (int i = 1; i <= this->board.getColumns(); i++) {
        cout << i << " | ";
        count += 4;
    }

    printBrokenLine(count);

    for (int i = 1; i <= this->board.getRows(); i++) {
        cout << i << "|";
        for (int j = 1; j <= this->board.getColumns(); j++) {
            cout << " " << colorAsCharacter(board.getCellValue(i, j)) << ' ' << '|';
        }
        printBrokenLine(count);
    }

    cout << endl;

    cout << "Black Score: " << blacks << "        White Score: " << whites << endl;

    char color = (*currPlayerColor == black ? 'X' : 'O');

    cout << color << ",it's your move ." << endl;

    if (passTurn) {
        cout << "No possible moves. Play passes to the other player." << endl;
    } else {
        cout << "Your possible moves are : " << endl;
        if (!moves.empty()) {
            cout << "(" << moves[0]->getLanding().getRow() << "," << moves[0]->getLanding().getColumn() << ")";
        }
        for (int i = 1; i < moves.size(); i++) {
            cout << ",(" << moves[i]->getLanding().getRow() << "," << moves[i]->getLanding().getColumn() << ")";
        }

        cout << endl;

        cout << "Please enter your move row,col as described : " << endl;
        cout << "The first is row number between 1 and " << board.getRows() << "," << endl;
        cout << "the second is column number between 1 and " << board.getColumns()
             << ", with a comma to seperate.( e.g. 3,4)" << endl;
    }
}

void Console::printBrokenLine(int count) const {
    cout << "  " << endl;
    for (int i = 1; i <= count; i++) {
        cout << '-';
    }
    cout << endl;
}

Console::Console(const Board &b) : board(b) {}

void Console::showError(Error errorType) const {
    cout << "Error !" << endl;
    if (errorType == outOfBounds || errorType == notIntegers) {
        cout << "Please enter integers in the right format and boundaries." << endl;
    } else {
        cout << "Please enter a move you can make on the board , the moves are printed for you (:" << endl;
    }
    cout << "Try again ..." << endl;

}

char Console::colorAsCharacter(Color color) const {
    switch (color) {
        case white :
            return 'o';
        case black :
            return 'x';
        case empty :
            return ' ';
        default:
            return ' ';
    }
}

void Console::showEndGameStatus(GameStatus gameStatus) const {
    if (gameStatus == tie) {
        cout << "It's a tie ... never say never , try again and this time win ! " << endl;
    } else if (gameStatus == blackWon) {
        cout << "X : you won , I knew it (:" << endl;
    } else {
        cout << "O : you won , I knew it (:" << endl;
    }
}

void Console::showMoveDone(const Cell &cell, Color playerColor) const {
    char whoDidAMove = colorAsCharacter(playerColor) == 'x' ? 'X' : 'O';
    cout << whoDidAMove << " played : " << cell << endl;
}

void Console::showMenu() const {
    cout << "For play against human player please press h" << endl;
    cout << "For play against AI player please press a" << endl;
}
