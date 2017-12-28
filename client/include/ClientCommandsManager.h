#ifndef CommandsManager_H
#define CommandsManager_H

#include <map>
#include "ClientStartCommand.h"
#include "ClientListGamesCommand.h"
#include "ClientJoinCommand.h"
#include "RemoteInputController.h"
#include "RemoteOutputController.h"
#include "Game.h"
#include <string>
#include <vector>

class ClientCommandsManager {
public:

    ClientCommandsManager(int socket_, RemoteOutputController *toServer, RemoteInputController *fromServer, Game *game,
                          Display *clientDisplay);

    ~ClientCommandsManager();

    void executeCommand(string command);

private:
    int socket;
    map<string, Command *> commandsMap;
    RemoteOutputController *toServer;
    RemoteInputController *fromServer;
};

#endif