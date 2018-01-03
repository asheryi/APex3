#include "../include/ClientHandler.h"
#include <sstream>
#include <algorithm>


ClientHandler::ClientHandler(ThreadsManager *threadsManager) : sids_mutex(), threadsManager(threadsManager) {
    commandsManager = new CommandsManager(threadsManager);
}


void *ClientHandler::handle(void *handleClientStruct_) {
    // getting the args .
    HandleClientStruct *handleClientStruct = (HandleClientStruct *) handleClientStruct_;

    ClientHandler *clientHandler = handleClientStruct->clientHandler;
    int sid = handleClientStruct->sid;
    // add this client sid to the collection of active sid.
    clientHandler->addClientSid(sid);
    // reading the command from the client .
    string input = clientHandler->readCommand(sid);
    // extracting it .
    string command = clientHandler->getCommand(input);
    // executing it
    clientHandler->executeCommand(command, clientHandler->getArgs(input), sid);
    // now sid should close.
    clientHandler->removeClientSid(sid);
    handleClientStruct->threadsManager->removeThread(pthread_self());
    delete handleClientStruct;
}

string ClientHandler::getCommand(string input) {
    return input.substr(0, input.find(" "));
}

vector<string> *ClientHandler::getArgs(string input) {
    cout << "Received command: " << input << endl;
    // Split the command string to the command name and the arguments
    string str(input);
    istringstream iss(str);
    string command;
    iss >> command;
    vector<string> *args = new vector<string>();
    while (iss) {
        string arg;
        iss >> arg;
        args->push_back(arg);
    }
    for (int i = 0; i < args->size(); i++) {
        cout << args->at(i) << endl;
    }
    return args;
}

string ClientHandler::readCommand(int sid) {
    char command[MAX_COMMAND_SIZE];
    int n = read(sid, &command, MAX_COMMAND_SIZE);
    if (n <= 0) {
        return "";
    }

    return string(command);
}

void ClientHandler::executeCommand(string command, vector<string> *args, int sid) {
    commandsManager->executeCommand(command, args, sid);
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

ClientHandler::~ClientHandler() {

    // Closing all of the active sockets.
    int size = connectedClientsSid.size();
    for (int i = 0; i < size; i++) {
        close(connectedClientsSid[i]);
    }
    delete commandsManager;
}

