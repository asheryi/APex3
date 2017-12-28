#include "../include/ClientCommandsManager.h"


ClientCommandsManager::ClientCommandsManager(int socket_) :socket(socket_), commandsMap(){
    commandsMap["start"] = new ClientStartCommand();
    commandsMap["list_games"] = new ClientListGamesCommand(socket_);
    commandsMap["join"] = new JoinCommand();
    cout<<"Socket Manager:"<<socket<<endl;

}
void ClientCommandsManager::executeCommand(string command) {
    if ( commandsMap.find(command) == commandsMap.end() ) { // not found

        cout<<"Command Error"<<endl;
    } else { // found
        vector<string>*args=new vector<string>();
        commandsMap[command]->execute(*args);
    }
}
ClientCommandsManager::~ClientCommandsManager() {
    map<string, Command *>::iterator it;

    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }


}
