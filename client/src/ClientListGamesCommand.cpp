#include "../include/ClientListGamesCommand.h"

ClientListGamesCommand::ClientListGamesCommand(int socket_, Display *display) : Command(display, socket_) {

}

void ClientListGamesCommand::execute(vector<string> args) {
    //sending command to server

    //cout<<"Welcome to ClientGetList Exexute"<<endl;
    const char *com = "list_games";
    int size = 11;
    int n = write(sid, com, sizeof(char) * size);
    if (n == -1) {
        throw "Error writing to socket";
    }

    //receiving respond from server
    unsigned long sizeRespond;
    read(sid, &sizeRespond, sizeof(unsigned long));

    string str = "Number of games is: ";

    clientDisplay->showMessage(str);
    //cout << sizeRespond << endl;

    char res[50];

    for (int i = 0; i < sizeRespond; i++) {
        int n = read(sid, res, 50);
        clientDisplay->showMessage(string(res));
    }
}

ClientListGamesCommand::~ClientListGamesCommand() {

}


