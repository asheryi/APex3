//
// Created by yishay on 11/27/17.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Board.h"

class BoardTest : public testing::Test {
    virtual void SetUp() {

        blacks = new vector<Cell *>();
        whites = new vector<Cell *>();


        blacks->push_back(new Cell(1, 1));
        blacks->push_back(new Cell(8, 8));
        blacks->push_back(new Cell(5, 6));


        blacks->push_back(new Cell(2, 2));
        blacks->push_back(new Cell(3, 3));
        blacks->push_back(new Cell(4, 5));


        this->board(8, 8, *blacks, *whites);

    }

    virtual void TearDown() {
        delete blacks;
        delete whites;
    }


protected:
    Board board;
    vector<Cell *> *blacks;
    vector<Cell *> *whites;
};


TEST_F(BoardTest, testingConstructor) {
    EXPECT_EQ(board.getCellValue(1, 1), black);
    EXPECT_EQ(board.getCellValue(8, 8), black);
    EXPECT_EQ(board.getCellValue(5, 6), black);

    EXPECT_EQ(board.getCellValue(2, 2), white);
    EXPECT_EQ(board.getCellValue(3, 3), white);
    EXPECT_EQ(board.getCellValue(4, 4), white);

}