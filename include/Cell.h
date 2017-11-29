// 318225851
// Yishay Asher

#ifndef EX2_CELL_H
#define EX2_CELL_H

#include <iostream>

using namespace std;
// Represents a cell in a matrix . (in this case board)

class Cell {
private:
    int row;
    int column;
public:
    Cell();

    /**
   * Cell Constructor.
   * @param row - int ,row of cell.
   * @param column - - int , column of cell.
   */
    Cell(int row, int column);

    /**
     *Copy constructor of Cell.
     * @param p - cell to be copy.
     */
    Cell(const Cell &p);

    /**
    *returns the cell column.
    */
    int getColumn() const;

    /**
   *returns the cell row.
   */
    int getRow() const;

    /**
     * Update this cell to be : row +p's row , col +p's col, and return reference to this .
     * @param p - point to add from .
     * @return reference to this cell after update(as described)
     */
    Cell &operator+=(Cell p);

    Cell operator-(Cell p);

    /**
     * Comparing two cells row by row , column by column .
     * @param p - other cell .
     * @return true if and only if this row = to p's and same for column .
     */
    bool operator==(Cell p);

    /**
    * checks if the cell not equal.
    * @param p - other cell .
    * @return true if this row != to p's or same for column .
    */
    bool operator!=(Cell p);

/**
    *applied to print the cell.
    * @param p - cell to print.
    */
    friend ostream &operator<<(ostream &stream, const Cell &cell);
};


#endif //EX2_CELL_H
