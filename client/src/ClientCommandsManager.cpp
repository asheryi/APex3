#include "../include/ClientCommandsManager.h"


ClientCommandsManager::ClientCommandsManager(int socket_, RemoteOutputController *toServer,
                                             RemoteInputController *fromServer,
                                             Game *game, Display *clientDisplay) : socket(socket_), commandsMap() {

    commandsMap["start"] = new ClientStartCommand(clientDisplay, socket_);
    commandsMap["list_games"] = new ClientListGamesCommand(socket_, clientDisplay);
    commandsMap["join"] = new ClientJoinCommand(clientDisplay, socket_);


    cout << "Socket Manager:" << socket << endl;

}

void ClientCommandsManager::executeCommand(string command) {
    int index=command.find(' ');
    string command_=command.substr(0,index);

    if (commandsMap.find(command_) == commandsMap.end()) { // not found

        //TODO abstraction.

        cout << "Command Error For: " <<command_ <<" "<<command<<endl;

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
