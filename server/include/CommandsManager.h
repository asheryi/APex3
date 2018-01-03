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
    /**
     *CommandsManager constructor.
     * @param threadsManager -ThreadsManager, in change of threads we create.
     */
    CommandsManager(ThreadsManager *threadsManager);
    /**
    *CommandsManager deconstructor.
    */
    ~CommandsManager();
    /**
    * executeCommand. navigate the command request to the command operation.
    * @param command -string, the command to execute.
    * @param args -vector<string>, arguments required for the command.
    * @param sid -int, the socket of the client who sent the command.
    */
    void executeCommand(string command, vector<string> *args, int sid);

private:
    map<string, Command *> commandsMap;
    Command *error;
    GamesHandler *gamesHandler;

};

#endif