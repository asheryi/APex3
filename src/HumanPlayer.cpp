#include "../include/HumanPlayer.h"

Cell *HumanPlayer::chooseAndReturnMove(const std::vector<Path *> &availableMovePaths) {
    return controller->getLandingPoint();
}

HumanPlayer::HumanPlayer(PlayerController *controller, Counter *discsCounter, Color color) : Player(controller,
                                                                                                    discsCounter,
                                                                                                    color) {
}

int HumanPlayer::getMenuSelection() {
    return controller->getMenuSelection();
}


