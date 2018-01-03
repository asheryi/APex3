#ifndef Command_h
#define Command_h
#define MAX_GAME_NAME_SIZE 50

#include <vector>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>
#include "Display.h"

using namespace std;

// Command pattern , also for the client .
class Command {
public:
    /**
     *
     * @param command - the command to execute .
     * @param sid - socket id .
     * @return true if after execution
     */
    virtual bool execute(string command, int sid) = 0;

    virtual ~Command() {}

protected:
    Command(Display *display) : clientDisplay() {
        clientDisplay = display;
    }

    Display *clientDisplay;
    int sid;
};

#endif

