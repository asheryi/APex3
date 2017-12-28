

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdlib>
#include "../include/Game.h"
#include "../include/StdGameLogic.h"
#include "../include/Console.h"
#include "../include/ConsoleController.h"
#include "../include/StandardAttack.h"
#include "../include/VectorExterminator.h"
#include "../include/HumanPlayer.h"
#include "../include/HumanConsole.h"
#include "../include/AIConsole.h"
#include "../include/AIplayer.h"
#include "../include/RemoteOutputController.h"
#include "../include/RemoteInputController.h"
#include "../include/RemoteConsole.h"
#include "../include/ClientCommandsManager.h"

using namespace std;

Game::Game(int rows, int columns, const char *serverIp, int serverPort)
        : players(), displays(), currPlayer(), serverIP(serverIp), serverPort(serverPort) {
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


    PlayerController *tempController = new ConsoleController();
    HumanPlayer *humanPlayer = new HumanPlayer(tempController);

    Display *display = new HumanConsole();
    display->showMenu();

    int selection = humanPlayer->getMenuSelection();

    while (selection < 1 || selection > 3) {
        display->showMenu();
        selection = humanPlayer->getMenuSelection();
    }

    bool normal = selection == 1;
    bool againstAI = selection == 2;
    bool network = selection == 3;

    if (normal || againstAI) {
        PlayerController *pc2 = new ConsoleController();

        humanPlayer->modifyPlayerColor(black, blacksCounter);
        this->players[0] = humanPlayer;
        this->displays[0] = display;
        if (normal) {
            this->players[1] = new HumanPlayer(pc2, whitesCounter, white);
            this->displays[1] = new HumanConsole();
        } else {
            this->displays[1] = new AIConsole();
            this->players[1] = new AIplayer(pc2, whitesCounter, *blacksCounter, *board, *gameLogic, white);
        }
    } else if (network) {
        try {
            HumanPlayer *activePlayer = humanPlayer;

            int clientSocket = this->connectToServer();
            RemoteOutputController *toServer = new RemoteOutputController(tempController, clientSocket);
            humanPlayer->setController(toServer);
            RemoteInputController *fromServer = new RemoteInputController(clientSocket);
            HumanPlayer *rivalPlayer = new HumanPlayer(fromServer);

            Display *rivalDisplay = new RemoteConsole();

            activePlayer->modifyPlayerColor(black, blacksCounter);
            rivalPlayer->modifyPlayerColor(white, whitesCounter);
            this->displays[0] = display;
            this->displays[1] = rivalDisplay;

            this->players[0] = activePlayer;
            this->players[1] = rivalPlayer;

            string command;
            cout << "Socket PLayer:" << clientSocket << endl;
            cin >> command;
            ClientCommandsManager *cm = new ClientCommandsManager(clientSocket, toServer, fromServer, this, display);
            while (command == "list_games") {
                cm->executeCommand(command);
                cin >> command;
            }
        } catch (const char *msg) {
            cout << "Failed to connect to server. Reason: " << msg << endl;
            exit(-1);
        }
    }

    this->players[0]->updateScore(blacks);
    this->players[1]->updateScore(whites);

    this->currPlayer = 0;

}


void Game::prepareGame(int playerIndex) {
    if (playerIndex == 0) {
        return;
    }

    // Swap from first to be second
    Display *tempDisplay = this->displays[0];
    this->displays[0] = this->displays[1];
    this->displays[1] = tempDisplay;

    Player *tempPlayer = this->players[0];
    this->players[0] = this->players[1];
    this->players[1] = tempPlayer;
}

int Game::connectToServer() {
    int clientSocket = 0;
    try {
        // Create a socket point
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1) {
            throw "Error opening socket";
        }
        // Convert the ip string to a network address
        struct in_addr address = {};
        if (!inet_aton(serverIP, &address)) {
            throw "Can't parse IP address";
        }
        // Get a hostent structure for the given host address
        struct hostent *server;
        server = gethostbyaddr((const void *) &address, sizeof
                address, AF_INET);
        if (server == NULL) {
            throw "Host is unreachable";
        }
        // Create a structure for the server address
        struct sockaddr_in serverAddress = {};
        bzero((char *) &address, sizeof(address));
        serverAddress.sin_family = AF_INET;
        memcpy((char *) &serverAddress.sin_addr.s_addr, (char
        *) server->h_addr, server->h_length);
        // htons converts values between host and network byte orders
        serverAddress.sin_port = htons(serverPort);
        // Establish a connection with the TCP server
        if (connect(clientSocket, (struct sockaddr
        *) &serverAddress, sizeof(serverAddress)) == -1) {
            throw "Error connecting to server";
        }
        cout << "Connected to server" << endl;
    } catch (const char *msg) {
        throw "Error connecting to server";
    }
    return clientSocket;
}


void Game::nextPlayer(Color &currPlayerColor) {
    this->currPlayer = (this->currPlayer + 1) % 2;
    currPlayerColor = players[this->currPlayer]->getColor();
}

void Game::start() {
    Cell noMove(-1, -1);

    Color currPlayerColor(players[currPlayer]->getColor());

    std::vector<Path *> *movePaths = this->gameLogic->validMovePaths(*board, currPlayerColor);
    bool currPlayerhasMoves = !movePaths->empty();

    GameStatus gameStatus = gameLogic->currGameStatus(*board, currPlayerhasMoves, currPlayerColor,
                                                      players[0]->getScore(),
                                                      players[1]->getScore());

    while (gameStatus == noOneWon || gameStatus == passTurn) {

        bool passTurnState = gameStatus == passTurn;
        this->displays[currPlayer]->show(*board, *movePaths, currPlayerColor, passTurnState, players[0]->getScore(),
                                         players[1]->getScore());

        try {
            if (!passTurnState) {
                //cout << "Before choose move" << endl;
                Cell *move = players[currPlayer]->chooseAndReturnMove(*movePaths);
                Path *currPathOfLandingPoint;
                //cout << "After choose move" << endl;

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
                this->players[currPlayer]->update(*move);

                delete move;
            } else {
                this->players[currPlayer]->update(noMove);
            }
        } catch (const char *errorMsg) {
            displays[0]->showMessage(errorMsg);
            displays[1]->showMessage(errorMsg);
        }


        deleteVector(*movePaths);
        delete movePaths;

        nextPlayer(currPlayerColor);
        movePaths = this->gameLogic->validMovePaths(*board, currPlayerColor);
        currPlayerhasMoves = !movePaths->empty();

        gameStatus = gameLogic->currGameStatus(*board, currPlayerhasMoves, currPlayerColor, players[0]->getScore(),
                                               players[1]->getScore());
    }
    displays[currPlayer]->show(*board, *movePaths, empty, false, players[0]->getScore(), players[1]->getScore());

    deleteVector(*movePaths);
    delete movePaths;

    Cell end(-2, -2);
    displays[currPlayer]->showEndGameStatus(gameStatus);
    this->players[currPlayer]->update(end);

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




