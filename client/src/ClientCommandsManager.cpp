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
    if (commandsMap.find(command) == commandsMap.end()) { // not found

        //TODO abstraction.
        cout << "Command Error" << endl;

    } else { // found
        vector<string> *args = new vector<string>();
        commandsMap[command]->execute(*args);
    }
}

ClientCommandsManager::~ClientCommandsManager() {
    map<string, Command *>::iterator it;

    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }


}
