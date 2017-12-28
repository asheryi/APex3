

#include <zconf.h>
#include "../include/RemoteInputController.h"
#include <stdlib.h>
RemoteInputController::RemoteInputController(int clientSocket) : clientSocket(clientSocket) {}

Cell *RemoteInputController::getLandingPoint() const {
    // Read the move from the server
    Cell move;
    int n = read(clientSocket, &move, sizeof(move));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return new Cell(move);
}
string RemoteInputController::getRespond() const {
    // Read the move from the server
    string d="df";
    unsigned long sizeRespond;
    int n = read(clientSocket, &sizeRespond, sizeof(unsigned long));
    cout<<sizeRespond;
    char* res=(char*) malloc(sizeof(char)*sizeRespond);
     n = read(clientSocket, res, sizeRespond);
    if (n == -1) {
        throw "Error reading result from socket";
    }
    cout<<&res;
    return d;
}
int RemoteInputController::getMenuSelection() const {
    return 0;
}
