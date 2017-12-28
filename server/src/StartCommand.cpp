#include "../include/StartCommand.h"
#include "../include/ClientHandler.h"

void StartCommand::execute(vector<string> args) {
    int sid = atoi(args[0].c_str());
    string gameName=args[1];
    cout<<"Wellcom to Start Command"<<endl;
    cout<<"The game you want to create is: "<<gameName<<endl;
    int respond=1;
    GameManager *gm=new GameManager(sid);
    if(gamesHandler->addGame(gameName,gm)){
        int n = write(sid,&respond,sizeof(int));
    }else{
        delete gm;
        respond=-1;
        int n = write(sid,&respond,sizeof(int));
    }

}
StartCommand::StartCommand(GamesHandler* clientHandler_):Command(clientHandler_){

}
StartCommand::~StartCommand() {

}
