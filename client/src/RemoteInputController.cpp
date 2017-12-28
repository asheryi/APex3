

#include <zconf.h>
#include "../include/RemoteInputController.h"

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

    char* res;
    int n = read(clientSocket, res, 20);
    if (n == -1) {
        throw "Error reading result from socket";
    }
    string t=string(res);
    cout<<t;
    return t;
}
int RemoteInputController::getMenuSelection() const {
    return 0;
}
