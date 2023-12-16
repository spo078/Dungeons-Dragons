#ifndef MONSTER_H
#define MONSTER_H

#include <string>

class Monster {
public:
    Monster(const std::string& name, int difficulty);

    const std::string& getName() const;
    int getDifficulty() const;

    // Add other member functions as needed for simulating fights

private:
    std::string name_;
    int difficulty_;
    // Add other member variables as needed for simulating fights, like health, attack power, etc.
};

#endif // MONSTER_H
