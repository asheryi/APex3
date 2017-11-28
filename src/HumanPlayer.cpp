#include "../include/HumanPlayer.h"

Cell *HumanPlayer::chooseAndReturnMove(const std::vector<Path *> &availableMovePaths) {
    return controller->getLandingPoint();
}

HumanPlayer::HumanPlayer(PlayerController *controller, Counter *scoreCounter, Color color) : Player(controller,
                                                                                                    scoreCounter,
                                                                                                    color) {
}

int HumanPlayer::getMenuSelection() {
    return controller->getMenuSelection();
}


