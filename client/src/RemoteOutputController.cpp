

#include <zconf.h>
#include "../include/RemoteOutputController.h"


RemoteOutputController::RemoteOutputController(PlayerController *pc, int clientSocket) : clientSocket(clientSocket) {
    this->pc = pc;
}


void RemoteOutputController::update(const Cell &cell) {
    // Write the move to the server
    //cout << "OUTPUT CONTROLLER TRYING TO WRITE" << endl;
    int n = write(clientSocket, &cell, sizeof(cell));
    if (n == -1) {
        throw "Error writing cell to socket";
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


