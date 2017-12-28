#include "../include/ClientListGamesCommand.h"

ClientListGamesCommand::ClientListGamesCommand(int socket_) {
    socket=socket_;
    cout<<"Socket List:"<<socket<<endl;
}

void ClientListGamesCommand::execute(vector<string> args) {
    //sending command to server
    cout<<"Welcom to ClientGetList Exexute"<<endl;
    const char *com="list_games";
    int size=11;
    int n = write(socket,com,sizeof(char)*size);
    if (n == -1) {
        throw "Error writing cell to socket";
    }

   //receiving respond from server
    unsigned long sizeRespond;
    read(socket, &sizeRespond, sizeof(unsigned long));
    cout<<"Number of game is: "<<sizeRespond<<endl;
    vector<char*> *gameNames=new vector<char*>;
    cout<<sizeRespond<<endl;
    for(int i=0;i<sizeRespond;i++){
        char *res = (char*) calloc(50, sizeof(char));
        int n = read(socket, res, 50);
        // cout<<res<<endl;
        gameNames->push_back(res);
    }
    for(int i=0;i<gameNames->size();i++){
        cout<<gameNames->at(i)<<endl;
    }
}

ClientListGamesCommand::~ClientListGamesCommand() {

}


