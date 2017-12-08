

#ifndef EX3_HUMANCONSOLE_H
#define EX3_HUMANCONSOLE_H


#include "Console.h"

class HumanConsole : public Console {
public:
    /**
     * Constructor .
     */
    HumanConsole();

    virtual void showMoveDone(const Cell &cell, Color playerColor) const;

};


#endif //EX3_HUMANCONSOLE_H
