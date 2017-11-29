// 318225851
// Yishay Asher

#ifndef EX2_BOARD_H
#define EX2_BOARD_H


#include <vector>
#include "Cell.h"
#include "TypesOf.h"

class Board {
public:
    /**
    * Builds the board with the given rows and columns and initialize the board.
    * @param rows - int ,rows size.
    * @param columns - - int , columns size.
    * @param blacks - vector of cells to place blacks disks.
    * @param whites - vector of cells to place whites disks.
    */
    Board(int rows, int columns, const std::vector<Cell *> &blacks, const std::vector<Cell *> &whites);

    /**
     * Copy constructor board
     * @param board - board
     */
    Board(const Board &board);

    /**
     * @return how many rows .
     */
    int getRows() const;

    /**
     * @return how many columns .
     */
    int getColumns() const;

    Color getCellValue(int i, int j) const;

    /**
     * Fills the corresponding real cell on the board , as the indexes are from 1 to the size of line/column.
     * @param i - int , index of line (1-DEFAULT_ROWS)
     * @param j - - int , index of columns (1-DEFAULT_COLUMNS)
     * @param value - the value of the cell.
     */
    void setCellAs(int i, int j, Color value);

    ~Board();

private:
    int rows;
    int columns;
    Color **grid;
};


#endif //EX2_BOARD_H
