#ifndef CommandsManager_H
#define CommandsManager_H

#include <map>
#include "GamesHandler.h"
#include "StartCommand.h"
#include "../include/ErrorCommand.h"
#include "ListGamesCommand.h"
#include "../include/JoinCommand.h"
#include "ThreadsManager.h"

class CommandsManager {
public:
    CommandsManager(ThreadsManager *threadsManager);

    ~CommandsManager();

    void executeCommand(string command, vector<string> *args, int sid);

private:
    map<string, Command *> commandsMap;
    Command *error;
    GamesHandler *gamesHandler;

};

#endif