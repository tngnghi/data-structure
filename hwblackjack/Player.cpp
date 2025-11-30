#include "Player.h"
#include <iostream>
#include <string>

Player::Player(const std::string& name) : GenericPlayer(name) {}

Player::~Player() {}

bool Player::isHitting() const {
    std::cout << getName() << ", do you want a hit? (Y/N): ";
    char response;
    std::cin >> response;
    return (response == 'y' || response == 'Y');
}

void Player::win() const {
    std::cout << getName() << " wins!" << std::endl;
}

void Player::lose() const {
    std::cout << getName() << " loses!" << std::endl;
}

void Player::push() const {
    std::cout << getName() << " pushes!" << std::endl;
}