

#include "../include/RemoteConsole.h"

using namespace std;

void
RemoteConsole::show(const Board &board, const std::vector<Path *> &moves, const Color &currPlayerColor, bool passTurn,
                    int blacks,
                    int whites) const {
    if (passTurn) {
        cout << "No possible moves for the remote player , turn passed" << endl;

    }
}

void RemoteConsole::showError(Error errorType) const {
}

RemoteConsole::RemoteConsole() {}