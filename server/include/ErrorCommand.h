#ifndef EX3_ERRORCOMMAND_H
#define EX3_ERRORCOMMAND_H
#include "../include/Command.h"
class ErrorCommand : public Command {
public:
    virtual void execute(vector<string> args);
    ~ErrorCommand();
    ErrorCommand(GamesHandler* clientHandler_);
};


#endif //EX3_ERRORCOMMAND_H
