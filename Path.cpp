
#include "Path.h"

using namespace std;

Path::Path(Cell *landing_) : landing(landing_) {

}

void Path::insertMove(Cell *direction, Cell *stopCell) {
    directions.push_back(direction);
    stopCells.push_back(stopCell);
}

Cell *Path::getStopCell(int index) const {
    return stopCells[index];
}

Cell Path::getLanding() const {
    return *landing;
}

Cell *Path::getDirection(int index) const {
    return directions[index];
}

int Path::movesCount() const {
    return directions.size();
}

Path::~Path() {
    delete landing;
    for (unsigned int i = 0; i < directions.size(); i++) {
        delete directions[i];
        delete stopCells[i];
    }
    directions.clear();
    stopCells.clear();
}

Path::Path(const Path &other) {
    this->landing = new Cell(*other.landing);
    for (unsigned int i = 0; i < other.directions.size(); i++) {
        this->directions.push_back(new Cell(*other.directions[i]));
        this->stopCells.push_back(new Cell(*other.stopCells[i]));
    }
}

int Path::score() const {
    int result = 1;
    for (unsigned int i = 0; i < this->directions.size(); i++) {
        Cell *currStopCell = stopCells[i];
        int flipsOnThatDirection = abs(currStopCell->getColumn() - landing->getColumn());
        if (flipsOnThatDirection == 0) {
            flipsOnThatDirection = abs(currStopCell->getRow() - landing->getColumn());
        }
        result += flipsOnThatDirection;
    }
    return result;
}
/*
int Path::abs(int x) {
    return x >= 0 ? x : -x;
}
 */



