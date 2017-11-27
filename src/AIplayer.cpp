//
// Created by yishay on 11/23/17.
//

#include "../include/AIplayer.h"
#include "../include/StandardAttack.h"
#include "../include/VectorExterminator.h"

AIplayer::AIplayer(PlayerController *controller, Counter *scoreCounter, const Counter &otherPlayerCounter,
                   const Board &gameBoard,
                   const GameLogic &gameLogic, Color color) : Player(controller, scoreCounter, color),
                                                              gameBoard(gameBoard),
                                                              gameLogic(gameLogic),
                                                              otherPlayerCounter(otherPlayerCounter) {

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
            minGrade = grade;
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
        int currLength = movePaths[i]->length();
        // according to the algorithm , we need to subtract the number of AI's disk from the other player's .
        // the length of the path is the number of flips + 1 .
        // meaning the num of other player's disks - the num of AI's disks , is the subtraction  AFTER the flips :
        int numOfOtherPlayerDisks = this->otherPlayerCounter.getValue() + currLength;
        int numOfAIDisks = this->scoreCounter->getValue() - currLength +
                           1; // adding 1 because of length is with the empty cell also ...

        int currScore = numOfOtherPlayerDisks - numOfAIDisks;

        if (currScore > maxScore) {
            maxScore = currScore;
        }
    }
    return maxScore;
}







