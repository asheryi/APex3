//
// Created by walter on 11/28/17.
//

#include "../include/AIConsole.h"
//
// Created by walter on 11/28/17.
//
using namespace std;

void AIConsole::show(const Board &board, const std::vector<Path *> &moves, const Color *currPlayerColor, bool passTurn,
                     int blacks,
                     int whites) const {
    cout << "Black Score: " << blacks << "        White Score: " << whites << endl;

}

void AIConsole::showError(Error errorType) const {
}

AIConsole::AIConsole() {}
