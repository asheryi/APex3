#include "../include/ListGamesCommand.h"

ListGamesCommand::ListGamesCommand(GamesHandler *gamesHandler_) : Command(gamesHandler_) {}

void ListGamesCommand::execute(vector<string> args, int sid) {
    unsigned long gamesCount = gamesHandler->howManyHoldOnGames();
    int n = write(sid, &gamesCount, sizeof(unsigned long));
    vector<string> *gameList = gamesHandler->getHoldOnGames();
    unsigned long gameNameLength;
    for (int i = 0; i < gameList->size(); i++) {
        const char *gamesList = gameList->at(i).c_str();
        n = write(sid, gamesList, sizeof(char) * 50);
    }
    delete gameList; //TODO delete inside strings ???
}

ListGamesCommand::~ListGamesCommand() {

}


