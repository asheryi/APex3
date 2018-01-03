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
   * Command constructor.
   * @param gamesHandler_ -GamesHandler, in change of the gaems.
   */
    Command(GamesHandler *gamesHandler_) {
        gamesHandler = gamesHandler_;
    }

public:
    /**
   * execute, operates the command.
   * @param args -vector<string>, arguments required for the command.
   * @param sid -int, the socket of the client who sent the command.
   */
    virtual void execute(vector<string> args, int sid) = 0;
   /*
    * Command deconstructor.
    */
    virtual ~Command() {};

};

#endif

