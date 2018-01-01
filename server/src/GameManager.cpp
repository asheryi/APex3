#include "../include/GameManager.h"


using namespace std;

GameManager::GameManager(int socket_) {
    playersSid[0] = socket_;
    currPlayer = 0;
}

void GameManager::writeToClient(Cell cell) {
    cout << "WRITER PLAYER IS: " << currPlayer << endl;
    cout << cell << endl;
    int n = write(playersSid[currPlayer], &cell, sizeof(cell));
    cout << "NUM OF BYTES IN WRITE TO CLIENT IS: " << n << endl;
    if (n <= 0) {
        throw "Problem with write operation";
    }
}

Cell GameManager::readFromClient() {
    Cell cell;
    cout << "READER PLAYER IS: " << currPlayer << endl;
    //cout << "Sid:" << playersSid[currPlayer] << endl;
    int n = read(playersSid[currPlayer], &cell, sizeof(cell));
    int respond;
    char msg[300];
    for (int i = 0; i < 300; i++) {
        msg[i] = 0;
    }
    //int n=read(playersSid[currPlayer],msg,300);
    //cout << msg << endl;
    //cout << n << endl;
    //cout<<"RESPOND:"<<respond<<endl;


    cout << cell << endl;

    if (n <= 0) {
        throw "Problem with read operation";
    }
    return cell;
}

GameManager::~GameManager() {
    // Close communication with the clients
    close(playersSid[0]);
    close(playersSid[1]);
}

void *GameManager::runGame(void *gameManager_) {
    cout << "test1" << endl;

    GameManager *gameManager = (GameManager *) (gameManager_);
    cout << "test2" << endl;

    Cell cell;
    Cell gameOver(-2, -2);
    Cell passTurn(-1, -1);

    do {
        try {
            cout << gameManager->testPrint << endl;
            cell = gameManager->readFromClient();
            cout << gameManager->testPrint << endl;
            gameManager->nextPlayer();
            if (cell != passTurn) {
                gameManager->writeToClient(cell);
            }
        } catch (const char *msg) {
            return (void *) (msg);
        }
    } while (cell != gameOver);
}

void GameManager::nextPlayer() {
    this->currPlayer = 1 - this->currPlayer;
}

void GameManager::setPlayerSid(int index, int sid) {
    playersSid[index] = sid;
}

int GameManager::getSid(int index) {
    return playersSid[index];
}





