#include "../include/ClientCommandsManager.h"


ClientCommandsManager::ClientCommandsManager(Game *game,
                                             Display *clientDisplay, Counter *whitesCounter, Counter *blacksCounter)
        : commandsMap(), whites(whitesCounter), blacks(blacksCounter) {
    this->errorCommand = new ClientErrorCommand(clientDisplay);

    commandsMap["start"] = new ClientStartCommand(game, clientDisplay, whitesCounter, blacksCounter);
    commandsMap["list_games"] = new ClientListGamesCommand(clientDisplay);
    commandsMap["join"] = new ClientJoinCommand(game, clientDisplay, whitesCounter, blacksCounter);
}

bool ClientCommandsManager::executeCommand(string command, int sid) {
    int index = command.find(' ');
    string command_ = command.substr(0, index);

    if (commandsMap.find(command_) == commandsMap.end()) { // not found
        return errorCommand->execute(command_, sid);
    } else { // found
        return commandsMap[command_]->execute(command, sid);
    }
}

ClientCommandsManager::~ClientCommandsManager() {
    map<string, Command *>::iterator it;

    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }

    delete errorCommand;
}
