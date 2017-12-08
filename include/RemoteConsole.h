

#ifndef EX3_REMOTECONSOLE_H
#define EX3_REMOTECONSOLE_H


#include "Console.h"

class RemoteConsole : public Console {

public:
    RemoteConsole();

    void show(const Board &board, const vector<Path *> &moves, const Color &currPlayerColor, bool passTurn, int blacks,
              int whites) const;

    void showError(Error errorType) const;
};


#endif //EX3_REMOTECONSOLE_H
