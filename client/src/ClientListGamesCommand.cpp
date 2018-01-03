#include <sstream>
#include "../include/ClientListGamesCommand.h"

ClientListGamesCommand::ClientListGamesCommand(Display *display) : Command(display) {

}

bool ClientListGamesCommand::execute(string command, int sid) {
    //sending command to server

    //cout<<"Welcome to ClientGetList Exexute"<<endl;
    const char *com = "list_games";
    int size = 11;
    int n = write(sid, com, sizeof(char) * size);
    if (n == 0) {
        close(sid);
        throw "server disconnected before list_games write";
    } else if (n == -1) {
        close(sid);
        throw "problem writing to server in list_games command";
    }

    //receiving respond from server
    unsigned long sizeRespond;
    n = read(sid, &sizeRespond, sizeof(unsigned long));
    if (n == 0) {
        close(sid);
        throw "server disconnected while list_games read";
    } else if (n == -1) {
        close(sid);
        throw "problem reading from server in list_games command";
    }

    stringstream gameNumStr;
    gameNumStr << "Number of games is: " << sizeRespond;
    clientDisplay->showMessage(gameNumStr.str());

    char *res = new char[(sizeRespond * (MAX_GAME_NAME_SIZE + 1)) + 1];
    n = read(sid, res, MAX_GAME_NAME_SIZE);
    if (n == 0) {
        close(sid);
        throw "server disconnected while list_games read";
    } else if (n == -1) {
        close(sid);
        throw "problem reading from server in list_games command";
    }
    clientDisplay->showMessage(string(res));
    delete[] res;
    close(sid);
    return true;
}

ClientListGamesCommand::~ClientListGamesCommand() {

}


