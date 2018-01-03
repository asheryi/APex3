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

string GamesHandler::getHoldOnGames() {
    string gamesList_ = "";
    pthread_mutex_lock(&maps_mutex);
    map<string, GameManager *>::iterator it;
    for (it = holdOnGames.begin(); it != holdOnGames.end(); it++) {

        gamesList_ += it->first + "\n";
    }
    pthread_mutex_unlock(&maps_mutex);

    return gamesList_;
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
    StartGameArgs *startGameArgs = ((StartGameArgs *) startGameArgs_);
    GamesHandler *gamesHandler = startGameArgs->gamesHandler;
    GameManager *gameManager = startGameArgs->gameManager;
    string gameName = startGameArgs->gameName;

    gameManager->runGame();
    gamesHandler->removeGame(gameName);
    startGameArgs->threadsManager->removeThread(pthread_self());
    delete startGameArgs;
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
        return;
    }
    delete activeGames[gameName];
    activeGames.erase(gameName);
}



