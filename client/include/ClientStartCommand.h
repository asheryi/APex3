#ifndef StartCommand_H
#define StartCommand_H

#include "Command.h"
#include "Counter.h"
#include "Game.h"

class ClientStartCommand : public Command {
public:

    ClientStartCommand(Game* game_,Display *display, int socket, Counter *whitesCounter, Counter *blacksCounter);

    virtual void execute(string command);

    virtual ~ClientStartCommand();

private:
    Game* game;
    Counter *whites;
    Counter *blacks;
};

#endif
