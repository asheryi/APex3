#ifndef CommandsManager_H
#define CommandsManager_H

#include <map>
#include "GamesHandler.h"
#include "../include/StartCommand.h"
#include "../include/ErrorCommand.h"
#include "../include/ListGamesCommand.h"
#include "../include/JoinCommand.h"
class CommandsManager {
public:
    CommandsManager();
    ~CommandsManager();
    void executeCommand(string command,
                        vector<string>* args);
private:
    map<string, Command *> commandsMap;
    Command* error;
    GamesHandler gamesHandler;
};
#endif