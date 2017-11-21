// 318225851
// Yishay Asher

#ifndef EX2_CELL_H
#define EX2_CELL_H

// Represents a cell in a matrix . (in this case board)

class Cell {
private:
    int row;
    int column;
public:
    Cell();

    Cell(int row, int column);

    Cell(const Cell &p);

    int getColumn() const;

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
     * @param p - othe cell .
     * @return true if and only if this row = to p's and same for column .
     */
    bool operator==(Cell p);
    bool operator!=(Cell p);
    };


#endif //EX2_CELL_H
