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

    bool isWaitingGame(string gameName);


public:
    GamesHandler();

    bool exists(string gameName);


    GameManager *joinGame(string gameName, int sid);

    void addGame(string gameName, GameManager *gm);

    void removeGame(string gameName);

    //void removeGame(GameManager *gameManager);

    static void *joinAndStartGame(void *startGameArgs_);

    vector<string> *getHoldOnGames();

    ~GamesHandler();

    unsigned long howManyHoldOnGames();

    typedef struct StartGameArgs {
        GamesHandler *gamesHandler;
        GameManager *gameManager;
        string gameName;
    } StartGameArgs;
};

#endif

