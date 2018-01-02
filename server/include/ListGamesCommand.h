#ifndef EX3_LISTGAMESCOMMAND_H
#define EX3_LISTGAMESCOMMAND_H


#include "Command.h"


class ListGamesCommand : public Command {
public:
    ListGamesCommand(GamesHandler *gamesHandler);

    virtual ~ListGamesCommand();


    void execute(vector<string> args, int sid);
};


#endif //EX3_LISTGAMESCOMMAND_H
