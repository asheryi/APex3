#ifndef StartCommand_H
#define StartCommand_H

#include "Command.h"
#include "Counter.h"
#include "Game.h"

class ClientStartCommand : public Command {
public:


    ClientStartCommand(Game *game_, Display *display, Counter *whitesCounter, Counter *blacksCounter);

    virtual ~ClientStartCommand();

    bool execute(string command, int sid);


private:
    Game *game;
    Counter *whites;
    Counter *blacks;

};

#endif
