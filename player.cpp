// player.cpp
#include "player.h"

Player::Player() {
    
}

std::string Player::getName()
{
    return name_;
}

int Player::getFullness()
{
    if(fullness_ > 50) {
        return 50;
    }
    return fullness_;
}

void Player::setName(const std::string& name)
{
    name_ = name;
}

void Player::setFullness(int fullness)
{
    fullness_ = fullness;
}

void Player::addFullness(int value)
{
    if(getFullness() == 0 || getFullness() == 50) {
        fullness_ = fullness_;
    }
    fullness_ += value;
}
void Player::decreaseFullness(int amount) {
    fullness_ -= amount;
    if (fullness_ < 0) {
        fullness_ = 0;
    }
}