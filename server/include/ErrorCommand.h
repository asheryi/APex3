#ifndef EX3_ERRORCOMMAND_H
#define EX3_ERRORCOMMAND_H
#include "Command.h"

class ErrorCommand : public Command {
public:
    virtual void execute(vector<string> args);
    virtual ~ErrorCommand();
};


#endif //EX3_ERRORCOMMAND_H
