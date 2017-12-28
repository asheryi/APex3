#ifndef StartCommand_H
#define StartCommand_H
#include "Command.h"

class ClientStartCommand: public Command {
public:
    ClientStartCommand(Display *display, int socket);

    virtual void execute(vector<string> args);
    virtual ~ClientStartCommand();
};
#endif
