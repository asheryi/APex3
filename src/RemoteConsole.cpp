

#include "../include/RemoteConsole.h"

using namespace std;

void
RemoteConsole::show(const Board &board, const std::vector<Path *> &moves, const Color &currPlayerColor, bool passTurn,
                    int blacks,
                    int whites) const {
    if (passTurn) {
        cout << "No possible moves for the remote player , it's your turn again (:" << endl;
    } else {
        Console::show(board, moves, empty, passTurn, blacks, whites);
        if (currPlayerColor != empty) {
            cout << "Waiting for the other player to make a move" << endl;
        }
    }
}

void RemoteConsole::showError(Error errorType) const {
}

RemoteConsole::RemoteConsole() {}