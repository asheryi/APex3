
#ifndef EX3_SERVER_H
#define EX3_SERVER_H

#include "../include/Cell.h"
#include "ClientHandler.h"
#include <pthread.h>

#define MAX_CONNECTED_CLIENTS 10

class Server {
public:
    /**
   * Server constructor.
   * @param port -int, server's port.
   */
    Server(int port,ClientHandler* clientHandler);

    /**
   * start the server operation.
   */
    void start();
    bool* getAlive();
    pthread_mutex_t* getAliveMutex();

private:
    ClientHandler* clientHandler;
    bool alive;
    pthread_mutex_t alive_mutex;
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

    typedef struct HandleClientStruct {
    public:
        void setSid(int sid_){
            sid=sid_;
        }
        int getSid(){
            return sid;
        }
        void setClientHandler(ClientHandler* clientHandler_){
            clientHandler=clientHandler_;
        }
        ClientHandler* getClientHandler(){
            return clientHandler;
        }
    private:
        int sid;
        ClientHandler* clientHandler;
    } HandleClientStruct;
};


#endif //EX3_SERVER_H
