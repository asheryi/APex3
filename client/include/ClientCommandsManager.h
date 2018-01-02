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


    ClientCommandsManager(Game *game, Display *clientDisplay, Counter *whitesCounter, Counter *blacksCounter);

    ~ClientCommandsManager();

    void executeCommand(string command, int sid);


private:
    int socket;
    map<string, Command *> commandsMap;
    Counter *whites;
    Counter *blacks;

};

#endif