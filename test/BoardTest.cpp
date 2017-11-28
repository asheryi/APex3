//
// Created by yishay on 11/27/17.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Board.h"

class BoardTest : public testing::Test {
    virtual void SetUp() {
        this->board_ = new Board(8, 8, vector<Cell *>(), vector<Cell *>());
    }

    virtual void TearDown() {
        delete board_;
    }

public :
    bool something() {
        return false;
    }


protected:
    Board *board_;
};


TEST_F(BoardTest, testingBoard) {
    EXPECT_EQ(board_->getRows(), 8);
    EXPECT_TRUE(something());
}