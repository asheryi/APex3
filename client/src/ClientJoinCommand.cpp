#include "../include/ClientJoinCommand.h"

bool ClientJoinCommand::execute(string command, int sid) {
    const char *com = command.c_str();
    int n = write(sid, com, command.length() + 1);
    if (n == 0) {
        close(sid);
        throw "server disconnected before join command";
    } else if (n == -1) {
        close(sid);
        throw "problem writing to server in join command";
    }
    int respond = 0;
    n = read(sid, &respond, sizeof(int));

    if (n == 0) {
        close(sid);
        throw "server disconnected in join command before reading respond";
    } else if (n == -1) {
        close(sid);
        throw "problem reading from server in join command";
    }

    if (respond == -1) {
        clientDisplay->showMessage("you can not join to the game");
    } else if (respond == 1) {
        clientDisplay->showMessage("you joined to the game");
        game->prepareGame(1, whites, blacks);
        return false;
    } else {
        clientDisplay->showMessage("ERROR");
    }
    return true;
}

ClientJoinCommand::~ClientJoinCommand() {

}

ClientJoinCommand::ClientJoinCommand(Game *game_, Display *display,
                                     Counter *whitesCounter, Counter *blacksCounter) : Command(display),
                                                                                       game(game_),
                                                                                       whites(whitesCounter),
                                                                                       blacks(blacksCounter) {

}

