#ifndef EX1_CONSOLECONTROLLER_H
#define EX1_CONSOLECONTROLLER_H


#include "PlayerController.h"
class ConsoleController: public PlayerController {
public:
    Cell* getLandingPoint()const;

    char getMenuSelection() const;
};


#endif //EX1_CONSOLECONTROLLER_H
