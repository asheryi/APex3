

#include <zconf.h>
#include "../include/RemoteInputController.h"
#include <stdlib.h>
#include <vector>

RemoteInputController::RemoteInputController(int clientSocket) : clientSocket(clientSocket) {}

Cell *RemoteInputController::getLandingPoint() const {
    // Read the move from the server
    Cell move;
    int n = read(clientSocket, &move, sizeof(move));
    if (n == -1) {
        throw "Error reading result from socket";
    }
    return new Cell(move);
}
string RemoteInputController::getRespond() const {
    // Read the move from the server
    string d="";
    unsigned long sizeRespond;
    read(clientSocket, &sizeRespond, sizeof(unsigned long));
    vector<char*> *gameNames=new vector<char*>;
    cout<<sizeRespond<<endl;
    for(int i=0;i<sizeRespond;i++){
        char *res = (char*) calloc(50, sizeof(char));
        int n = read(clientSocket, res, 50);
       // cout<<res<<endl;
        gameNames->push_back(res);
    }
    for(int i=0;i<gameNames->size();i++){
        cout<<gameNames->at(i)<<endl;
    }
   /* while(sizeRespond!=0) {
        cout << sizeRespond << endl;
        sizeRespond = (sizeRespond);
        char *res = (char *) calloc(sizeRespond, sizeof(char));
        int n = read(clientSocket, res, sizeRespond);
        if (n == -1) {
            throw "Error reading result from socket";
        }
        cout << res<< endl;;
        read(clientSocket, &sizeRespond, sizeof(unsigned long));
    }*/
    return d;
}
int RemoteInputController::getMenuSelection() const {
    return 0;
}
