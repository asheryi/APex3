#include "../include/ClientStartCommand.h"

void ClientStartCommand::execute(string command) {
    const char *com = command.c_str();
    int n = write(sid, com, command.length());
    int respond = 0;
    read(sid, &respond, sizeof(int));
    if (respond == -1) {
        clientDisplay->showMessage("this game is taken");

    } else {
        clientDisplay->showMessage("Waiting to second player...");
        read(sid, &respond, sizeof(int));
        game->prepareGame(0, whites, blacks);
    }
}

ClientStartCommand::~ClientStartCommand() {

}

ClientStartCommand::ClientStartCommand(Game *game_, Display *display, int socket, Counter *whitesCounter,
                                       Counter *blacksCounter) : Command(display, socket), game(game_),
                                                                 whites(whitesCounter),
                                                                 blacks(blacksCounter) {

}

