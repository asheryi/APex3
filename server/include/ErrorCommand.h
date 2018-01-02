#ifndef EX3_ERRORCOMMAND_H
#define EX3_ERRORCOMMAND_H

#include "../include/Command.h"

class ErrorCommand : public Command {
public:
    ~ErrorCommand();

    ErrorCommand(GamesHandler *clientHandler_);

    void execute(vector<string> args, int sid);
};


#endif //EX3_ERRORCOMMAND_H
