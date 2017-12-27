#ifndef JoinCommand_H
#define JoinCommand_H
#include "Command.h"

class JoinCommand: public Command {
public:
   virtual void execute(vector<string> args);
   virtual ~JoinCommand();

};
#endif
