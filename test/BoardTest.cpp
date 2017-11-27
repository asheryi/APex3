//
// Created by yishay on 11/27/17.
//


#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Board.h"

class BoardTest : public testing::Test {
    virtual void SetUp() {
        BoardTest::board_ = new Board(8, 8, vector<Cell *>(), vector<Cell *>());
    }

    virtual void TearDown() {

    }


protected:
    Board *board_{};
};


TEST_F(BoardTest, ddsvsdv) {
    vector<int> a = {1, 2};
    vector<int> b = {2, 1};

    EXPECT_EQ(a, b);
    EXPECT_EQ(board_->getRows(), 8);
}