

#include <zconf.h>
#include <cstdlib>
#include "../include/RemoteInputController.h"

RemoteInputController::RemoteInputController(int clientSocket) : clientSocket(clientSocket) {}

Cell *RemoteInputController::getLandingPoint() const {
    // Read the move from the server
    Cell move;
    int n = read(clientSocket, &move, sizeof(move));
    //char string[8];
    //int n = read(clientSocket, string, 8);
    if (n == -1) {

        //TODO who is gonna catch it ? , how to display , where the display comes from ? args to main maybe ...


        throw "Error reading result from socket";
        exit(-1);
    }
    return new Cell(move);
}

int RemoteInputController::getMenuSelection() const {
    return 0;
}
