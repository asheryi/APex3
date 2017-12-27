#include "../include/Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

using namespace std;

Server::Server(int port,ClientHandler* clientHandler) : port(port),alive(true), clientHandler(clientHandler),serverSocket(0), currPlayer(), clientSockets() {
    cout << "Server" << endl;
    clientHandler->setAlive(getAlive());
    clientHandler->setAliveMutex(getAliveMutex());
}

void Server::start() {
    initializeServer();

    while (alive) {
        pthread_mutex_unlock(&alive_mutex);
        // Define the client socket's structures
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = 0;
        //TODO:testing
        cout << "Waiting for connection request" << endl;
        // Accept a new client connection
        int sid = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        if (sid == -1)
            throw "Error on accept";
        cout << "Connection request accepted\nCreates Command thread" << endl;
        HandleClientStruct* clientStruct;
        clientStruct->setSid(sid);
        clientStruct->setClientHandler(clientHandler);
        pthread_t handleClientThread;
        pthread_create(&handleClientThread, NULL, clientHandler->handle, (void*)clientStruct);
        string serverCommand;
        cin>>serverCommand;

        //initializeClients();

        //gameFlow();

        // Close communication with the clients
        //close(clientSockets[0]);
        //close(clientSockets[1]);
        //cout << "Game Over ! ready for the next couple of players ." << endl;
        pthread_mutex_lock(&alive_mutex);
        if(cin=="exit"){

            alive=false;
        }
    }
}
bool* Server::getAlive(){
    return &alive;
}
pthread_mutex_t* Server::getAliveMutex(){
    return &alive_mutex;
}
void Server::gameFlow() {
    Cell cell;
    Cell gameOver(-2, -2);
    Cell passTurn(-1, -1);
    do {
        try {
            cell = readFromClient();
            currPlayer = 1 - currPlayer;
            if (cell != passTurn) {
                writeToClient(cell);
            }
        } catch (const char *msg) {
            return;
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
    if (n <= 0) {
        throw "Problem with write operation";
    }
}

Cell Server::readFromClient() {
    Cell cell;
    int n = read(clientSockets[currPlayer], &cell, sizeof(cell));

    if (n <= 0) {
        throw "Problem with read operation";
    }
    return cell;
}

void Server::stop() {
    cout << "Game over !" <<
         close(serverSocket);
}

