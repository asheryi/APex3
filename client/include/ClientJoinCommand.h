#ifndef ClientJoinCommand_H
#define ClientJoinCommand_H

#include "Command.h"
#include "Game.h"

class ClientJoinCommand : public Command {
public:
    ClientJoinCommand(Game *game_, Display *display, Counter *whitesCounter, Counter *blacksCounter);

    virtual ~ClientJoinCommand();

    bool execute(string command, int sid);

private:
    Game *game;
    Counter *whites;
    Counter *blacks;

};

#endif
