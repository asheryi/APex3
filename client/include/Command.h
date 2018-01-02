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

class Command {
public:
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

