#ifndef EX3_CLIENTHANDLER_H
#define EX3_CLIENTHANDLER_H


#include "CommandsManager.h"
#include "ThreadsManager.h"

class ClientHandler {
private:
    ClientCommandsManager* commandsManager;
    pthread_mutex_t sids_mutex;
    ThreadsManager threadsManager;
    vector<int> connectedClientsSid;
public:
    ClientHandler();
    static void* handle(void *clientHandlerStruct);
    string readCommand(int sid);
    string getCommand(string input);
    vector<string>* getArgs(string input,int sid);
    void executeCommand(string command,vector<string>* args);

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

    void addThread(pthread_t thread);

    void removeClientSid(int sid);

    void addClientSid(int sid);
};


#endif //EX3_CLIENTHANDLER_H
