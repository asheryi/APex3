// 318225851
// Yishay Asher

#include "../include/Cell.h"


Cell::Cell(int row, int column) : row(row), column(column) {}

int Cell::getColumn() const {
    return this->column;
}

int Cell::getRow() const {
    return row;
}

Cell &Cell::operator+=(Cell p) {
    this->row += p.row;
    this->column += p.column;
    return *this;
}

Cell Cell::operator-(Cell p) {
    return Cell(getRow()-p.getRow(),getColumn()-p.getColumn());
}
Cell::Cell(const Cell &p) {
    this->row = p.row;
    this->column = p.column;
}

Cell::Cell() : row(0), column(0) {}

bool Cell::operator==(Cell p) {
    return row == p.row && column == p.column;
}
bool Cell::operator!=(Cell p) {
    return ((row != p.row) || (column != p.column));
}

ostream &operator<<(ostream &stream, const Cell &cell) {
    stream << "(" << cell.row << "," << cell.column << ")";
    return stream;
}

