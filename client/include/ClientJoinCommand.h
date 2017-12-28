#ifndef ClientJoinCommand_H
#define ClientJoinCommand_H

#include "Command.h"

class ClientJoinCommand : public Command {
public:
    ClientJoinCommand(Display *display, int socket);

    virtual void execute(vector<string> args);

    virtual ~ClientJoinCommand();

};

#endif
