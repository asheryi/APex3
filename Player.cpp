#include "Player.h"

using namespace std;


void Player::updateScore(int newScore) {
    score = newScore;
}

int Player::getScore() const {
    return score;
}


Player::~Player() {
    delete controller;
}

Color Player::getRivalColor() {
    return color == black ? white : black;
}

Player::Player(PlayerController *controller, Color color) : controller(controller),
                                                            color(color) {
    score = 0;
}

