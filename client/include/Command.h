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
    virtual void execute(string command) = 0;

    virtual ~Command() {}

protected:
    Command(Display *display, int socket) : clientDisplay(), sid(socket) {
        clientDisplay = display;
    }

    Display *clientDisplay;
    int sid;
};

#endif

