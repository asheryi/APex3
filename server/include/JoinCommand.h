#ifndef JoinCommand_H
#define JoinCommand_H

#include "Command.h"
#include "ThreadsManager.h"
#include "GamesHandler.h"

class JoinCommand : public Command {
private:
    ThreadsManager *threadsManager;

public:
    JoinCommand(ThreadsManager *threadsManager_, GamesHandler *gamesHandler_);

    virtual void execute(vector<string> args);

    virtual ~JoinCommand();
};

#endif
