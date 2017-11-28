//
// Created by walter on 11/28/17.
//

#ifndef EX3_AICONSOLE_H
#define EX3_AICONSOLE_H

#include "Console.h"

class AIConsole : public Console {
public:
    AIConsole(const Board &b);

    void show(const vector<Path *> &moves, const Color *currPlayerColor, bool passTurn, int blacks, int whites) const;

    void showError(Error errorType) const;
};

#endif //EX3_AICONSOLE_H
