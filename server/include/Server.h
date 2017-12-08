//
// Created by yishay on 12/4/17.
//

#ifndef EX3_SERVER_H
#define EX3_SERVER_H

#include "../include/Cell.h"

#define MAX_CONNECTED_CLIENTS 2


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
};


#endif //EX3_SERVER_H
