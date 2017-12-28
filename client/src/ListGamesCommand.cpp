#include "../include/ClientListGamesCommand.h"

ClientListGamesCommand1::ClientListGamesCommand1(int socket_) {
    socket=socket_;
}

void ClientListGamesCommand1::execute(vector<string> args) {
    unsigned long sizeRespond;
    read(socket, &sizeRespond, sizeof(unsigned long));
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

ClientListGamesCommand1::~ClientListGamesCommand1() {

}


