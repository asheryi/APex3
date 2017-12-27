#include "../include/GameManager.h"


using namespace std;

GameManager::GameManager(int socket_,bool* alive_,pthread_mutex_t* alive_mutex_) {
    playersSid[0]=socket_;
    alive=alive_;
    alive_mutex=alive_mutex_;

    currPlayer = 0;
}

void GameManager::play(GameManager* gameManager) {

    gameManager->writeToClient(Cell(1, 0));
    gameManager->nextPlayer();
    gameManager->writeToClient(Cell(2, 0));
    gameManager->nextPlayer();

    gameManager->runGame(gameManager);
}

void GameManager::writeToClient(Cell cell) {
    int n = write(playersSid[currPlayer], &cell, sizeof(cell));
    if (n <= 0) {
        throw "Problem with write operation";
    }
}

Cell GameManager::readFromClient() {
    Cell cell;
    int n = read(playersSid[currPlayer], &cell, sizeof(cell));

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

void GameManager::runGame(GameManager* gameManager) {
    Cell cell;
    Cell gameOver(-2, -2);
    Cell passTurn(-1, -1);
    do {
        try {
            cell = readFromClient();
            nextPlayer();
            if (cell != passTurn) {
                writeToClient(cell);
            }
        } catch (const char *msg) {
            return;
        }
        pthread_mutex_unlock(alive_mutex);
    } while (*alive && cell != gameOver);
}

void GameManager::nextPlayer() {
    this->currPlayer = 1-this->currPlayer;
}

void GameManager::setPlayerSid(int index, int sid) {
    playersSid[index] = sid;
}





