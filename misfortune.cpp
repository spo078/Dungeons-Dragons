#include "misfortune.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Misfortune::Misfortune(Party& party, Inventory& inventory)
    : party_(party), inventory_(inventory) {
}

void Misfortune::triggerMisfortune() {
    srand(static_cast<unsigned>(time(nullptr)));
    int misfortuneChance = rand() % 100;

    // 40% probability of a misfortune event
    if (misfortuneChance < 40) {
        int misfortuneType = rand() % 100;

        if (misfortuneType < 30) {
            // 30% chance - Your team is robbed!
            // Implement the logic for this misfortune here
            inventory_.gold -= 10;
            for(int i = 0; i < 3; i++) {
                if(inventory_.cookware[i] > 0) {
                    inventory_.cookware[i] -= 1;
                    break;
                }
            }
            inventory_.armor -= 1;
            std::cout << "OH NO! Your team was robbed by dungeon bandits!\n";
            std::cout << "You lost 1 Cauldron!\n";
        } else if (misfortuneType < 40) {
            // 10% chance - One of the weapons/armor breaks
            // Implement the logic for this misfortune here
            int ran = rand() % 5;
            inventory_.weapons[ran] -= 1;
            if(inventory_.weapons[ran] < 0) {
                inventory_.weapons[ran] = 0;
            }
            std::cout << "OH NO! Your +1 Rapier broke!\n";
        } else if (misfortuneType < 70) {
            // 30% chance - Food poisoning
            // Implement the logic for this misfortune here
            int ran = rand() % 3+1;
            party_.getMember(ran).decreaseFullness(10);
        } else {
            // 30% chance - Team member locked in the previous room
            // Implement the logic for this misfortune here
            int j = rand() % 3 + 1;
            party_.getMember(j).setFullness(0);
            party_.getMember(j).setName("Dead");
            std::cout << "OH NO! Your teammate Jot is trapped in the previous room and is unable to get through. You must continue without them.\n";
            std::cout << "Your party size has reduced to 4 members.\n";
        }
    }
}
