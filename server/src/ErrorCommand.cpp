#include "../include/ErrorCommand.h"

void ErrorCommand::execute(vector<string> args, int sid) {
    cout << "invalid command was entered , connection with this client is closed (sid = " << sid << ")" << endl;
    close(sid);
}

ErrorCommand::ErrorCommand(GamesHandler *gamesHandler) : Command(gamesHandler) {
}

ErrorCommand::~ErrorCommand() {
}
