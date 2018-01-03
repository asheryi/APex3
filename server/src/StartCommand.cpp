#include "../include/StartCommand.h"

void StartCommand::execute(vector<string> args, int sid) {
    string gameName = args[0];
    cout << "The game that player with sid = " << sid << "is starting is: " << gameName << endl;
    int respond = 1;

    // if the gameName is not taken :
    if (!gamesHandler->exists(gameName)) {
        GameManager *gm = new GameManager(sid);
        gamesHandler->addGame(gameName, gm);
    } else { // otherwise .
        respond = -1;
    }
    int n = write(sid, &respond, sizeof(int));
    if (n == -1) {
        cout << "Unable to write to client (sid = " << sid << ")" << endl;
        close(sid);
    } else if (n == 0) {
        cout << "Client with sid = " << sid << ", closed the connection" << endl;
        close(sid);
    }
    if (respond == -1) { // sent -1 , means game was not created
        close(sid);
    }
}

StartCommand::StartCommand(GamesHandler *clientHandler_) : Command(clientHandler_) {

}

StartCommand::~StartCommand() {

}
