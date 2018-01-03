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
    /**
   * handle.
   * @param clientHandlerStruct -void.
   */
    static void *handle(void *clientHandlerStruct);

    /**
   * readCommand, reads command from client.
   * @param sid -int, client's socket.
   * @return  string, client's command.
   */
    string readCommand(int sid);

    /**
   * getCommand, extracts the command type from the command.
   * @param input -string, command to execute.
   * @return  string, command type.
   */
    string getCommand(string input);
    /*
     * Struct using to pass arguments to thread function.
     */
    typedef struct HandleClientStruct {
        int sid;
        ClientHandler *clientHandler;
        ThreadsManager *threadsManager;
    } HandleClientStruct;

    /**
   * removeClientSid, removes sid from sids vector.
   * @param sid -int, client socket.
   */
    void removeClientSid(int sid);

    /**
   * addClientSid, adds sid to sids vector.
   * @param sid -int, client socket.
   */
    void addClientSid(int sid);

    /**
   * ClientHandler constructor.
   * @param threadsManager -ThreadsManager.
   */
    ClientHandler(ThreadsManager *threadsManager);

    /**
  * ClientHandler deconstructor.
  */
    ~ClientHandler();

    /**
   * executeCommand.
   * @param command -string, command to execute.
   * @param  args-vector<string>*, arguments need for execute the command.
   * @param  sid-int, client socket who sent the command.
   */
    void executeCommand(string command, vector<string> *args, int sid);

    /**
   * executeCommand, extracts the args from the command.
   * @param input -string, command to execute.
   * @return  args-vector<string>*, arguments need for execute the command.
   */
    vector<string> *getArgs(string input);
};


#endif //EX3_CLIENTHANDLER_H
