#include "../include/StartCommand.h"
#include "../include/ClientHandler.h"

void StartCommand::execute(vector<string> args) {
    int sid = atoi(args[0].c_str());
    cout<<"Wellcom to Start Command"<<endl;
    cout<<"Socket is: "<<sid<<endl;
    //string gameName=args.at(1);

}
StartCommand::StartCommand(GamesHandler* clientHandler_):Command(clientHandler_){

}
StartCommand::~StartCommand() {

}
