#include <sstream>
#include "../include/GameManager.h"


using namespace std;

GameManager::GameManager(int socket_) {
    playersSid[0] = socket_;
    currPlayer = 0;
}

void GameManager::writeToClient(Cell cell) {
    //cout << "WRITER PLAYER IS: " << currPlayer << endl;
    cout << cell << endl;
    int n = write(playersSid[currPlayer], &cell, sizeof(cell));
    //cout << "NUM OF BYTES IN WRITE TO CLIENT IS: " << n << endl;
    int sid = playersSid[currPlayer];
    if (n == -1) {
        cout << "Problem with write operation sid(" << sid << ")" << endl;
        throw "";
    } else if (n == 0) {
        cout << "Client disconnected (sid" << sid << ")" << endl;
        throw "";
    }
}

Cell GameManager::readFromClient() {
    Cell cell;
    //cout << "READER PLAYER IS: " << currPlayer << endl;
    int n = read(playersSid[currPlayer], &cell, sizeof(cell));

    //cout << cell << endl;
    int sid = playersSid[currPlayer];

    if (n == -1) {
        cout << "Problem with write operation sid(" << sid << ")" << endl;
        throw "";
    } else if (n == 0) {
        cout << "Client disconnected (sid" << sid << ")" << endl;
        throw "";
    }

    return cell;
}

GameManager::~GameManager() {
    // Close communication with the clients
    close(playersSid[0]);
    close(playersSid[1]);
}

void GameManager::runGame() {
    Cell cell;
    Cell gameOver(-2, -2);
    Cell passTurn(-1, -1);

    do {
        try {
            cout << this->testPrint << endl;
            cell = this->readFromClient();
            cout << this->testPrint << endl;
            this->nextPlayer();
            if (cell != passTurn) {
                this->writeToClient(cell);
            }
        } catch (const char *msg) {
            break;
        }
    } while (cell != gameOver);

    cout << "GAME IS OVER" << endl;
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





