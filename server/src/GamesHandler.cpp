#include "../include/GamesHandler.h"

bool GamesHandler::exists(string gameName) {
    bool result = true;
    pthread_mutex_lock(&maps_mutex);
    if (holdOnGames.find(gameName) == holdOnGames.end()) {
        if (activeGames.find(gameName) == activeGames.end()) {
            result = false;
        }
    }
    pthread_mutex_unlock(&maps_mutex);
    return result;
}

void GamesHandler::addGame(string gameName, GameManager *gm) {

    pthread_mutex_lock(&maps_mutex);
    holdOnGames[gameName] = gm;
    pthread_mutex_unlock(&maps_mutex);

}

GameManager * GamesHandler::joinGame(string gameName, int socket) {
    pthread_mutex_lock(&maps_mutex);
    if (holdOnGames.find(gameName) == holdOnGames.end()) {
        pthread_mutex_unlock(&maps_mutex);
        return NULL;
    }

    GameManager *gameManager = activeGames[gameName] = holdOnGames[gameName];
    holdOnGames.erase(gameName);
    pthread_mutex_unlock(&maps_mutex);

    gameManager->setPlayerSid(1, socket);

    return gameManager;
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
    holdOnGames["yossi"] = new GameManager(123);
    holdOnGames["is"] = new GameManager(124);
    holdOnGames["your"] = new GameManager(113);
    holdOnGames["Turn"] = new GameManager(124);
    holdOnGames["Now"] = new GameManager(113);
}

unsigned long GamesHandler::howManyHoldOnGames() const {
    return holdOnGames.size();
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

