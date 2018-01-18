#include "../include/Server.h"
#include <cstring>

using namespace std;

Server::Server(int port, ClientHandler *clientHandler, ThreadsManager *threadsManager) : port(port) {
    this->serverDetails = new ServerDetails;
    serverDetails->threadsManager = threadsManager;
    serverDetails->serverSocket = 0;
    serverDetails->clientHandler = clientHandler;
    cout << "Server" << endl;
}

void Server::start() {
    initializeServer();

    pthread_t receiveClientsThread;

    int thread = pthread_create(&receiveClientsThread, NULL, this->receiveClients, this->serverDetails);
    if (thread) {
        cout << "Error: unable to create thread, " << receiveClientsThread << endl;
    }
    serverDetails->threadsManager->addThread(receiveClientsThread);
    string serverCommand;

    do {
        cin >> serverCommand;
    } while (serverCommand != "exit");

    close(this->serverDetails->serverSocket);
    cout << "closed socket" << endl;
    delete serverDetails;
}

void *Server::receiveClients(void *receiveClientsStructArg) {
    ServerDetails *receiveClientsStruct = (ServerDetails *) (receiveClientsStructArg);
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
            break;
        cout << "Connection established with sid = " << sid << endl;
        ClientHandler::taskArgs *clientStruct = new ClientHandler::taskArgs;
        clientStruct->sid = sid;
        clientStruct->clientHandler = clientHandler;
        clientStruct->threadsManager = receiveClientsStruct->threadsManager;

        Task *commandTask = new Task(ClientHandler::handle, clientStruct);
        receiveClientsStruct->threadsManager->addTaskToThreadPool(commandTask);

        /*
        pthread_t handleClientThread;
        int thread = pthread_create(&handleClientThread, NULL, ClientHandler::handle, clientStruct);;

        if (thread) {
            cout << "Error: unable to create thread, " << thread << endl;
        } else {
            receiveClientsStruct->threadsManager->addThread(handleClientThread);
        }*/
    }
}

void Server::initializeServer() {
    // Create a socket point
    serverDetails->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int serverSocket = serverDetails->serverSocket;
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
    close(serverDetails->serverSocket);
}
