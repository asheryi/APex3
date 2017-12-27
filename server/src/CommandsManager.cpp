#include "../include/CommandsManager.h"
CommandsManager::CommandsManager() : commandsMap(),gamesHandler() {
    error = new ErrorCommand();

    commandsMap["start"] = new StartCommand();
    commandsMap["list_games"] = new ListGamesCommand(gamesHandler);
    commandsMap["join"] = new JoinCommand();
}
void CommandsManager::executeCommand(string
                                     command, vector<string>* args) {
    if ( commandsMap.find(command) == commandsMap.end() ) { // not found
        this->error->execute(*args);
    } else { // found
        commandsMap[command]->execute(*args);
    }
}
CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;

    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }

    delete error;
}
