#ifndef EX3_LISTGAMESCOMMAND_H
#define EX3_LISTGAMESCOMMAND_H


#include "Command.h"
#include "RemoteInputController.h"
#include "RemoteOutputController.h"

class ListGamesCommand : public Command{
private:
    int socket;

public:
    ListGamesCommand(int socket_);

    virtual void execute(vector<string> args);
    virtual ~ListGamesCommand();


};


#endif //EX3_LISTGAMESCOMMAND_H
