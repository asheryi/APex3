#ifndef EX1_PLAYERCONTROLLER_H
#define EX1_PLAYERCONTROLLER_H

#include <iostream>
#include "Cell.h"

using namespace std;

class PlayerController {
public:
    /**
     * @return selected landing point , aka move .
     */
    virtual Cell *getLandingPoint() const =0;

    /**
     * @return Main menu selection .
     */
    virtual int getMenuSelection() const =0;

    virtual void update(const Cell &cell) {};
};


#endif //EX1_PLAYERCONTROLLER_H
