// 318225851
// Yishay Asher

#include "../include/Game.h"
#include "../include/StdGameLogic.h"
#include "../include/Console.h"
#include "../include/ConsoleController.h"
#include "../include/StandardAttack.h"
#include "../include/AIplayer.h"
#include "../include/VectorExterminator.h"
#include "../include/HumanPlayer.h"
#include "../include/HumanConsole.h"
#include "../include/AIConsole.h"

using namespace std;

Game::Game(int rows, int columns) {
    std::vector<Cell *> blacks(2), whites(2);

    blacks[0] = new Cell(rows / 2, columns / 2 + 1);
    blacks[1] = new Cell(rows / 2 + 1, columns / 2);

    whites[0] = new Cell(rows / 2, columns / 2);
    whites[1] = new Cell(rows / 2 + 1, columns / 2 + 1);

    this->board = new Board(rows, columns, blacks, whites);



    this->gameLogic = new StdGameLogic();
    createPlayers(blacks.size(), whites.size());

    deleteVector(blacks);
    deleteVector(whites);
}

void Game::createPlayers(int blacks, int whites) {
    Counter *blacksCounter = new Counter(blacks);
    Counter *whitesCounter = new Counter(whites);


    PlayerController *pc1 = new ConsoleController();
    PlayerController *pc2 = new ConsoleController();
    HumanPlayer *humanPlayer = new HumanPlayer(pc1, blacksCounter, black);
    this->players[0] = humanPlayer;
    this->players[0]->updateScore(2);

    this->displays[0] = new HumanConsole(*board);
    this->displays[0]->showMenu();

    char selection = humanPlayer->getMenuSelection();
    while (selection != 'h' && selection != 'a') {
        this->displays[0]->showMenu();
        selection = humanPlayer->getMenuSelection();
    }
    if (selection == 'h') {
        this->displays[1] = new HumanConsole(*board);
        this->players[1] = new HumanPlayer(pc2, whitesCounter, white);
    } else {
        this->displays[1] = new AIConsole(*board);
        this->players[1] = new AIplayer(pc2, whitesCounter, *blacksCounter, *board, *gameLogic, white);
    }
    this->players[1]->updateScore(2);

    this->currPlayer = 0;
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
        this->displays[currPlayer]->show(*movePaths, &currPlayerColor, passTurnState, players[0]->getScore(),
                                         players[1]->getScore());


        if (!passTurnState) {
            // AI recieves board in constructor .
            Cell *move = players[currPlayer]->chooseAndReturnMove(*movePaths);
            Path *currPathOfLandingPoint;

            while (true) {
                if (move == NULL) {
                    displays[currPlayer]->showError(notIntegers);
                } else if (isOutOfBounds(*move)) {
                    displays[currPlayer]->showError(outOfBounds);
                } else {
                    currPathOfLandingPoint = pathOfLandingPoint(*movePaths, *move);
                    if (currPathOfLandingPoint == 0) {
                        displays[currPlayer]->showError(notValidMove);
                    } else {
                        displays[currPlayer]->showMoveDone(*move, currPlayerColor);
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

    displays[currPlayer]->showEndGameStatus(gameStatus);
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
    updateScores(*players[currPlayer], *players[1 - currPlayer], path.length());
}

void Game::updateScores(Player &curr, Player &other, int score) {
    curr.updateScore(curr.getScore() + score);
    other.updateScore(other.getScore() - score + 1);
}

Game::~Game() {
    delete players[0];
    delete players[1];
    delete displays[0];

    delete displays[1];
    delete gameLogic;
    delete board;
}




