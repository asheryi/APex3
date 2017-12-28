#ifndef StartCommand_H
#define StartCommand_H
#include "Command.h"

class StartCommand: public Command {
public:
    virtual void execute(vector<string> args);
    virtual ~StartCommand();
};
#endif
