#ifndef JoinCommand_H
#define JoinCommand_H
#include "Command.h"
#include "ThreadsManager.h"

class JoinCommand: public Command {
public:
    JoinCommand(ThreadsManager *threadsManager);

    virtual void execute(vector<string> args);
   virtual ~JoinCommand();

};
#endif
