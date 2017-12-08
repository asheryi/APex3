
#ifndef EX3_SERVER_H
#define EX3_SERVER_H

#include "../include/Cell.h"

#define MAX_CONNECTED_CLIENTS 10


class Server {
public:
    Server(int port);

    void start();

private:
    int port;
    int serverSocket; // the socket's file descriptor

    int currPlayer;
    int clientSockets[MAX_CONNECTED_CLIENTS];

    void stop();

    void initializeClients();

    void gameFlow();

    Cell readFromClient();

    void writeToClient(Cell cell);

    void initializeServer();
};


#endif //EX3_SERVER_H
