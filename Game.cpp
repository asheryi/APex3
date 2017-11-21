// 318225851
// Yishay Asher

#include "Game.h"
#include "StdGameLogic.h"
#include "Console.h"
#include "HumanPlayer.h"
#include "ConsoleController.h"
#include "Attack.h"
#include "StandardAttack.h"

using namespace std;

Game::Game(int rows, int columns) {
    std::vector<Cell *> blacks(2), whites(2);

    blacks[0] = new Cell(2, 3);
    blacks[1] = new Cell(3, 2);

    whites[0] = new Cell(2, 2);
    whites[1] = new Cell(3, 3);

    this->blacks = blacks.size();
    this->whites = whites.size();

    this->board = new Board(rows, columns, blacks, whites);


    this->gameLogic = new StdGameLogic(*board);
    this->display = new Console(*board);
    this->players[0] = new HumanPlayer(black);
    PlayerController *pc1 = new ConsoleController();
    this->players[0]->setController(pc1);
    this->players[0]->updateScore(blacks.size());
    this->players[1] = new HumanPlayer(white);
    PlayerController *pc2 = new ConsoleController();
    this->players[1]->setController(pc2);
    this->players[1]->updateScore(whites.size());
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
    GameStatus gameStatus = gameLogic->currGameStatus(currPlayerColor, blacks, whites);
    while (gameStatus == noOneWon || gameStatus == passTurn) {
        std::vector<Path *> *movePaths = this->gameLogic->validPathsOfMoves(currPlayerColor);

        bool passTurnState = gameStatus == passTurn;
        // ?
        this->display->show(*movePaths, &currPlayerColor, passTurnState);

        if (!passTurnState) {
            // AI recieves board in constructor .
            Cell *move = players[currPlayer]->makeMove();
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
                        break;
                    }
                }
                delete move;
                move = players[currPlayer]->makeMove();
            }
            this->attackThose(*currPathOfLandingPoint, currPlayerColor);

            delete move;
        }

        deleteVector(*movePaths);
        delete movePaths;

        nextPlayer(currPlayerColor);
        gameStatus = gameLogic->currGameStatus(currPlayerColor, blacks, whites);
    }

    display->showEndGameStatus(gameLogic->currGameStatus(currPlayerColor, blacks, whites));
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
    int score = 0;
    while (attack.hasNext()) {
        Cell c = attack.getNext();
        this->board->setCellAs(c.getRow(), c.getColumn(), currPlayerColor);
        score++;
    }
    updateScores(*players[currPlayer], *players[1 - currPlayer], score);
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




