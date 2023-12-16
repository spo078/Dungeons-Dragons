#include "monster.h"

Monster::Monster(const std::string& name, int difficulty)
    : name_(name), difficulty_(difficulty) {}

const std::string& Monster::getName() const { return name_; }
int Monster::getDifficulty() const { return difficulty_; }

// Implement other member functions as needed for simulating fights
