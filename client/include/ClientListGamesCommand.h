#ifndef EX3_LISTGAMESCOMMAND_H
#define EX3_LISTGAMESCOMMAND_H


#include "Command.h"
#include "RemoteInputController.h"
#include "RemoteOutputController.h"

class ClientListGamesCommand : public Command {
public:

    ClientListGamesCommand(Display *display);

    virtual ~ClientListGamesCommand();


    void execute(string command, int sid);
};


#endif //EX3_LISTGAMESCOMMAND_H
