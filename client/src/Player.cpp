#include "../include/Player.h"

using namespace std;


void Player::updateScore(int newScore) {
    discsCounter->setValue(newScore);
}

int Player::getScore() const {
    return discsCounter->getValue();
}


Player::~Player() {
    delete controller;
    delete discsCounter;
}

Color Player::getRivalColor() {
    return color == black ? white : black;
}

Player::Player(PlayerController *controller, Counter *discsCounter, Color color) : controller(controller),
                                                                                   color(color),
                                                                                   discsCounter(discsCounter) {

}

void Player::modifyPlayerColor(Color color, Counter *discsCounter) {
    this->color = color;
    this->discsCounter = discsCounter;
}


