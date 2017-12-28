#ifndef EX3_LISTGAMESCOMMAND_H
#define EX3_LISTGAMESCOMMAND_H


#include "Command.h"
#include "RemoteInputController.h"
#include "RemoteOutputController.h"

class ClientListGamesCommand : public Command{
private:
    int socket;

public:
    ClientListGamesCommand(int socket_);

    virtual void execute(vector<string> args);
    virtual ~ClientListGamesCommand();


};


#endif //EX3_LISTGAMESCOMMAND_H
