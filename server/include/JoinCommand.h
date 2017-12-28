#ifndef JoinCommand_H
#define JoinCommand_H
#include "Command.h"
#include "ThreadsManager.h"
#include "GamesHandler.h"

class JoinCommand: public Command {
public:
    JoinCommand(ThreadsManager *threadsManager,GamesHandler* gamesHandler_);
    virtual void execute(vector<string> args);
   virtual ~JoinCommand();
};
#endif
