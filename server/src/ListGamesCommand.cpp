#include "../include/ListGamesCommand.h"

ListGamesCommand::ListGamesCommand(GamesHandler *gamesHandler_) : Command(gamesHandler_) {}

void ListGamesCommand::execute(vector<string> args, int sid) {
    unsigned long gamesCount = gamesHandler->howManyHoldOnGames();
    int n = write(sid, &gamesCount, sizeof(unsigned long));
    string gameList_ = gamesHandler->getHoldOnGames();
    cout << "The Current Games Are: " << gameList_;
    const char *gamesList = gameList_.c_str();
    if (gamesCount > 0) {
        n = write(sid, gamesList, gameList_.length() + 1);
    }
    close(sid);
}

ListGamesCommand::~ListGamesCommand() {

}


