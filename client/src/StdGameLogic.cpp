
#include "../include/StdGameLogic.h"
#include "../include/VectorExterminator.h"

using namespace std;

StdGameLogic::StdGameLogic() : directions() {}

std::vector<Path *> *StdGameLogic::validMovePaths(const Board &board, Color color) const {

    vector<Path *> *paths = new vector<Path *>();
    // Scanning all the cells to check moves.

    int rows = board.getRows();

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= board.getColumns(); j++) {
            Cell currPotentialMove(i, j);
            Path *path;
            path = theEatingPathOfMove(board, currPotentialMove, color);
            // if the move is valid it's addded, otherwise the eating path is deleted .
            if (path->numberOfEatingDirections() > 0) {
                paths->push_back(path);
            } else {
                delete path;
            }
        }
    }

    return paths;
}

Path *StdGameLogic::theEatingPathOfMove(const Board &board, const Cell &move, Color color) const {
    Path *tmpPath = new Path(new Cell(move));
    // if there is a piece there , the move is not valid .
    if (board.getCellValue(move.getRow(), move.getColumn()) != empty) {
        return tmpPath;
    }


    for (int i = 0; i < this->directions.allDirectionsSize; i++) {
        updatePathBasedOnDirection(board, this->directions.allDirections[i], move, color, tmpPath);
    }
    return tmpPath;
}

void StdGameLogic::updatePathBasedOnDirection(const Board &board, const Cell &direction, const Cell &move, Color color,
                                              Path *path) const {
    Cell currPosition(move);
    currPosition += direction;

    if (isOutOfBounds(board, currPosition) ||
        board.getCellValue(currPosition.getRow(), currPosition.getColumn()) == color ||
        board.getCellValue(currPosition.getRow(), currPosition.getColumn()) == empty) {
        return;
    }

    while (!isOutOfBounds(board, currPosition) &&
           board.getCellValue(currPosition.getRow(), currPosition.getColumn()) != color
           && board.getCellValue(
            currPosition.getRow(), currPosition.getColumn()) != empty) {
        currPosition += direction;
    }
    // if the last cell to the direction is empty then it's not valid , as for out of bounds cell .
    if (!isOutOfBounds(board, currPosition) &&
        board.getCellValue(currPosition.getRow(), currPosition.getColumn()) == color) {
        Cell stopCell(currPosition - direction);
        path->insertMove(new Cell(direction), new Cell(stopCell));
    }
}

bool StdGameLogic::isOutOfBounds(const Board &board, const Cell &point) const {
    return point.getColumn() < 1 || point.getColumn() > board.getColumns()
           || point.getRow() < 1 || point.getRow() > board.getColumns();
}

GameStatus
StdGameLogic::currGameStatus(const Board &board, bool currPlayerhasMoves, const Color &currPlayerColor, int blacks,
                             int whites) {

    if (blacks + whites == board.getRows() * board.getColumns() || currPlayerColor == empty) {
        if (blacks == whites) {
            return tie;
        }
        return blacks > whites ? blackWon : whiteWon;
    }

    std::vector<Path *> *otherPlayerMoves = validMovePaths(board, currPlayerColor == black ? white : black);

    GameStatus gameStatus = noOneWon;
    // if the previous player had nothing to do .
    if (otherPlayerMoves->empty()) {
        if (!currPlayerhasMoves) {
            // if this player either has nothing to do , it's a tie .
            if (blacks == whites) {
                gameStatus = tie;
            } else {
                gameStatus = blacks > whites ? blackWon : whiteWon;
            }
        }
    } else if (!currPlayerhasMoves) {
        gameStatus = passTurn;
    }

    deleteVector(*otherPlayerMoves);
    delete otherPlayerMoves;

    return gameStatus;
}

