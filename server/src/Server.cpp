#include "../include/Server.h"
#include <cstring>

using namespace std;

Server::Server(int port, ClientHandler *clientHandler) : port(port), clientHandler(clientHandler),
                                                         serverSocket(0) {
    cout << "Server" << endl;

    //clientHandler->setAlive(getAlive());
    //clientHandler->setAliveMutex(getAliveMutex());

}

void Server::start() {
    initializeServer();

    pthread_t receiveClientsThread;

    ReceiveClientsStruct receiveClientsStruct = {};
    receiveClientsStruct.serverSocket = this->serverSocket;
    receiveClientsStruct.clientHandler = clientHandler;

    int thread = pthread_create(&receiveClientsThread, NULL, this->receiveClients, &receiveClientsStruct);
    if (thread) {
        cout << "Error: unable to create thread, " << thread << endl;
    }
    clientHandler->addThread(receiveClientsThread);

    string serverCommand;

    do {
        cin >> serverCommand;
    } while (serverCommand != "exit");

    close(serverSocket);
    cout << "closed socket" << endl;
}

void *Server::receiveClients(void *receiveClientsStructArg) {
    ReceiveClientsStruct *receiveClientsStruct = (ReceiveClientsStruct *) (receiveClientsStructArg);
    int serverSocket = receiveClientsStruct->serverSocket;
    ClientHandler *clientHandler = receiveClientsStruct->clientHandler;

    while (true) {
        // Define the client socket's structures
        struct sockaddr_in clientAddress = {};
        socklen_t clientAddressLen = 0;
        //TODO:testing
        cout << "Waiting for connection request" << endl;
        // Accept a new client connection
        int sid = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLen);
        if (sid == -1)
            throw "Error on accept";
        cout << "Connection request accepted\nCreates Command thread" << endl;
        ClientHandler::HandleClientStruct clientStruct = {};
        clientStruct.sid = sid;
        clientStruct.clientHandler = clientHandler;
        pthread_t handleClientThread;
        int thread = pthread_create(&handleClientThread, NULL, clientHandler->handle, &clientStruct);;

        if (thread) {
            cout << "Error: unable to create thread, " << thread << endl;
        }

        //TODO remove notes! : everyWHERE
        //initializeClients();

        //gameFlow();

        // Close communication with the clients
        //close(clientSockets[0]);
        //close(clientSockets[1]);
        //cout << "Game Over ! ready for the next couple of players ." << endl;
    }
}

/*
bool *Server::getAlive() {
    return &alive;
}

pthread_mutex_t *Server::getAliveMutex() {
    return &alive_mutex;
}*/

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
    listen(serverSocket, MAX_WAITING);
}

void Server::stop() {
    cout << "Game over !" << endl;
    close(serverSocket);
}
