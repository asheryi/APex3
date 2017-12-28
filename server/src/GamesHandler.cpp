#include "../include/GamesHandler.h"

bool GamesHandler::exists(string name) {
    bool result = true;
    pthread_mutex_lock(&maps_mutex);
    if (holdOnGames.find(name) == holdOnGames.end()) {
        if (activeGames.find(name) == activeGames.end()) {
            result = false;
        }
    }
    pthread_mutex_unlock(&maps_mutex);
    return result;
}

bool GamesHandler::addGame(string name, GameManager *gm) {
    if (exists(name)) {
        return false;
    } else {
        holdOnGames[name] = gm;
        return true;
    }
}

void GamesHandler::activateGame(string name, int socket) {
    pthread_mutex_lock(&maps_mutex);
    activeGames[name] = holdOnGames[name];
    holdOnGames.erase(name);
    activeGames[name]->setPlayerSid(1, socket);
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

