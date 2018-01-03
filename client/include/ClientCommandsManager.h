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
#include "../include/ClientErrorCommand.h"

class ClientCommandsManager {
public:

    /**
     * Recieves the following needed for the commands :
     * @param game
     * @param clientDisplay
     * @param whitesCounter
     * @param blacksCounter
     */
    ClientCommandsManager(Game *game, Display *clientDisplay, Counter *whitesCounter, Counter *blacksCounter);

    ~ClientCommandsManager();

    /**
     * Excecutes the command , and returns true if after execution needs to read another command , false otherwise .
     * @param command
     * @param sid
     * @return
     */
    bool executeCommand(string command, int sid);


private:
    map<string, Command *> commandsMap;
    Counter *whites;
    Counter *blacks;


    Command *errorCommand;

};

#endif