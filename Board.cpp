// 318225851
// Yishay Asher

#include "Board.h"
#include <iostream>


Board::Board(int rows, int columns, const std::vector<Cell *> &blacks, const std::vector<Cell *> &whites)
        : rows(rows), columns(columns) {
    grid = new Color *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        grid[i] = new Color[this->columns];
    }

    for (int i = 1; i <= this->rows; i++) {
        for (int j = 1; j <= this->columns; j++) {
            this->setCellAs(i, j, empty);
        }
    }

    int size = blacks.size();

    for (int i = 0; i < size; i++) {
        this->setCellAs(blacks[i]->getRow(), blacks[i]->getColumn(), black);
    }

    size = whites.size();

    for (int i = 0; i < size; i++) {
        this->setCellAs(whites[i]->getRow(), whites[i]->getColumn(), white);
    }
}

void Board::setCellAs(int i, int j, Color value) {
    this->grid[i - 1][j - 1] = value;
}


int Board::getRows() const {
    return rows;
}

int Board::getColumns() const {
    return columns;
}

Color Board::getCellValue(int i, int j) const {
    return this->grid[i - 1][j - 1];
}

Board::~Board() {
    for (int i = 0; i < columns; i++) {
        delete[] grid[i];
    }
    delete[] grid;
}



