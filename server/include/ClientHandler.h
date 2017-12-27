#ifndef EX3_CLIENTHANDLER_H
#define EX3_CLIENTHANDLER_H


#include "CommandsManager.h"

class ClientHandler {
private:
    CommandsManager* commandsManager;
    bool* alive;
    pthread_mutex_t* alive_mutex;
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
public:
    static void* handle(void *clientHandlerStruct);
    string readCommand(int sid);
    string getCommand(string input);
    vector<string>* getArgs(string input,int sid);
    void executeCommand(string command,vector<string>* args);
    void setAliveMutex(pthread_mutex_t* alive_mutex_);
    void setAlive(bool* alive_);
    pthread_mutex_t* getAliveMutex();
    bool* getAlive();
};


#endif //EX3_CLIENTHANDLER_H
