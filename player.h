// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
private:
    std::string name_;
    int fullness_ = 50;

public:
    Player();

    // getters
    std::string getName();
    int getFullness();

    // setters
    void setName(const std::string& name);
    void setFullness(int fullness);

    // other
    void addFullness(int value);
    void decreaseFullness(int amount);
};

#endif