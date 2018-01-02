#include "../include/StartCommand.h"

void StartCommand::execute(vector<string> args, int sid) {
    string gameName = args[0];
    cout << "Welcome to Start Command" << endl;
    cout << "The game you want to create is: " << gameName << endl;
    int respond = 1;

    if (!gamesHandler->exists(gameName)) {
        cout << "game was created" << endl;
        GameManager *gm = new GameManager(sid);
        gamesHandler->addGame(gameName, gm);
    } else {
        cout << "game was not created" << endl;
        respond = -1;
    }
    int n = write(sid, &respond, sizeof(int));
    if (n == -1) {
        cout << "Unable to writie to client (sid = " << sid << ")" << endl;
    } else if (n == 0) {
        cout << "Client with sid = " << sid << ", closed the connection" << endl;
    }
    if (respond == -1) { // sent -1 , means game was not created
        close(sid);
    }

}

StartCommand::StartCommand(GamesHandler *clientHandler_) : Command(clientHandler_) {

}

StartCommand::~StartCommand() {

}
