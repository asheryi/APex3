#include "../include/ClientStartCommand.h"

void ClientStartCommand::execute(string command) {
    const char *com =command.c_str();
    int n = write(sid, com, sizeof(char) * 60);
    int respond=0;
    read(sid, &respond, sizeof(int));
    if(respond==-1){
        clientDisplay->showMessage("this game is taken");
    }else{
        clientDisplay->showMessage("this game is free");
    }
}
ClientStartCommand::~ClientStartCommand() {

}

ClientStartCommand::ClientStartCommand(Display *display, int socket) : Command(display, socket) {}
