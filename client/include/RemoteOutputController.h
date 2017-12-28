

#ifndef EX3_REMOTEOUTPUTCONTROLLER_H
#define EX3_REMOTEOUTPUTCONTROLLER_H


#include "PlayerController.h"

class RemoteOutputController : public PlayerController {
    PlayerController *pc;
    int clientSocket;
public:
    /**
   * RemoteOutputController constructor.
   * @param pc -PlayerController, client's PlayerController.
   * @param clientSocket -int, client's socket.
   */
    RemoteOutputController(PlayerController *pc, int clientSocket);

    virtual Cell *getLandingPoint() const;

    virtual int getMenuSelection() const;

    virtual ~RemoteOutputController();
    /**
   * update the server about the selected move.
   * @param cell -Cell, client's selected move.
   */
    virtual void update(const Cell &cell);

};


#endif //EX3_REMOTEOUTPUTCONTROLLER_H
