#include "merchant.h"
#include <iostream>
#include <cmath>
#include <string>

Merchant::Merchant(Inventory& inv, Status& status) : player_inventory(inv), status(status){}

bool Merchant::merchant_menu() {
    int choice;
    while (true) {
        player_inventory.print();

        std::cout << "Choose one of the following:\n";
        std::cout << " 1. Ingredients: To make food, you have to cook raw ingredients.\n";
        std::cout << " 2. Cookware: You will need something to cook those ingredients.\n";
        std::cout << " 3. Weapons: It's dangerous to go alone, take this!\n";
        std::cout << " 4. Armor: If you want to survive monster attacks, you will need some armor.\n";
        std::cout << " 5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands.\n";
        std::cout << " 6. Leave: Make sure you get everything you need, I'm leaving after this sale!\n\n";
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                buy_ingredients();
                break;
            case 2:
                buy_cookware();
                break;
            case 3:
                buy_weapons();
                break;
            case 4:
                buy_armor();
                break;
            case 5:
                sell_treasures();
                break;
            case 6:
                std::cout << "Goodbye! Good luck on your adventure!\n";
                return false;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void Merchant::buy_ingredients() {
    int amount;
    std::cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive multiple of 5, or 0 to cancel)\n";
    std::cout << "> ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Canceled.\n";
        return;
    }

    int cost = adjusted_price(amount);
    if (player_inventory.gold >= cost) {
        player_inventory.gold -= cost;
        player_inventory.ingredients += amount;
        std::cout << "Thank you for your patronage! What else can I get for you?\n";
    } else {
        std::cout << "You don't have enough gold to purchase that!\n";
    }
}

void Merchant::buy_cookware() {
    int cookware_choice;

    std::cout << "I have several types of cookware, which one would you like?\n";
    std::cout << "Each type has a different probability of breaking when used, marked with (XX%).\n";
    std::cout << "Choose one of the following:\n";
    std::cout << " 1. (25%) Ceramic Pot [2 Gold]\n";
    std::cout << " 2. (10%) Frying Pan [10 Gold]\n";
    std::cout << " 3. ( 2%) Cauldron [20 Gold]\n";
    std::cout << " 4. Cancel\n";
    std::cout << "> ";
    std::cin >> cookware_choice;

    if (cookware_choice == 4) {
        std::cout << "Canceled.\n";
        return;
    }

    int amount;
    std::cout << "How many would you like? (Enter a positive integer, or 0 to cancel)\n";
    std::cout << "> ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Canceled.\n";
        return;
    }

    int base_cost;
    switch (cookware_choice) {
        case 1:
            base_cost = 2;
            break;
        case 2:
            base_cost = 10;
            break;
        case 3:
            base_cost = 20;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            return;
    }

    int cost = adjusted_price(base_cost * amount);
    if (player_inventory.gold >= cost) {
        player_inventory.gold -= cost;
        player_inventory.cookware[cookware_choice - 1] += amount;
        std::cout << "Thank you for your patronage! What else can I get for you?\n";
    } else {
        std::cout << "You don't have enough gold to purchase that!\n";
    }
}


void Merchant::buy_weapons() {
    int weapon_choice;
    std::cout << "I have a plentiful collection of weapons to choose from, what would you like?\n";
    std::cout << "Note that some of them provide you a special bonus in combat, marked by a (+X).\n";
    std::cout << "Choose one of the following:\n";
    std::cout << " 1. Stone Club [2 Gold]\n";
    std::cout << " 2. Iron Spear [2 Gold]\n";
    std::cout << " 3. (+1) Mythril Rapier [5 Gold]\n";
    std::cout << " 4. (+2) Flaming Battle-Axe [15 Gold]\n";
    std::cout << " 5. (+3) Vorpal Longsword [50 Gold]\n";
        std::cout << " 6. Cancel\n";
    std::cout << "> ";
    std::cin >> weapon_choice;

    if (weapon_choice == 6) {
        std::cout << "Canceled.\n";
        return;
    }

    int amount;
    std::cout << "How many would you like? (Enter a positive integer, or 0 to cancel)\n";
    std::cout << "> ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Canceled.\n";
        return;
    }

    int base_cost;
    switch (weapon_choice) {
        case 1:
            base_cost = 2;
            break;
        case 2:
            base_cost = 2;
            break;
        case 3:
            base_cost = 5;
            break;
        case 4:
            base_cost = 15;
            break;
        case 5:
            base_cost = 50;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            return;
    }

    int cost = adjusted_price(base_cost * amount);
    if (player_inventory.gold >= cost && amount + player_inventory.getTotalWeapons() <= 4) {
        player_inventory.gold -= cost;
        player_inventory.weapons[weapon_choice - 1] += amount;
        std::cout << player_inventory.gold << std::endl;
        std::cout << cost << std::endl;
        std::cout << "Thank you for your patronage! What else can I get for you?\n";
    } else {
        std::cout << "You don't have enough gold to purchase that or you already have or selecti 4 weapons\n";
    }
}

void Merchant::buy_armor() {
    int amount;
    std::cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)\n";
    std::cout << "> ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Canceled.\n";
        return;
    }

    int base_cost = 5;
    int cost = adjusted_price(base_cost * amount);
    if (player_inventory.gold >= cost) {
        player_inventory.gold -= cost;
        player_inventory.armor += amount;
        std::cout << "Thank you for your patronage! What else can I get for you?\n";
    } else {
        std::cout << "You don't have enough gold to purchase that!\n";
    }
}

void Merchant::sell_treasures() {
    std::cout << "Here is a list of the treasures you can sell and their values:\n";
    std::cout << "1. Silver ring (R) - 10 gold pieces each\n";
    std::cout << "2. Ruby necklace (N) - 20 gold pieces each\n";
    std::cout << "3. Emerald bracelet (B) - 30 gold pieces each\n";
    std::cout << "4. Diamond circlet (C) - 40 gold pieces each\n";
    std::cout << "5. Gem-encrusted goblet (G) - 50 gold pieces each\n";
    std::cout << "6. Cancel\n";
    std::cout << "Which treasure would you like to sell? (Enter the corresponding number, or 6 to cancel)\n";
    std::cout << "> ";

    int choice;
    std::cin >> choice;

    if (choice == 6) {
        std::cout << "Canceled.\n";
        return;
    }

    std::cout << "How many would you like to sell? (Enter a positive integer, or 0 to cancel)\n";
    std::cout << "> ";

    int amount;
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "Canceled.\n";
        return;
    }

    int base_value;
    switch (choice) {
        case 1:
            base_value = 10;
            break;
        case 2:
            base_value = 20;
            break;
        case 3:
            base_value = 30;
            break;
        case 4:
            base_value = 40;
            break;
        case 5:
            base_value = 50;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            return;
    }

    if (player_inventory.treasures[choice - 1] >= amount) {
        player_inventory.treasures[choice - 1] -= amount;
        int gold_received = adjusted_price(base_value * amount);
        player_inventory.gold += gold_received;
        std::cout << "You sold " << amount << " treasure(s) for " << gold_received << " gold.\n";
        std::cout << "Thank you for your patronage! What else can I get for you?\n";
    } else {
        std::cout << "You don't have enough of that treasure to sell!\n";
    }
}

int Merchant::adjusted_price(int base_price) {
    return static_cast<long long int>(std::floor(base_price * (1 + 0.25 * rooms_cleared)));
}

