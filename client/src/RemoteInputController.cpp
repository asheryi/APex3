

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
    string d="";
    unsigned long sizeRespond;
    read(clientSocket, &sizeRespond, sizeof(unsigned long));
    cout<<sizeRespond<<endl;
    sizeRespond=(sizeRespond*50);
    char* res=(char*)calloc(sizeRespond,sizeof(char));
     int n = read(clientSocket, res, sizeRespond);
    if (n == -1) {
        throw "Error reading result from socket";
    }
    cout<<res;
    return d;
}
int RemoteInputController::getMenuSelection() const {
    return 0;
}
