

#include <zconf.h>
#include "../include/RemoteInputController.h"

RemoteInputController::RemoteInputController(int clientSocket) : clientSocket(clientSocket) {}

Cell *RemoteInputController::getLandingPoint() const {
    // Read the move from the server
    Cell move;
    int n = read(clientSocket, &move, sizeof(move));
    cout << "\n\n" << move << endl;
    if (n == -1) {
        throw "Error reading result from socket, done";
    } else if (n == 0) {
        throw "Server disconnected , sorry, play fast next time (:";
    }
    return new Cell(move);
}

int RemoteInputController::getMenuSelection() const {
    return 0;
}

void RemoteInputController::setClientSocket(int clientSocket) {
    this->clientSocket = clientSocket;
}
