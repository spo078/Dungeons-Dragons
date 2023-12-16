// party.h
#ifndef PARTY_H
#define PARTY_H

#include <vector>
#include "player.h"
#include "inventory.h"
using namespace std;

class Party
{
private:
    vector<Player> members_;
    // Inventory& inventory_;

public:
   // Party(Inventory& inventory);
    // Add a player to the party
    Party();
    void addMember(const Player& player);

    // Get a reference to a party member
    Player& getMember(int index);

    // Get the number of party members
    int getPartySize() const;

    // Check if the party is full
    bool isFull() const;

    // Remove a member from the party by index
    void removeMember(int index);

    void decreaseFullness(int index, int amount);

    // Your existing declarations...

   // bool hasWeapon() const;
    //void surrender();
    //int getPartySize() const;
    //void removePartyMember(int index);
    //bool hasArmor(int index) const;
    void removeRandomPlayerArmor();
    void removeRandomPlayer();

};

#endif