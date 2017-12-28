#include "../include/ListGamesCommand.h"

ListGamesCommand::ListGamesCommand(GamesHandler* gamesHandler_):Command(gamesHandler_){}

void ListGamesCommand::execute(vector<string> args) {
    int sid = atoi(args[0].c_str());
    //string gamesList = gamesHandler.getHoldOnGames();
    unsigned long gamesCount = gamesHandler->howManyHoldOnGames();
    //cout<<"The Games Count Is"<<gamesCount<<endl;
    int n = write(sid,&gamesCount,sizeof(unsigned long));
    vector<string>* gameList=gamesHandler->getHoldOnGames();
    unsigned long gameNameLength;
    for(int i=0;i<gameList->size();i++){
       // gameNameLength = gameList->at(i).length();
       // int n = write(sid,&gameNameLength,sizeof(unsigned long));
        const char * gamesList =  gameList->at(i).c_str();
        n = write(sid,gamesList,sizeof(char)*50);
    }
   // gameNameLength =0;
    //int n = write(sid,&gameNameLength,sizeof(unsigned long));
    close(sid);
    delete gameList; //TODO delete inside strings ???
}

ListGamesCommand::~ListGamesCommand() {

}


