#ifndef EX3_ERRORCOMMAND_H
#define EX3_ERRORCOMMAND_H

#include "../include/Command.h"

// used to display invalid command.
class ErrorCommand : public Command {
public:
    ~ErrorCommand();

    ErrorCommand(GamesHandler *gameHandler_);

    void execute(vector<string> args, int sid);
};


#endif //EX3_ERRORCOMMAND_H
