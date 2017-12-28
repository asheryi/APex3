#include "../include/ClientHandler.h"
#include <sstream>
#include <cstdio>

void *ClientHandler::handle(void *handleClientStruct_) {
    HandleClientStruct *handleClientStruct = (struct HandleClientStruct *) handleClientStruct_;

    ClientHandler *clientHandler = handleClientStruct->clientHandler;
    int sid = handleClientStruct->sid;
    clientHandler->addClientSid(sid);
    string input = clientHandler->readCommand(sid);
    cout << input;
    string command = clientHandler->getCommand(input);
    clientHandler->executeCommand(command, clientHandler->getArgs(input, sid));
    close(sid);
    clientHandler->removeClientSid(sid);
}

string ClientHandler::getCommand(string input) {
    return input.substr(0, input.find(" "));
}

vector<string> *ClientHandler::getArgs(string input, int sid) {
    vector<string> *vectorArgs = new vector<string>();
    stringstream stringStream_;
    stringStream_ << sid;
    vectorArgs->push_back(stringStream_.str());

    int start = input.find(" ") + 1;
    string args_ = input.substr(start, input.length() - start);
    int end_ = args_.find(" ");

    while (end_ > -1) {
        vectorArgs->push_back(args_.substr(start, end_));
        start = end_ + 1;
        args_ = args_.substr(start, args_.length() - start);
        end_ = args_.find(" ");
    }
    vectorArgs->push_back(args_);
    return vectorArgs;


}

string ClientHandler::readCommand(int sid) {
    char command[20];
    int n = read(sid, &command, sizeof(command));

    if (n <= 0) {
        throw "Problem with read operation";
    }
    return string(command);
}

void ClientHandler::executeCommand(string command, vector<string> *args) {
    commandsManager->executeCommand(command, args);
}

/*

void ClientHandler::setAlive(bool* alive_){
    alive=alive_;
}
bool* ClientHandler::getAlive(){
    return alive;
}
void ClientHandler::setAliveMutex(pthread_mutex_t* alive_mutex_){
    alive_mutex=alive_mutex_;
}
pthread_mutex_t* ClientHandler::getAliveMutex(){
    return alive_mutex;
}*/

void ClientHandler::addThread(pthread_t thread) {
    threadsManager.addThread(thread);
}

ClientHandler::ClientHandler() : sids_mutex() {
    commandsManager = new CommandsManager(&threadsManager);
}

void ClientHandler::addClientSid(int sid) {
    pthread_mutex_lock(&sids_mutex);
    connectedClientsSid.push_back(sid);
    pthread_mutex_unlock(&sids_mutex);
}

void ClientHandler::removeClientSid(int sid) {
    pthread_mutex_lock(&sids_mutex);
  //  connectedClientsSid.erase(remove(connectedClientsSid.begin(), connectedClientsSid.end(), sid),
                             // connectedClientsSid.end());

    pthread_mutex_unlock(&sids_mutex);

}


