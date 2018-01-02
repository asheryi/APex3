#include "../include/GamesHandler.h"

bool GamesHandler::exists(string gameName) {
    bool result = true;
    pthread_mutex_lock(&maps_mutex);
    if (holdOnGames.find(gameName) == holdOnGames.end()) {
        if (activeGames.find(gameName) == activeGames.end()) { // if not found on neither map .
            result = false;
        }
    }
    pthread_mutex_unlock(&maps_mutex);
    return result;
}

bool GamesHandler::isWaitingGame(string gameName) {
    bool result = true;
    pthread_mutex_lock(&maps_mutex);
    if (holdOnGames.find(gameName) == holdOnGames.end()) { // is waiting game .
        result = false;
    }
    pthread_mutex_unlock(&maps_mutex);
    return result;
}

void GamesHandler::addGame(string gameName, GameManager *gm) {

    pthread_mutex_lock(&maps_mutex);
    holdOnGames[gameName] = gm;
    pthread_mutex_unlock(&maps_mutex);

}

vector<string> *GamesHandler::getHoldOnGames() {
    vector<string> *gamesList = new vector<string>();
    pthread_mutex_lock(&maps_mutex);
    map<string, GameManager *>::iterator it;
    for (it = holdOnGames.begin(); it != holdOnGames.end(); it++) {
        gamesList->push_back(it->first);
    }
    pthread_mutex_unlock(&maps_mutex);

    return gamesList;
}

GamesHandler::GamesHandler() : holdOnGames(), maps_mutex(), activeGames() {

}

unsigned long GamesHandler::howManyHoldOnGames() {
    pthread_mutex_lock(&maps_mutex);

    unsigned long size = holdOnGames.size();
    pthread_mutex_unlock(&maps_mutex);
    return size;
}

GamesHandler::~GamesHandler() {
    pthread_mutex_lock(&maps_mutex);
    map<string, GameManager *>::iterator it;
    for (it = holdOnGames.begin(); it != holdOnGames.end(); it++) {
        delete it->second;
    }
    for (it = activeGames.begin(); it != activeGames.end(); it++) {
        delete it->second;
    }
    pthread_mutex_unlock(&maps_mutex);
}


void *GamesHandler::joinAndStartGame(void *startGameArgs_) {
    StartGameArgs *startGameArgs = (StartGameArgs *) startGameArgs_;
    string gameName = startGameArgs->gameName;
    GamesHandler *gamesHandler = startGameArgs->gamesHandler;
    GameManager *gameManager = startGameArgs->gameManager;
    gameManager->runGame();
    gamesHandler->removeGame(gameName);
}

GameManager *GamesHandler::joinGame(string gameName, int sid) {
    if (!isWaitingGame(gameName)) {
        return NULL;
    }
    pthread_mutex_lock(&maps_mutex);

    GameManager *gameManager = activeGames[gameName] = holdOnGames[gameName];
    holdOnGames.erase(gameName);
    pthread_mutex_unlock(&maps_mutex);

    gameManager->setPlayerSid(1, sid);

    return gameManager;
}

void GamesHandler::removeGame(string gameName) {
    if (!this->exists(gameName)) {
        return;
    }
    if (this->isWaitingGame(gameName)) {
        delete holdOnGames[gameName];
        holdOnGames.erase(gameName);
    }
    delete activeGames[gameName];
    activeGames.erase(gameName);
}



