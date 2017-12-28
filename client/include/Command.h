#ifndef Command_h
#define Command_h
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
class Command {
public:
    virtual void execute(vector<string> args) = 0;
    virtual ~Command() {}
};

#endif

