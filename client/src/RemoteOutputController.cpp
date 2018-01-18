

#include <zconf.h>
#include "../include/RemoteOutputController.h"


RemoteOutputController::RemoteOutputController(PlayerController *pc, int clientSocket) : clientSocket(clientSocket) {
    this->pc = pc;
}


void RemoteOutputController::update(const Cell &cell) {
    // Write the move to the server
    int n = write(clientSocket, &cell, sizeof(cell));
    if (n == -1) {
        throw "Error writing cell to socket";
    } else if (n == 0) {
        throw "Server disconnected , sorry, play fast next time (:";
    }
}

RemoteOutputController::~RemoteOutputController() {
    delete pc;
}

Cell *RemoteOutputController::getLandingPoint() const {
    return pc->getLandingPoint();
}

int RemoteOutputController::getMenuSelection() const {
    return pc->getMenuSelection();
}

void RemoteOutputController::setClientSocket(int clientSocket) {
    this->clientSocket = clientSocket;
}


