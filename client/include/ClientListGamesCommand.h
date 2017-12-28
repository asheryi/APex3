#ifndef EX3_LISTGAMESCOMMAND_H
#define EX3_LISTGAMESCOMMAND_H


#include "Command.h"
#include "RemoteInputController.h"
#include "RemoteOutputController.h"

class ClientListGamesCommand : public Command {
public:
    ClientListGamesCommand(int socket_, Display *display);

    virtual void execute(string command);

    virtual ~ClientListGamesCommand();


};


#endif //EX3_LISTGAMESCOMMAND_H
