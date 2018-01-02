#include "../include/ClientHandler.h"
#include <sstream>
#include <algorithm>

void *ClientHandler::handle(void *handleClientStruct_) {
    HandleClientStruct *handleClientStruct = (struct HandleClientStruct *) handleClientStruct_;

    ClientHandler *clientHandler = handleClientStruct->clientHandler;
    int sid = handleClientStruct->sid;
    clientHandler->addClientSid(sid);
    string input = clientHandler->readCommand(sid);
    cout << "The command is:"<<input<<endl;
    string command = clientHandler->getCommand(input);
    clientHandler->executeCommand(command, clientHandler->getArgs(input, sid));
    clientHandler->removeClientSid(sid);
}

string ClientHandler::getCommand(string input) {
    return input.substr(0, input.find(" "));
}

vector<string> *ClientHandler::getArgs(string input, int sid) {
    cout << "Received command: " << input << endl;
    // Split the command string to the command name and the arguments
    string str(input);
    istringstream iss(str);
    string command;
    iss >> command;
    vector<string> *args=new vector<string>();
    while (iss) {
        string arg;
        iss >> arg;
        args->push_back(arg);
    }
    cout<<"the command after split is:"<<endl;
    for(int i=0;i<args->size();i++){
        cout<<args->at(i)<<endl;
    }

    return args;


}

string ClientHandler::readCommand(int sid) {
    char command[MAX_COMMAND_SIZE];
    int n = read(sid, &command, sizeof(command));

    if (n <= 0) {
        throw "Problem with read operation";
    }
    return string(command);
}

void ClientHandler::executeCommand(string command, vector<string> *args) {
    commandsManager->executeCommand(command, args);
}


void ClientHandler::addThread(pthread_t thread) {
    threadsManager->addThread(thread);
}

ClientHandler::ClientHandler() : sids_mutex() {
    threadsManager = new ThreadsManager();
    commandsManager = new CommandsManager(threadsManager);
}

void ClientHandler::addClientSid(int sid) {
    pthread_mutex_lock(&sids_mutex);
    connectedClientsSid.push_back(sid);
    pthread_mutex_unlock(&sids_mutex);
}

void ClientHandler::removeClientSid(int sid) {
    pthread_mutex_lock(&sids_mutex);
    connectedClientsSid.erase(remove(connectedClientsSid.begin(), connectedClientsSid.end(), sid),
                              connectedClientsSid.end());

    pthread_mutex_unlock(&sids_mutex);

}


