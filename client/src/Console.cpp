

#include "../include/Console.h"

using namespace std;

void Console::show(const Board &board, const std::vector<Path *> &moves, const Color &currPlayerColor, bool passTurn,
                   int blacks,
                   int whites) const {
    // counting how many tiny lines needed in order to print the broken line .
    int count = 2;

    cout << " | ";
    for (int i = 1; i <= board.getColumns(); i++) {
        cout << i << " | ";
        count += 4;
    }

    printBrokenLine(count);

    for (int i = 1; i <= board.getRows(); i++) {
        cout << i << "|";
        for (int j = 1; j <= board.getColumns(); j++) {
            cout << " " << colorAsCharacter(board.getCellValue(i, j)) << ' ' << '|';
        }
        printBrokenLine(count);
    }

    cout << endl;

    cout << "Black Score: " << blacks << "        White Score: " << whites << endl;

    if (currPlayerColor == empty) {
        return;
    }

    char color = (currPlayerColor == black ? 'X' : 'O');

    cout << color << ",it's your move ." << endl;

    if (passTurn) {
        cout << "No possible moves. Play passes to the other player." << endl;
    } else {
        cout << "Your possible moves are : ";
        if (!moves.empty()) {
            cout << "(" << moves[0]->getLanding().getRow() << "," << moves[0]->getLanding().getColumn() << ")";
        }
        for (int i = 1; i < moves.size(); i++) {
            cout << ",(" << moves[i]->getLanding().getRow() << "," << moves[i]->getLanding().getColumn() << ")";
        }

        cout << endl;

        cout << "Please enter your move : row,col (row input from 1 to " << board.getRows() << ", col from 1 to "
             << board.getColumns() << ") :" << endl;

    }
}

void Console::printBrokenLine(int count) const {
    cout << "  " << endl;
    for (int i = 1; i <= count; i++) {
        cout << '-';
    }
    cout << endl;
}

Console::Console() {}

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
        cout << "X won , I knew it (:" << endl;
    } else {
        cout << "O won , I knew it (:" << endl;
    }
}

void Console::showMoveDone(const Cell &cell, Color playerColor) const {
    char whoDidAMove = colorAsCharacter(playerColor) == 'x' ? 'X' : 'O';
    cout << whoDidAMove << " played : " << cell << endl;
}

void Console::showMenu() const {
    cout << "To play against human player please press 1" << endl;
    cout << "To play against AI player please press 2" << endl;
    cout << "To play remote please press 3" << endl;

}

void Console::showMessage(string message) const {
    cout << message << endl;
}
