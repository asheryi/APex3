

#ifndef EX3_REMOTEINPUTCONTROLLER_H
#define EX3_REMOTEINPUTCONTROLLER_H


#include "PlayerController.h"

class RemoteInputController : public PlayerController {
    int clientSocket;
public:
    /**
    * RemoteInputController constructor.
    * @param clientSocket -int, client's socket.
    */
    RemoteInputController(int clientSocket);

    virtual Cell *getLandingPoint() const;
    virtual string getRespond() const;

    virtual int getMenuSelection() const;
};


#endif //EX3_REMOTEINPUTCONTROLLER_H
