#ifndef MISFORTUNE_H
#define MISFORTUNE_H

#include "party.h"
#include "inventory.h"

class Misfortune {
public:
    Misfortune(Party& party, Inventory& inventory);
    void triggerMisfortune();

private:
    Party& party_;
    Inventory& inventory_;
};

#endif // MISFORTUNE_H
