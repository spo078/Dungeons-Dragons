#include "inventory.h"
#include <iostream>
using namespace std;

Inventory::Inventory() : gold(100), ingredients(0), cookware(3, 0), weapons(5, 0), armor(0), treasures(5, 0) {}

void Inventory::print() {
    std::cout << "+-------------+\n";
    std::cout << "| INVENTORY   |\n";
    std::cout << "+-------------+\n";
    std::cout << "| Gold        | " << gold << '\n';
    std::cout << "| Ingredients | " << ingredients << " kg\n";
    std::cout << "| Cookware    | P: " << cookware[0] << " | F: " << cookware[1] << " | C: " << cookware[2] << '\n';
    std::cout << "| Weapons     | C: " << weapons[0] << " | S: " << weapons[1] << " | R: " << weapons[2] << " | B: " << weapons[3] << " | L: " << weapons[4] << '\n';
    std::cout << "| Armor       | " << armor << '\n';
    std::cout << "| Treasures   | R: " << treasures[0] << " | N: " << treasures[1] << " | B: " << treasures[2] << " | C: " << treasures[3] << " | G: " << treasures[4] << "\n\n";
}

void Inventory::addKey() {
    keys + 1;
}

int Inventory::getKeys() {
    return keys;
}
int Inventory::getTotalWeapons() const {
    int totalWeapons = 0;

    for (const int weaponQuantity : weapons) {
        totalWeapons += weaponQuantity;
    }

    return totalWeapons;
}

void Inventory::addTreasure() {
    srand(time(0));
    int rando = rand() % 5;
    treasures[rando]++;
}
int Inventory::getIngredients() const {
    return ingredients;
}

std::vector<int> Inventory::getCookware() const {
    return cookware;
}
void Inventory::consumeFood(int kg) {
    if (kg > 0 && kg <= ingredients) {
        ingredients -= kg;
    }
}

void Inventory::removeCookware(int index) {
    if (index >= 0 && index < cookware.size()) {
        cookware.erase(cookware.begin() + index);
    }
}
void Inventory::addGold(int num) {
    gold += num;
}
void Inventory::addIngredients(int num) {
    ingredients += num;
}
int Inventory::getArmor() {
    return armor;
}


/*void Inventory::displayForCook() {
    cout << "Remaining Ingredients" << Inventory::ingredients << endl;
    cout << "Updated"
}*/