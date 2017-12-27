#include "../include/ListGamesCommand.h"

ListGamesCommand::ListGamesCommand(GamesHandler &gamesHandler) : gamesHandler(gamesHandler) {}

void ListGamesCommand::execute(vector<string> args) {
    int sid = atoi(args[0].c_str());
    //string gamesList = gamesHandler.getHoldOnGames();
    unsigned long gamesCount = gamesHandler.howManyHoldOnGames();
    int n = write(sid,&gamesCount,sizeof(unsigned long));
    const char * gamesList = gamesHandler.getHoldOnGames().c_str();
    n = write(sid,gamesList,sizeof(gamesList));
    close(sid);
}
ListGamesCommand::~ListGamesCommand() {

}


