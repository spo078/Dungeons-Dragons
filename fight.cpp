#include "fight.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <cmath>

Fight::Fight(Party& party, Inventory& inventory, Status& status, Player& player) : party_(party), inventory_(inventory), status_(status), player_(player) {}

/*bool Fight::startBattle(const std::string& monsterName, int challengeRating) {
    std::cout << monsterName << " AHEAD! THEY LOOK HOSTILE!" << std::endl;

    if (party_.hasWeapon()) {
        // Your code to calculate the battle outcome using the formula
        // ...

        if (battleOutcome > 0) {
            handleVictory(challengeRating);
            defeatedMonsters_.push_back(monsterName);
            return true;
        } else {
            handleDefeat();
            return false;
        }
    } else {
        // No weapons, only option is to surrender
        party_.surrender();
        return false;
    }
}

void Fight::handleVictory(int challengeRating) {
    inventory_.addGold(challengeRating);
    inventory_.addIngredients(challengeRating);
    
    int keyDropChance = rand() % 100;
    if (keyDropChance < 10) {
        inventory_.addKey();
        std::cout << "The monster dropped a key!" << std::endl;
    }

    std::cout << "You have defeated the " << defeatedMonsters_.back() << "!" << std::endl;
}

void Fight::handleDefeat() {
    inventory_.loseGold(inventory_.getGold() / 4);
    inventory_.loseIngredients(30);

    srand(time(0));
    for (int i = 1; i < party_.getPartySize(); i++) {
        int deathChance = (party_.hasArmor(i)) ? 5 : 10;
        int deathRoll = rand() % 100;

        if (deathRoll < deathChance) {
            std::cout << "Party member " << i << " has been slain." << std::endl;
            party_.removePartyMember(i);
        }
    }
}*/
vector<pair<string,int>> Fight::monsterOption(string filename) {
    std::vector<std::pair<std::string, int>> monsters;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string monsterName = line.substr(0, commaPos);
            std::string numberStr = line.substr(commaPos + 1);
            int monsterValue = std::stoi(numberStr);
            monsters.push_back(std::make_pair(monsterName, monsterValue));
        }
    }
    file.close();
    return monsters;
}
string Fight::chooseMonster(Status& status_) {
    string filename;
    int rooms = status_.getRooms();
    switch (rooms)
    {
    case 0:
        filename = "monster_1.txt";
    break;
    case 1:
        filename = "monster_2.txt";
    break;
    case 2:
        filename = "monster_3.txt";
    break;
    case 3:
        filename = "monster_4.txt";
    break;
    case 4:
        filename = "monster_5.txt";
    case 5:
        filename = "sorcerer.txt";
    break;
    default:
        filename = "sorcerer.txt";
    break;
    }
    return filename;
}
void Fight::loseCase(Inventory& inventory_, Party& party_, Player& player_) {
    if(inventory_.gold > 30) {
        inventory_.gold = round(inventory_.gold/4);
    }
    if(inventory_.armor > 1) {
        party_.removeRandomPlayerArmor();
    }
    else{
        srand(time(0));
        int j = rand() % 3 + 1;
        party_.getMember(j).setFullness(0);
        party_.getMember(j).setName("Dead");
        for(int i = 0; i < 5; i++) {
            if(inventory_.weapons[i] > 0) {
                inventory_.weapons[i] -= 1;
                //peqta gna myusin vor minus chdarna;
            }
        }
        
    }
}
void Fight::winCase(Inventory& inventory_, Status& status_) {
    int level;
    switch (status_.getRooms())
    {
    case 0:
        level = 1;
    break;
    case 1:
        level = 2;
    break;
    case 2:
        level = 3;
    break;
    case 3:
        level = 4;
    break;
    case 4:
        level = 5;
    break;
    default:
        return;
    break;
    }
    inventory_.gold += 10*level;
    inventory_.ingredients += 5*level;
    srand(time(0));
    int randomChance = rand() % 100;
    if (randomChance < 10) {
        status_.updKeys();
    }
}
void Fight::Surrender(Party& party_) {
    cout << "You need to be braver next time!!!" << endl;
    srand(time(0));
    int j = rand() % 3 + 1;
    party_.getMember(j).setFullness(0);
    party_.getMember(j).setName("Dead");
    int random = rand() % 5;
    for(int i = 0; i < 5; i++) {
        if(inventory_.weapons[i] > 0) {
            inventory_.weapons[i] -= 1;
            //peqta gna myusin vor minus chdarna;
        }
    }
    for (int i = 0; i < 3; i++) {
         int dropChance = rand() % 100;
         if (dropChance < 20) {
            party_.decreaseFullness(i, 1);
        }
    }
}
bool Fight::attackMonster(Inventory& inventory_, Party& party_, Status& status_) {
    srand(time(0));
    double d = 0;
    double r1 = rand() % 6 + 1;
    double r2 = rand() % 6 + 1;
    double rapier = inventory_.weapons[2];
    double axe = inventory_.weapons[3] * 2;
    double sword = inventory_.weapons[4] * 3;
    double w = 5 * inventory_.getTotalWeapons() + rapier + axe + sword;
    if(inventory_.weapons[2] > 1 && inventory_.weapons[3] > 1 && inventory_.weapons[4] > 1 && inventory_.weapons[1] > 1 && inventory_.weapons[0] > 1) {
        d = 4;
    }
    int a = inventory_.getArmor();
    int c = 0;
    if(inventory_.getTotalWeapons() > 4) {
        d = 4;
    }
    switch (status_.getRooms())
    {
    case 0:
        c = 1;
    break;
    case 1:
        c = 2;
    break;
    case 2:
        c = 3;
    break;
    case 3:
        c = 4;
    break;
    case 4:
        c = 5;
    break;
    
    default:
        c = 0;
    break;
    }
    double eq_1 = r1 * w + d;
    double eq_2 = r2 * c/a;
    double result = eq_1 - eq_2;
    if(result > 0) {
        cout << "You won thr battle warrior!!! check your supplies" << endl;
        return true;
    }
    else{
        cout << "You lose the battle but you fought like a true warrior!!! RIP our friend" << endl;
        return false;
    }

}
string Fight::chooseMonsterForRoom(Status& status_) {
    string filename;
    int rooms = status_.getRooms();
    switch (rooms)
    {
    case 0:
        filename = "monster_2.txt";
    break;
    case 1:
        filename = "monster_3.txt";
    break;
    case 2:
        filename = "monster_4.txt";
    break;
    case 3:
        filename = "monster_5.txt";
    break;
    case 4:
        filename = "sorcerer.txt";
    default:
        filename = "sorcerer.txt";
    break;
    }
    return filename;
}

