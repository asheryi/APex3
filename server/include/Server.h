
#ifndef EX3_SERVER_H
#define EX3_SERVER_H

#include "../include/Cell.h"
#include "ClientHandler.h"
#include "ThreadsManager.h"
#include <pthread.h>

#define MAX_WAITING 10

class Server {
public:
    /**
   * Server constructor.
   * @param port -int, server's port.
   */
    Server(int port, ClientHandler *clientHandler);

    Server(int port, ClientHandler *clientHandler, ThreadsManager *threadsManager);

    /**
            * start the server operation.
          */
    void start();

    //TODO delete all notes !
    //bool* getAlive();
    //pthread_mutex_t* getAliveMutex();

private:
    typedef struct ServerDetails {
        int serverSocket;
        ClientHandler *clientHandler;
        ThreadsManager *threadsManager;
    } ServerDetails;

    ServerDetails *serverDetails;
    int port;

    void stop();

    /**
    * initializeServer initializes the server to listen to connection requests.
    * @param clientSocket -int, client's socket.
    */
    void initializeServer();


    static void *receiveClients(void *receiveClientsStructArg);

};


#endif //EX3_SERVER_H
