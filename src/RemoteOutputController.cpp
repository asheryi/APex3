

#include <zconf.h>
#include "../include/RemoteOutputController.h"


RemoteOutputController::RemoteOutputController(PlayerController *pc, int clientSocket) : pc(pc),
                                                                                         clientSocket(clientSocket) {}


void RemoteOutputController::update(Cell cell) {
    // Write the move to the server
    int n = write(clientSocket, &cell, sizeof(cell));
    if (n == -1) {
        //TODO same to do as before
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


