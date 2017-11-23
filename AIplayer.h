//
// Created by yishay on 11/23/17.
//

#ifndef EX3_AIPLAYER_H
#define EX3_AIPLAYER_H


#include "Board.h"
#include "Player.h"
#include "Path.h"
#include "GameLogic.h"

class AIplayer : public Player {
    const Board &gameBoard;
    const GameLogic &gameLogic;
    const Counter &otherPlayerCounter;
private:
    void attackThose(const Path *path, Board &board) const;

    int maxScore(const std::vector<Path *> &movePaths) const;

public:
    AIplayer(PlayerController *controller, Counter *scoreCounter, const Counter &otherPlayerCounter,
             const Board &gameBoard,
             const GameLogic &gameLogic, Color color);

    virtual Cell *chooseAndReturnMove(const std::vector<Path *> &availableMovePaths);

};


#endif //EX3_AIPLAYER_H
