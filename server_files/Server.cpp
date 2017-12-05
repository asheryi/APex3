//
// Created by yishay on 12/4/17.
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

using namespace std;

Server::Server(int port) : port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {
    initializeClients();

    gameFlow();

    // Close communication with the client
    close(clientSockets[0]);
    close(clientSockets[1]);

    stop();
}

void Server::gameFlow() {
    Cell cell;
    Cell gameOver(-2, -2);
    Cell passTurn(-1, -1);
    do {
        cell = readFromClient();
        if (cell != passTurn) {
            writeToClient(cell);
        }
        currPlayer = 1 - currPlayer;
    } while (cell != gameOver);
}

void Server::initializeClients() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress,
          sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr
    *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // Start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENTS);
    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    cout << "Waiting for client connections..." << endl;
    // Accept a new client connection
    int clientSocket = accept(serverSocket, (struct
            sockaddr *) &clientAddress, &clientAddressLen);
    if (clientSocket == -1)
        throw "Error on accept";
    cout << "First Client connected" << endl;
    clientSockets[0] = clientSocket;


    clientSocket = accept(serverSocket, (struct
            sockaddr *) &clientAddress, &clientAddressLen);
    if (clientSocket == -1)
        throw "Error on accept";
    cout << "Second Client connected" << endl;
    clientSockets[1] = clientSocket;
    currPlayer = 0;
    writeToClient(Cell(1, 0));
    currPlayer = 1;
    writeToClient(Cell(2, 0));
    currPlayer = 0;
    writeToClient(Cell (0,0));
}

void Server::writeToClient(Cell cell) {
    int n = write(clientSockets[currPlayer], &cell, sizeof(cell));
    //char string[8] = "454";
    //int n = write(clientSockets[currPlayer], string, 8);
    if (n == -1) {
        //TODO:How to solve it, think about it...
        throw "Problem";
    }
}

Cell Server::readFromClient() {
    Cell cell;
    int n = read(clientSockets[currPlayer], &cell, sizeof(cell));
    cout << "FROM CLIENT" << cell << endl;

    if (n == -1) {
        //TODO:How to solve it, think about it...
        throw "Problem";
    }
    return cell;
}

void Server::stop() {
    close(serverSocket);
}