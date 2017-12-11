
#ifndef EX3_SERVER_H
#define EX3_SERVER_H

#include "../include/Cell.h"

#define MAX_CONNECTED_CLIENTS 10


class Server {
public:
    /**
   * Server constructor.
   * @param port -int, server's port.
   */
    Server(int port);

    /**
   * start the server operation.
   */
    void start();

private:
    int port;
    int serverSocket; // the socket's file descriptor

    int currPlayer;
    int clientSockets[MAX_CONNECTED_CLIENTS];

    void stop();

    /**
     * initializeClients initializes the clients sockets.
     */
    void initializeClients();

    /**
     * gameFlow manages the clients turns.
     */
    void gameFlow();

    /**
    * readFromClient reads the client message.
    * @return Cell - client's message(could be next move or indicates message to sever e.g:NoMoves).
    */
    Cell readFromClient();

    /**
    * writeToClient writes message to client.
    */
    void writeToClient(Cell cell);

    /**
    * initializeServer initializes the server to listen to connection requests.
    * @param clientSocket -int, client's socket.
    */
    void initializeServer();
};


#endif //EX3_SERVER_H
