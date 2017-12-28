#ifndef CommandsManager_H
#define CommandsManager_H
#include <map>
#include "ClientStartCommand.h"
#include "ClientListGamesCommand.h"
#include "ClientJoinCommand.h"
#include "RemoteInputController.h"
#include "RemoteOutputController.h"
#include <string>
#include <vector>

class ClientCommandsManager {
public:
    ClientCommandsManager(int socket_);
    ~ClientCommandsManager();
    void executeCommand(string command);
private:
    int socket;
    map<string, Command *> commandsMap;
};
#endif