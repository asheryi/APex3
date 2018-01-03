
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
   * @param clientHandler .
   * @param threadsManager.
   */
    Server(int port, ClientHandler *clientHandler, ThreadsManager *threadsManager);

    /**
            * start the server operation.
          */
    void start();

    //TODO delete all notes !
    //bool* getAlive();
    //pthread_mutex_t* getAliveMutex();

private:
    // args to threaded func below . also used as wrapper of these 3 fields in server property serverDetails.
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

    /**
     * Main loop accepting clients (threaded) .
     * @param receiveClientsStructArg - args to func
     * @return
     */
    static void *receiveClients(void *receiveClientsStructArg);

};


#endif //EX3_SERVER_H
