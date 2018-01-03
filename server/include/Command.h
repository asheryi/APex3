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
    GamesHandler *gamesHandler;
    /**
   * readCommand, reads command from client.
   * @param sid -int, client's socket.
   * @return  string, client's command.
   */
    Command(GamesHandler *gamesHandler_) {
        gamesHandler = gamesHandler_;
    }

public:
    virtual void execute(vector<string> args, int sid) = 0;

    virtual ~Command() {};

};

#endif

