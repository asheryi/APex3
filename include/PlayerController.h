#ifndef EX1_PLAYERCONTROLLER_H
#define EX1_PLAYERCONTROLLER_H
#include <iostream>
#include "Cell.h"

using namespace std;
class PlayerController {
public:
    /*****************************************************************************
    *function name: getLandingPoint
    *operation function:return from keyboard a landing point choose by the player
    *NOTE:
    *****************************************************************************/
    virtual Cell* getLandingPoint()const=0;

    virtual char getMenuSelection() const =0;
};


#endif //EX1_PLAYERCONTROLLER_H
