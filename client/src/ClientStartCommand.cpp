#include "../include/ClientStartCommand.h"

void ClientStartCommand::execute(vector<string> args) {

}
ClientStartCommand::~ClientStartCommand() {

}

ClientStartCommand::ClientStartCommand(Display *display, int socket) : Command(display, socket) {}
