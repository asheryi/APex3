#include "../include/GamesHandler.h"

bool GamesHandler::exists(string name) {
    bool result=true;
    pthread_mutex_lock(&maps_mutex);
    if ( holdOnGames.find(name) == holdOnGames.end() ) {
        if (activeGames.find(name) == activeGames.end() ) {
            result = false;
        }
    }
    pthread_mutex_unlock(&maps_mutex);
    return result;
}

bool GamesHandler::addGame(string name,GameManager* gm) {
    if(exists(name)){
        return false;
    }else{
        holdOnGames[name]=gm;
        return true;
    }
}
void GamesHandler::activateGame(string name,int socket) {
    pthread_mutex_lock(&maps_mutex);
    activeGames[name]=holdOnGames[name];
    holdOnGames.erase(name);
    activeGames[name]->setPlayerSid(1,socket);
    pthread_mutex_unlock(&maps_mutex);
}

string GamesHandler::getHoldOnGames() const {
    string result = "";
    pthread_mutex_lock(&maps_mutex);
    /*for (const pair<const string, GameManager *> & gameName:holdOnGames){
        result += gameName.first;
        result += "\n";
    }*/
    map<string, GameManager*>::iterator it;
    for (it = holdOnGames.begin(); it != holdOnGames.end(); it++ )
    {
        result += it->first;
        result += "\n";
    }
    pthread_mutex_unlock(&maps_mutex);

    return result;
}

GamesHandler::GamesHandler() : holdOnGames(),activeGames(){
}

unsigned long GamesHandler::howManyHoldOnGames() const {
    return holdOnGames.size();
}

