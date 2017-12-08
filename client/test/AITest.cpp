


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Board.h"
#include "../include/AIplayer.h"
#include "../include/StdGameLogic.h"
#include "../include/ConsoleController.h"
#include "../include/VectorExterminator.h"

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
    vector<Path *> *movePaths = gameLogic->validMovePaths(*board, white);
    Cell *selectedMove = this->AI->chooseAndReturnMove(*movePaths);
    // After checking manually ...
    Cell supposeToReturnCell(2, 2);

    //EXPECT_EQ(*selectedMove, supposeToReturnCell);
    EXPECT_TRUE(*selectedMove == supposeToReturnCell);

    deleteVector(*movePaths);
    delete movePaths;
    delete selectedMove;
}