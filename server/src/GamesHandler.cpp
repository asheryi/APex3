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
    StartGameArgs *startGameArgs = ((StartGameArgs *) startGameArgs_);
    GamesHandler *gamesHandler = startGameArgs->gamesHandler;
    GameManager *gameManager = startGameArgs->gameManager;
    //cout << "almost reading gameName" << endl;
    //cout << startGameArgs->gameName << endl;
    string gameName = startGameArgs->gameName;
    cout << "almost running game , just a sec" << endl;
    cout << gameManager->testPrint << endl;
    gameManager->runGame();
    gamesHandler->removeGame(gameName);
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
    }
    delete activeGames[gameName];
    activeGames.erase(gameName);
}
/*
void GamesHandler::removeGame(GameManager *gameManager) {
    map<string, GameManager *>::iterator it;
    string gameName = "";
    for (it = holdOnGames.begin(); it != holdOnGames.end(); it++) {
        if (it->second == gameManager) {
            string gameName = it->first;
            break;
        }
    }
    if (gameName != NULL) {
        delete gameManager;
        holdOnGames.erase(gameName);
        return;
    }

    for (it = activeGames.begin(); it != activeGames.end(); it++) {
        if (it->second == gameManager) {
            string gameName = it->first;
            break;
        }
    }
    if (gameName != NULL) {
        delete gameManager;
        activeGames.erase(gameName);
    }

}
*/



