#include "Player.h"

using namespace std;


void Player::updateScore(int newScore) {
    scoreCounter->setValue(newScore);
}

int Player::getScore() const {
    return scoreCounter->getValue();
}


Player::~Player() {
    delete controller;
    delete scoreCounter;
}

Color Player::getRivalColor() {
    return color == black ? white : black;
}

Player::Player(PlayerController *controller, Counter *scoreCounter, Color color) : controller(controller),
                                                                                   color(color),
                                                                                   scoreCounter(scoreCounter) {

}


