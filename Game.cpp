// 318225851
// Yishay Asher

#include "Game.h"
#include "StdGameLogic.h"
#include "Console.h"
#include "HumanPlayer.h"
#include "ConsoleController.h"
#include "StandardAttack.h"
#include "AIplayer.h"
#include "VectorExterminator.h"

using namespace std;

Game::Game(int rows, int columns) {
    std::vector<Cell *> blacks(2), whites(2);

    blacks[0] = new Cell(rows / 2, columns / 2 + 1);
    blacks[1] = new Cell(rows / 2 + 1, columns / 2);

    whites[0] = new Cell(rows / 2, columns / 2);
    whites[1] = new Cell(rows / 2 + 1, columns / 2 + 1);

    this->board = new Board(rows, columns, blacks, whites);

    this->gameLogic = new StdGameLogic();
    this->display = new Console(*board);

    PlayerController *pc1 = new ConsoleController();
    PlayerController *pc2 = new ConsoleController();


    this->players[0] = new HumanPlayer(pc1, black);
    this->players[0]->updateScore(2);
    this->players[1] = new AIplayer(pc2, *board, *gameLogic, white);
    this->players[1]->updateScore(2);

    this->currPlayer = 0;

    deleteVector(blacks);
    deleteVector(whites);
}

void Game::nextPlayer(Color &currPlayerColor) {
    this->currPlayer = (this->currPlayer + 1) % 2;
    currPlayerColor = players[this->currPlayer]->getColor();
}

void Game::start() {
    // pseudo code of AI algo :
    // create board for each move m .
    //

    Color currPlayerColor(players[currPlayer]->getColor());

    std::vector<Path *> *movePaths = this->gameLogic->validMovePaths(*board, currPlayerColor);
    bool currPlayerhasMoves = !movePaths->empty();

    GameStatus gameStatus = gameLogic->currGameStatus(*board, currPlayerhasMoves, currPlayerColor,
                                                      players[0]->getScore(),
                                                      players[1]->getScore());

    while (gameStatus == noOneWon || gameStatus == passTurn) {

        bool passTurnState = gameStatus == passTurn;
        // ?
        this->display->show(*movePaths, &currPlayerColor, passTurnState);

        if (!passTurnState) {
            // AI recieves board in constructor .
            Cell *move = players[currPlayer]->chooseAndReturnMove(*movePaths);
            Path *currPathOfLandingPoint;

            while (true) {
                if (move == NULL) {
                    display->showError(notIntegers);
                } else if (isOutOfBounds(*move)) {
                    display->showError(outOfBounds);
                } else {
                    currPathOfLandingPoint = pathOfLandingPoint(*movePaths, *move);
                    if (currPathOfLandingPoint == 0) {
                        display->showError(notValidMove);
                    } else {
                        display->showMoveDone(*move, currPlayerColor);
                        break;
                    }
                }
                delete move;
                move = players[currPlayer]->chooseAndReturnMove(*movePaths);
            }
            this->attackThose(*currPathOfLandingPoint, currPlayerColor);

            delete move;
        }

        deleteVector(*movePaths);
        delete movePaths;

        nextPlayer(currPlayerColor);
        movePaths = this->gameLogic->validMovePaths(*board, currPlayerColor);
        currPlayerhasMoves = !movePaths->empty();

        gameStatus = gameLogic->currGameStatus(*board, currPlayerhasMoves, currPlayerColor, players[0]->getScore(),
                                               players[1]->getScore());
    }

    deleteVector(*movePaths);
    delete movePaths;

    display->showEndGameStatus(gameStatus);
}

Path *Game::pathOfLandingPoint(std::vector<Path *> paths, const Cell &point) {
    for (unsigned i = 0; i < paths.size(); i++) {
        if (paths[i]->getLanding() == point) {
            return paths[i];
        }
    }
    return 0;
}

bool Game::isOutOfBounds(const Cell &point) {
    return point.getColumn() < 1 || point.getColumn() > board->getColumns()
           || point.getRow() < 1 || point.getRow() > board->getColumns();
}

void Game::attackThose(const Path &path, Color currPlayerColor) {
    StandardAttack attack(path);
    while (attack.hasNext()) {
        Cell c = attack.getNext();
        this->board->setCellAs(c.getRow(), c.getColumn(), currPlayerColor);
    }
    updateScores(*players[currPlayer], *players[1 - currPlayer], path.score());
}

void Game::updateScores(Player &curr, Player &other, int score) {
    curr.updateScore(curr.getScore() + score);
    other.updateScore(other.getScore() - score + 1);
}

Game::~Game() {
    delete players[0];
    delete players[1];
    delete display;
    delete gameLogic;
    delete board;
}




