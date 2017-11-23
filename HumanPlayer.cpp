#include "HumanPlayer.h"

Cell *HumanPlayer::chooseAndReturnMove(const std::vector<Path *> &availableMovePaths) {
    return controller->getLandingPoint();
}

HumanPlayer::HumanPlayer(PlayerController *controller, Color color) : Player(controller,
                                                                             color) {

}


