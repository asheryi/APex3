

#ifndef EX3_CLIENTERRORCOMMAND_H
#define EX3_CLIENTERRORCOMMAND_H


#include "Command.h"

class ClientErrorCommand : public Command {
public:
    ClientErrorCommand(Display *display);

    bool execute(string command, int sid);
};


#endif //EX3_CLIENTERRORCOMMAND_H
