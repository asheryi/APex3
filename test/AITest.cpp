//
// Created by yishay on 11/28/17.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Board.h"
#include "../include/AIplayer.h"
#include "../include/StdGameLogic.h"
#include "../include/Console.h"
#include "../include/ConsoleController.h"

class AITest : public testing::Test {
    virtual void SetUp() {

        blacks = new vector<Cell *>();
        whites = new vector<Cell *>();

        // Building a specific board , checked manually , that suppose to return 2,2 .

        blacks->push_back(new Cell(3, 4));
        blacks->push_back(new Cell(3, 3));
        blacks->push_back(new Cell(3, 2));
        blacks->push_back(new Cell(4, 5));
        blacks->push_back(new Cell(5, 4));


        whites->push_back(new Cell(5, 5));
        whites->push_back(new Cell(4, 4));


        this->board = new Board(8, 8, *blacks, *whites);

        this->blacksCounter = new Counter(blacks->size());
        this->whitesCounter = new Counter(whites->size());

        this->gameLogic = new StdGameLogic();

        this->controller = new ConsoleController();

        this->AI = new AIplayer(controller, whitesCounter, *blacksCounter, *board, *gameLogic, white);

    }

    virtual void TearDown() {
        delete board;
        delete blacks;
        delete whites;
    }


protected:
    Board *board;
    vector<Cell *> *blacks;
    vector<Cell *> *whites;
    AIplayer *AI;
    Counter *whitesCounter;
    Counter *blacksCounter;
    GameLogic *gameLogic;
    PlayerController *controller;
};


TEST_F(AITest, testingValidAIMove) {
    EXPECT_EQ(this->AI->)
}