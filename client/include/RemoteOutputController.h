

#ifndef EX3_REMOTEOUTPUTCONTROLLER_H
#define EX3_REMOTEOUTPUTCONTROLLER_H


#include "PlayerController.h"

class RemoteOutputController : public PlayerController {
    PlayerController *pc;
    int clientSocket;
public:
    RemoteOutputController(PlayerController *pc, int clientSocket);

    virtual Cell *getLandingPoint() const;

    virtual int getMenuSelection() const;

    virtual ~RemoteOutputController();

    virtual void update(const Cell &cell);

};


#endif //EX3_REMOTEOUTPUTCONTROLLER_H
