#ifndef EX3_CLIENTHANDLER_H
#define EX3_CLIENTHANDLER_H
#define MAX_COMMAND_SIZE 60

#include "../include/CommandsManager.h"
#include "ThreadsManager.h"

class ClientHandler {
private:

    CommandsManager *commandsManager;
    pthread_mutex_t sids_mutex;
    ThreadsManager *threadsManager;
    vector<int> connectedClientsSid;
public:
    static void *handle(void *clientHandlerStruct);

    string readCommand(int sid);

    string getCommand(string input);

    /*
    void setAliveMutex(pthread_mutex_t* alive_mutex_);
    void setAlive(bool* alive_);
    pthread_mutex_t* getAliveMutex();
    bool* getAlive();
     */

    typedef struct HandleClientStruct {
        int sid;
        ClientHandler *clientHandler;
    } HandleClientStruct;

    void removeClientSid(int sid);

    void addClientSid(int sid);

    ClientHandler(ThreadsManager *threadsManager);

    ~ClientHandler();

    void executeCommand(string command, vector<string> *args, int sid);

    vector<string> *getArgs(string input);
};


#endif //EX3_CLIENTHANDLER_H
