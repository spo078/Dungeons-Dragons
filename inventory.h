#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

class Inventory {
public:
    Inventory();
    void print();
    void addKey();
    int getKeys();
    void addTreasure();
    int gold;
    int ingredients;
    std::vector<int> cookware;
    std::vector<int> weapons;
    int armor;
    std::vector<int> treasures;
    int keys = 0;
    int getTotalWeapons() const;
    int getIngredients() const;
    std::vector<int> getCookware() const;
    void displayCookware();
    //Cookware getCookwareByIndex(int index);
    int getFood() const;
    void consumeFood(int kg);
    void removeCookware(int index);
    void displayForCook();
    void addGold(int num);
    void addIngredients(int num);
    int getArmor();
};

#endif // INVENTORY_H
