#ifndef EX3_LISTGAMESCOMMAND_H
#define EX3_LISTGAMESCOMMAND_H


#include "Command.h"
#include "GamesHandler.h"

class ListGamesCommand : public Command{
private:
    const GamesHandler &gamesHandler;


public:
    ListGamesCommand(const GamesHandler &gamesHandler);

    virtual void execute(vector<string> args);
    virtual ~ListGamesCommand();


};


#endif //EX3_LISTGAMESCOMMAND_H
