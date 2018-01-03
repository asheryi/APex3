#ifndef StartCommand_H
#define StartCommand_H

#include "Command.h"
#include "Counter.h"
#include "Game.h"

class ClientStartCommand : public Command {
public:
    /**
     * Start command needs the game , the display , and the counters for the players for the excecution.
     * @param game_
     * @param display
     * @param whitesCounter
     * @param blacksCounter
     */
    ClientStartCommand(Game *game_, Display *display, Counter *whitesCounter, Counter *blacksCounter);

    virtual ~ClientStartCommand();

    bool execute(string command, int sid);


private:
    Game *game;
    Counter *whites;
    Counter *blacks;

};

#endif
