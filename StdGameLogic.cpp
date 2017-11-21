// 318225851
// Yishay Asher

#include "StdGameLogic.h"

using namespace std;

StdGameLogic::StdGameLogic(const Board &b) : board(b), directions() {}

//TODO:const removed
std::vector<Path *> *StdGameLogic::validPathsOfMoves(Color color) const {

    //TODO:Why *paths ,paths??
    vector<Path *> *paths = new vector<Path *>();
    // Scanning all the cells to check moves.

    int rows = board.getRows();

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= board.getColumns(); j++) {
            if (i == 4 && j == 3) {
                cout << "IM HERE";
            }

            Cell currPotentialMove(i, j);
            Path *path;
            path = isValidMove(currPotentialMove, color);
            // if the move is valid it's addded.
            if (path->movesCount() > 0) {
                paths->push_back(path);
            } else {
                delete path;
            }
        }
    }

    return paths;
}

//TODO:const removed
Path *StdGameLogic::isValidMove(const Cell &move, Color color) const {
    Path *tmpPath = new Path(new Cell(move));
    // if there is a piece there , the move is not valid .
    if (board.getCellValue(move.getRow(), move.getColumn()) != empty) {
        return tmpPath;
    }
    for (int i = 0; i < 8; i++) {
        isValidDirection(this->directions.allDirections[i], move, color, tmpPath);
        /*if (path!=NULL) {
            tmpPaths.push_back(path);
        }*/
    }
    return tmpPath;
}

void StdGameLogic::isValidDirection(const Cell &direction, const Cell &move, Color color, Path *path) const {
    Cell currPosition(move);
    currPosition += direction;

    if (isOutOfBounds(currPosition) || board.getCellValue(currPosition.getRow(), currPosition.getColumn()) == color ||
        board.getCellValue(currPosition.getRow(), currPosition.getColumn()) == empty) {
        return;
    }

    while (!isOutOfBounds(currPosition) &&
           board.getCellValue(currPosition.getRow(), currPosition.getColumn()) != color
           && board.getCellValue(
            currPosition.getRow(), currPosition.getColumn()) != empty) {
        currPosition += direction;
    }
    // if the last cell to the direction is empty then it's not valid , as for out of bounds cell .
    if (!isOutOfBounds(currPosition) &&
        board.getCellValue(currPosition.getRow(), currPosition.getColumn()) == color) {
        Cell stopCell(currPosition - direction);
        path->insertMove(new Cell(direction), new Cell(stopCell));
    }
}

bool StdGameLogic::isOutOfBounds(const Cell &point) const {
    return point.getColumn() < 1 || point.getColumn() > board.getColumns()
           || point.getRow() < 1 || point.getRow() > board.getColumns();
}

void StdGameLogic::updateFlipLocationsInThisDirection(std::vector<Cell *> &flipLocations, const Cell &direction,
                                                      const Cell &startCell, Color currPlayerColor) const {
    Cell currPosition(startCell);
    while (!isOutOfBounds(currPosition)
           && board.getCellValue(currPosition.getRow(), currPosition.getColumn()) != currPlayerColor
           && board.getCellValue(currPosition.getRow(), currPosition.getColumn()) != empty) {
        flipLocations.push_back(new Cell(currPosition));
        currPosition += direction;
    }
}

GameStatus StdGameLogic::currGameStatus(const Color &currPlayerColor, int blacks, int whites) {

    if (blacks + whites == board.getRows() * board.getColumns()) {
        if (blacks == whites) {
            return tie;
        }
        return blacks > whites ? blackWon : whiteWon;
    }

    std::vector<Path *> *currPlayerMoves = validPathsOfMoves(currPlayerColor);
    std::vector<Path *> *otherPlayerMoves = validPathsOfMoves(currPlayerColor == black ? white : black);

    GameStatus gameStatus = noOneWon;
    // if the previous player had nothing to do .
    if (otherPlayerMoves->empty()) {
        if (currPlayerMoves->empty()) {
            // if this player either has nothing to do , it's a tie .
            if (blacks == whites) {
                gameStatus = tie;
            }
            gameStatus = blacks > whites ? blackWon : whiteWon;
        }
    } else if (currPlayerMoves->empty()) {
        gameStatus = passTurn;
    }

    deleteVector(*currPlayerMoves);
    deleteVector(*otherPlayerMoves);

    delete currPlayerMoves;
    delete otherPlayerMoves;

    return gameStatus;
}

void StdGameLogic::deleteVector(std::vector<Path *> &moves) {

    for (unsigned i = 0; i < moves.size(); i++) {
        delete moves[i];
    }
    moves.clear();
}

