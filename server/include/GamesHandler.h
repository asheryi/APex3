#ifndef GamesHandler_H
#define GamesHandler_H

#include<map>
#include "GameManager.h"
#include <pthread.h>
#include <vector>


class GamesHandler {
private:
    map<string, GameManager *> activeGames;
    map<string, GameManager *> holdOnGames;
    pthread_mutex_t maps_mutex;

public:
    GamesHandler();

    bool exists(string gameName);

    void addGame(string gameName, GameManager *gm);

    GameManager * joinGame(string gameName, int socket);

    unsigned long howManyHoldOnGames() const;

    vector<string> *getHoldOnGames();

    ~GamesHandler();

    unsigned long howManyHoldOnGames();
};

#endif

