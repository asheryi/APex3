#include "../include/ClientCommandsManager.h"


ClientCommandsManager::ClientCommandsManager(Game *game,
                                             Display *clientDisplay, Counter *whitesCounter, Counter *blacksCounter)
        : commandsMap(), whites(whitesCounter),
          blacks(blacksCounter) {

    commandsMap["start"] = new ClientStartCommand(game, clientDisplay, whitesCounter, blacksCounter);
    commandsMap["list_games"] = new ClientListGamesCommand(clientDisplay);
    commandsMap["join"] = new ClientJoinCommand(game, clientDisplay, whitesCounter, blacksCounter);


    cout << "Socket Manager:" << socket << endl;

}

void ClientCommandsManager::executeCommand(string command, int sid) {
    int index = command.find(' ');
    string command_ = command.substr(0, index);

    if (commandsMap.find(command_) == commandsMap.end()) { // not found

        //TODO abstraction.

        cout << "Command Error For: " << command_ << " " << command << endl;

    } else { // found
        commandsMap[command_]->execute(command, sid);
    }
}

ClientCommandsManager::~ClientCommandsManager() {
    map<string, Command *>::iterator it;

    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
