#include <sstream>
#include "../include/ClientListGamesCommand.h"

ClientListGamesCommand::ClientListGamesCommand(Display *display) : Command(display) {

}

void ClientListGamesCommand::execute(string command, int sid) {
    //sending command to server

    //cout<<"Welcome to ClientGetList Exexute"<<endl;
    const char *com = "list_games";
    int size = 11;
    int n = write(sid, com, sizeof(char) * size);
    if (n <= 0) {
        close(sid);
        throw "Error writing to socket";
    }

    //receiving respond from server
    unsigned long sizeRespond;
    read(sid, &sizeRespond, sizeof(unsigned long));
    stringstream gameNumStr;
    gameNumStr << "Number of games is: " << sizeRespond;
    clientDisplay->showMessage(gameNumStr.str());

    char res[MAX_GAME_NAME_SIZE];

    for (int i = 0; i < sizeRespond; i++) {
        for (int i = 0; i < MAX_GAME_NAME_SIZE; i++) {
            res[i]=0;
        }
        int n = read(sid, res, MAX_GAME_NAME_SIZE); //TODO
        gameNumStr<<res;
        clientDisplay->showMessage(gameNumStr.str());

    }

    close(sid);
}

ClientListGamesCommand::~ClientListGamesCommand() {

}


