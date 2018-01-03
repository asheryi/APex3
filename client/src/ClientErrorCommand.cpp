

#include "../include/ClientErrorCommand.h"

ClientErrorCommand::ClientErrorCommand(Display *display) : Command(display) {}

bool ClientErrorCommand::execute(string command, int sid) {
    clientDisplay->showMessage(command + " isn't a valid command.");
    return true;
}
