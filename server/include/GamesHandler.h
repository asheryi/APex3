#ifndef GamesHandler_H
#define GamesHandler_H
#include<map>
#include "GameManager.h"
#include <pthread.h>


class GamesHandler {
private:
    map<string, GameManager *> activeGames;
    map<string, GameManager *> holdOnGames;
    pthread_mutex_t maps_mutex;

public:
    GamesHandler();
    bool exists(string name) ;
    bool addGame(string name,GameManager* gm);
    void activateGame(string name,int socket);
    unsigned long howManyHoldOnGames() const;

    string getHoldOnGames();
};
#endif

