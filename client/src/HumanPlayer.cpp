#include "../../include/HumanPlayer.h"

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

HumanPlayer::HumanPlayer(PlayerController *controller) : Player(controller, NULL,
                                                                empty) {
}

void HumanPlayer::modifyPlayerColor(Color color, Counter *discsCounter) {
    this->color = color;
    this->discsCounter = discsCounter;
}

void HumanPlayer::setController(PlayerController *controller) {
    this->controller = controller;
}


