#include "../include/ClientJoinCommand.h"

void ClientJoinCommand::execute(string command) {
    const char *com = command.c_str();
    int n = write(sid, com, command.length());
    int respond = 0;
    read(sid, &respond, sizeof(int));
    if (respond == -1) {
        clientDisplay->showMessage("you can not join to the game");
    } else if (respond == 1) {
        clientDisplay->showMessage("you joined to the game");
        game->prepareGame(1, whites, blacks);
    } else {
        clientDisplay->showMessage("ERROR");
    }
}

ClientJoinCommand::~ClientJoinCommand() {

}

ClientJoinCommand::ClientJoinCommand(Game *game_, Display *display, int socket,
                                     Counter *whitesCounter, Counter *blacksCounter) : Command(display, socket),
                                                                                       game(game_),
                                                                                       whites(whitesCounter),
                                                                                       blacks(blacksCounter) {

}

