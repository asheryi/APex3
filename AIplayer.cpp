//
// Created by yishay on 11/23/17.
//

#include "AIplayer.h"
#include "StandardAttack.h"
#include "VectorExterminator.h"

AIplayer::AIplayer(PlayerController *controller,
                   const Board &gameBoard,
                   const GameLogic &gameLogic, Color color) : Player(controller, color),
                                                              gameBoard(gameBoard),
                                                              gameLogic(gameLogic) {

}

Cell *AIplayer::chooseAndReturnMove(const std::vector<Path *> &availableMovePaths) {

    int minGrade = gameBoard.getRows() * gameBoard.getColumns(); // no better grade than that ...
    Cell AIFinalMove;

    for (unsigned int i = 0; i < availableMovePaths.size(); i++) {
        Board copy(gameBoard);
        this->attackThose(availableMovePaths[i], copy);
        std::vector<Path *> *otherMoves = gameLogic.validMovePaths(copy, this->getRivalColor());
        if (otherMoves->empty()) {
            deleteVector(*otherMoves);
            delete otherMoves;
            return new Cell(availableMovePaths[i]->getLanding());
        }

        int grade = maxScore(*otherMoves);
        if (grade < minGrade) {
            AIFinalMove = availableMovePaths[i]->getLanding();
        }

        deleteVector(*otherMoves);
        delete otherMoves;

    }

    return new Cell(AIFinalMove);
}

void AIplayer::attackThose(const Path *path, Board &board) const {
    StandardAttack attack(*path);
    while (attack.hasNext()) {
        Cell c = attack.getNext();
        board.setCellAs(c.getRow(), c.getColumn(), this->color);
    }
}

int AIplayer::maxScore(const std::vector<Path *> &movePaths) const {
    int maxScore = 0;
    for (unsigned int i = 0; i < movePaths.size(); i++) {
        int currScore = movePaths[i]->score();
        if (currScore > maxScore) {
            maxScore = currScore;
        }
    }
    return maxScore;
}







