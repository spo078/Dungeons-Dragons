#ifndef FIGHT_H
#define FIGHT_H

#include "party.h"
#include "inventory.h"
#include "status.h"
#include "player.h"
#include <string>
#include <vector>

class Fight {
public:
    Fight(Party& party, Inventory& inventory, Status& status, Player& player);

    bool startBattle(const std::string& monsterName, int challengeRating);
    void handleVictory(int challengeRating);
    void handleDefeat();
    vector<pair<string,int>> monsterOption(string file_name);
    string chooseMonster(Status& status_);
    void loseCase(Inventory& inventory_, Party& party_, Player& player_);
    void winCase(Inventory& inventory_, Status& status_);
    void Surrender(Party& party_);
    bool attackMonster(Inventory& inventory_, Party& party_, Status& status_);
    string chooseMonsterForRoom(Status& status_);

private:
    Party& party_;
    Inventory& inventory_;
    Status& status_;
    Player& player_;
    std::vector<std::string> defeatedMonsters_;
};

#endif // FIGHT_H
