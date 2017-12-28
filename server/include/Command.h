#ifndef Command_h
#define Command_h
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include "../include/GamesHandler.h"
using namespace std;
class Command {
protected:
    GamesHandler* gamesHandler;
    Command(GamesHandler* gamesHandler_){
        gamesHandler=gamesHandler_;
    }
public:
    virtual void execute(vector<string> args) = 0;
    virtual ~Command() {}

};

#endif

