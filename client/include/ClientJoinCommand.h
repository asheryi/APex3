#ifndef ClientJoinCommand_H
#define ClientJoinCommand_H

#include "Command.h"
#include "Game.h"

class ClientJoinCommand : public Command {
public:
    ClientJoinCommand(Game *game_, Display *display, int socket);

    virtual void execute(string command);

    virtual ~ClientJoinCommand();

private:
    Game *game;
};

#endif
