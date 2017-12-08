#include "../include/Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

using namespace std;

Server::Server(int port) : port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {
    initializeServer();

    while (true) {
        initializeClients();

        gameFlow();

        // Close communication with the clients
        close(clientSockets[0]);
        close(clientSockets[1]);
        cout << "Game Over ! ready for the next couple of players ." << endl;
    }
}

void Server::gameFlow() {
    Cell cell;
    Cell gameOver(-2, -2);
    Cell passTurn(-1, -1);
    do {
        cell = readFromClient();
        currPlayer = 1 - currPlayer;
        if (cell != passTurn) {
            writeToClient(cell);
        }
    } while (cell != gameOver);
}

void Server::initializeServer() {
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
}

void Server::initializeClients() {

    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = 0;

    cout << "Waiting for players connections..." << endl;
    // Accept a new client connection
    int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
    if (clientSocket == -1)
        throw "Error on accept";
    cout << "First player connected" << endl;
    clientSockets[0] = clientSocket;


    clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
    if (clientSocket == -1)
        throw "Error on accept";
    cout << "Second player connected" << endl;
    clientSockets[1] = clientSocket;
    currPlayer = 0;
    writeToClient(Cell(1, 0));
    currPlayer = 1;
    writeToClient(Cell(2, 0));
    currPlayer = 0;
}

void Server::writeToClient(Cell cell) {
    int n = write(clientSockets[currPlayer], &cell, sizeof(cell));
    if (n == -1) {
        //TODO:How to solve it, think about it...
        throw "Problem";
    }
}

Cell Server::readFromClient() {
    Cell cell;
    int n = read(clientSockets[currPlayer], &cell, sizeof(cell));

    if (n == -1) {
        //TODO:How to solve it, think about it...
        throw "Problem";
    }
    return cell;
}

void Server::stop() {
    cout << "Game over !" <<
         close(serverSocket);
}