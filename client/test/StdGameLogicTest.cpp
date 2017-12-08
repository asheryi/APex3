


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Board.h"
#include "../include/StdGameLogic.h"
#include "../include/VectorExterminator.h"

class StdGameLogicTest : public testing::Test {
    virtual void SetUp() {
        blacks.push_back(new Cell(3, 2));
        blacks.push_back(new Cell(3, 4));
        blacks.push_back(new Cell(4, 5));
        blacks.push_back(new Cell(5, 4));

        whites.push_back(new Cell(2, 2));
        whites.push_back(new Cell(3, 3));
        whites.push_back(new Cell(4, 4));
        whites.push_back(new Cell(5, 5));
        this->board_ = new Board(8, 8, blacks, whites);
        gameLogic = new StdGameLogic();
        paths = gameLogic->validMovePaths(*board_, black);


        possiblePathLanding.push_back(new Cell(1, 2));
        possiblePathLanding.push_back(new Cell(4, 3));
        possiblePathLanding.push_back(new Cell(5, 6));
        possiblePathLanding.push_back(new Cell(6, 5));

        notPossiblePathLanding.push_back(new Cell(3, 2));
        notPossiblePathLanding.push_back(new Cell(1, 6));
        notPossiblePathLanding.push_back(new Cell(3, 3));
        notPossiblePathLanding.push_back(new Cell(6, 4));

        bool playerHaveMoves = (paths->size() > 0);
        gameStatus = gameLogic->currGameStatus(*board_, playerHaveMoves, black, 4, 4);


    }


protected:
    Board *board_;
    vector<Cell *> blacks;
    vector<Cell *> whites;
    StdGameLogic *gameLogic;
    vector<Path *> *paths;
    vector<Cell *> possiblePathLanding;
    vector<Cell *> notPossiblePathLanding;
    GameStatus gameStatus;

public :
    bool notEmptyMoves() {
        return (!paths->size() == 0);
    }

    bool pathsSameAs(vector<Cell *> cells) {
        //if there is no matching with their size its invalid
        if (cells.size() != paths->size())return false;
        bool correct = false;
        for (int i = 0; i < paths->size(); i++) {
            Cell cell = (*paths)[i]->getLanding();
            correct = false;
            for (int j = 0; j < cells.size(); j++) {
                if (cell == *cells[j]) {
                    correct = true;
                }
            }
            if (!correct) {
                break;
            }
        }
        return correct;
    }

    bool noOneWonCheck() {

        return (gameStatus == noOneWon);
    }

    bool passTurnCheck() {
        std::vector<Cell *> blacks_(5), whites_(1);
        blacks_[0] = new Cell(1, 1);
        blacks_[1] = new Cell(2, 1);
        blacks_[2] = new Cell(3, 1);
        blacks_[3] = new Cell(1, 3);
        blacks_[4] = new Cell(2, 3);

        whites_[0] = new Cell(3, 2);
        Board *b = new Board(3, 3, blacks_, whites_);
        vector<Path *> *paths_ = gameLogic->validMovePaths(*b, white);
        bool playerHaveMoves = (paths_->size() > 0);
        GameStatus gameStatus_ = gameLogic->currGameStatus(*b, playerHaveMoves, white, 5, 1);
        deleteVector(blacks_);
        deleteVector(whites_);
        deleteVector(*paths_);
        delete paths_;
        delete b;
        return (gameStatus_ == passTurn);
    }

    bool tieCheck() {
        std::vector<Cell *> blacks_(32), whites_(32);

        int p = 0;
        for (int i = 1; i <= 8; i++) {
            if (i == 5) {
                p = 0;
            }
            for (int j = 1; j <= 8; j++, p++) {
                if (i > 4) {
                    whites_[p] = new Cell(i, j);
                } else {
                    blacks_[p] = new Cell(i, j);
                }

            }
        }
        Board *b = new Board(8, 8, blacks_, whites_);
        vector<Path *> *paths_ = gameLogic->validMovePaths(*b, white);
        bool playerHaveMoves = (paths_->size() > 0);
        GameStatus gameStatus_ = gameLogic->currGameStatus(*b, playerHaveMoves, white, 32, 32);
        deleteVector(blacks_);
        deleteVector(whites_);
        deleteVector(*paths_);
        delete paths_;
        delete b;
        return (gameStatus_ == tie);
    }

    bool winCheck() {
        std::vector<Cell *> blacks_(40), whites_(24);

        int p = 0;
        for (int i = 1; i <= 7; i++) {
            if (i == 5) {
                p = 0;
            }
            for (int j = 1; j <= 8; j++, p++) {
                if (i > 4) {
                    whites_[p] = new Cell(i, j);
                } else {
                    blacks_[p] = new Cell(i, j);
                }

            }
        }
        for (int i = 1; i <= 8; i++) {
            blacks_[31 + i] = new Cell(8, i);
        }

        Board *b = new Board(8, 8, blacks_, whites_);
        vector<Path *> *paths_ = gameLogic->validMovePaths(*b, black);
        bool playerHaveMoves = (paths_->size() > 0);
        GameStatus gameStatus_ = gameLogic->currGameStatus(*b, playerHaveMoves, black, 40, 24);
        deleteVector(blacks_);
        deleteVector(whites_);
        deleteVector(*paths_);
        delete paths_;
        delete b;
        return (gameStatus_ == blackWon);
    }

    virtual void TearDown() {
        delete gameLogic;
        delete board_;
        deleteVector(blacks);
        deleteVector(whites);
        deleteVector(*paths);
        delete paths;
        deleteVector(possiblePathLanding);
        deleteVector(notPossiblePathLanding);
    }
};


TEST_F(StdGameLogicTest, validMoveCheck) {
    EXPECT_TRUE(notEmptyMoves());
    EXPECT_TRUE(pathsSameAs(possiblePathLanding));
    EXPECT_FALSE(pathsSameAs(notPossiblePathLanding));
}

TEST_F(StdGameLogicTest, currGameStatusNoOneOwnCheck) {
    EXPECT_TRUE(noOneWonCheck());
    EXPECT_TRUE(passTurnCheck());
    EXPECT_TRUE(tieCheck());
    EXPECT_TRUE(winCheck());


}
