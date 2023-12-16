// party.cpp
#include "party.h"
#include <iostream>
using namespace std;

Party::Party() {};
void Party::addMember(const Player& player)
{
    members_.push_back(player);
}

Player& Party::getMember(int index)
{
    return members_[index];
}

int Party::getPartySize() const
{
    return members_.size();
}

bool Party::isFull() const
{
    return getPartySize() >= 5; // Assuming a maximum party size of 5
}

void Party::removeMember(int index)
{
    members_.erase(members_.begin() + index);
}

void Party::decreaseFullness(int index, int amount) {
    if (index >= 0 && index < members_.size()) {
        members_[index].decreaseFullness(amount);
    }
}
void Party::removeRandomPlayerArmor() {
    srand(time(0));
    int deathChance = rand() % 100;
    if (deathChance < 5 && members_.size() > 1) {
        int playerIndex = rand() % (members_.size() - 1) + 1;
        cout << "Player " << members_[playerIndex].getName() << " has been killed." << endl;
        members_.erase(members_.begin() + playerIndex);
    } else {
        cout << "No players killed." << endl;
    }
}
void Party::removeRandomPlayer() {
    srand(time(0));
    int deathChance = rand() % 100;
    if (deathChance < 10 && members_.size() > 1) {
        int playerIndex = rand() % (members_.size() - 1) + 1;
        cout << "Player " << members_[playerIndex].getName() << " has been killed." << endl;
        members_.erase(members_.begin() + playerIndex);
    } else {
        cout << "No players killed." << endl;
    }
}