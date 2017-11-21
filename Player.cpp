#include "Player.h"

using namespace std;


void Player::setController(PlayerController *controller_) {
    controller = controller_;
}

string Player::getSign() const {
    return sign;
}

void Player::updateScore(int newScore) {
    score = newScore;
}

int Player::getScore() const {
    return score;
}

int Player::getRivalColor() const {
    return (color == -3) ? -2 : -3;
}
//TODO:need to free controller, but ~Player makes
//problems

Player::~Player() {
    delete controller;
}
