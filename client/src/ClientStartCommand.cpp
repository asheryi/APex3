#include "../include/ClientStartCommand.h"

bool ClientStartCommand::execute(string command, int sid) {
    const char *com = command.c_str();
    int n = write(sid, com, command.length() + 1);
    if (n == 0) {
        close(sid);
        throw "server disconnected in start command";
    } else if (n == -1) {
        close(sid);
        throw "problem writing to server in start command";
    }
    int respond = 0;
    n = read(sid, &respond, sizeof(int));
    if (n == 0) {
        close(sid);
        throw "server disconnected in start command";
    } else if (n == -1) {
        close(sid);
        throw "problem writing to server in start command";
    }

    if (respond == -1) {
        clientDisplay->showMessage("this game is taken");
        return true;
    } else {
        clientDisplay->showMessage("Waiting to second player...");
        n = read(sid, &respond, sizeof(int));
        if (n == 0) {
            close(sid);
            throw "server disconnected in start command";
        } else if (n == -1) {
            close(sid);
            throw "problem writing to server in start command";
        }
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

