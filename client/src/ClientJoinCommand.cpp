#include "../include/ClientJoinCommand.h"

void ClientJoinCommand::execute(string command) {
    const char *com = command.c_str();
    int n = write(sid, com, sizeof(char) * 60);
    int respond = 0;
    read(sid, &respond, sizeof(int));
    if (respond == -1) {
        clientDisplay->showMessage("you can not join to the game");
    } else if (respond == 1) {
        clientDisplay->showMessage("you joined to the game");
        game->prepareGame(1);
    } else {
        clientDisplay->showMessage("ERROR");
    }
}

ClientJoinCommand::~ClientJoinCommand() {

}

ClientJoinCommand::ClientJoinCommand(Game *game_, Display *display, int socket) : Command(display, socket),
                                                                                  game(game_) {

}
