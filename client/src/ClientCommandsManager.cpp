#include "../include/ClientCommandsManager.h"


ClientCommandsManager::ClientCommandsManager(int socket_, RemoteOutputController *toServer,
                                             RemoteInputController *fromServer, Game *game,
                                             Display *clientDisplay, Counter *whitesCounter, Counter *blacksCounter)
        : socket(socket_), commandsMap(), toServer(toServer), fromServer(fromServer), whites(whitesCounter),
          blacks(blacksCounter) {

    commandsMap["start"] = new ClientStartCommand(game, clientDisplay, socket_, whitesCounter, blacksCounter);
    commandsMap["list_games"] = new ClientListGamesCommand(socket_, clientDisplay);
    commandsMap["join"] = new ClientJoinCommand(game, clientDisplay, socket_, whitesCounter, blacksCounter);


    cout << "Socket Manager:" << socket << endl;

}

void ClientCommandsManager::executeCommand(string command) {
    int index = command.find(' ');
    string command_ = command.substr(0, index);

    if (commandsMap.find(command_) == commandsMap.end()) { // not found

        //TODO abstraction.

        cout << "Command Error For: " << command_ << " " << command << endl;

    } else { // found
        commandsMap[command_]->execute(command);
    }
}

ClientCommandsManager::~ClientCommandsManager() {
    map<string, Command *>::iterator it;

    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}
