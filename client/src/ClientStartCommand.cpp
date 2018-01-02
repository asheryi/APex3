#include "../include/ClientStartCommand.h"

bool ClientStartCommand::execute(string command, int sid) {
    const char *com = command.c_str();
    int n = write(sid, com, command.length() + 1);
    if (n == 0) {
        close(sid);
        throw "server disconnected before start command";
    } else if (n == -1) {
        close(sid);
        throw "problem writing to server in start command";
    }
    int respond = 0;
    read(sid, &respond, sizeof(int));
    if (respond == -1) {
        clientDisplay->showMessage("this game is taken");
        return true;
    } else {
        clientDisplay->showMessage("Waiting to second player...");
        read(sid, &respond, sizeof(int));
        game->prepareGame(0, whites, blacks);
        return false;
    }
}

ClientStartCommand::~ClientStartCommand() {

}

ClientStartCommand::ClientStartCommand(Game *game_, Display *display, Counter *whitesCounter,
                                       Counter *blacksCounter) : Command(display), game(game_),
                                                                 whites(whitesCounter),
                                                                 blacks(blacksCounter) {

}

