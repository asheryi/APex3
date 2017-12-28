#include "../include/ClientStartCommand.h"

void ClientStartCommand::execute(vector<string> args) {
    const char *com = "start";
    int size = 11;
    int n = write(sid, com, sizeof(char) * size);
}
ClientStartCommand::~ClientStartCommand() {

}

ClientStartCommand::ClientStartCommand(Display *display, int socket) : Command(display, socket) {}
