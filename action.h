#ifndef ACTION_H
#define ACTION_H

#include "party.h"
#include "inventory.h"
#include "map.h"
#include "status.h"
#include "cook.h"
#include "fight.h"
#include "player.h"
#include "merchant.h"
#include "misfortune.h"

class Action {
public:
    Action(Party& party, Inventory& inventory, Map& map, Cook& cook, Fight& fight, Player& player, Status& status, Merchant& merhchant, Misfortune& misfortune);
    bool actionMenu(Status& status, Map& map, Misfortune& misfotune, Party& party);
    bool normalSpaceActions(Status& status, Misfortune& misfortune);
    bool npcSpaceActions(Status& status, Inventory& inventory, Merchant& merchant, Misfortune& misfortune);
    bool roomSpaceActions(Status& status, Fight& fight, Misfortune& misfortune);
    bool hasGivenUp() const;

private:
    Party& party_;
    Inventory& inventory_;
    Map& map_;
    Cook& cook_;
    Fight& fight_;
    Player& player_;
    Status& status;
    Merchant& merchant_;
    Misfortune& misfortune_;
    //NPC& npc_;

    void move();
    void investigate();
    void pickFight();
    void cookEat();
    void giveUp();

    void speakToNpc();
    void openDoor();
    bool givenUp_;
   // void fightMonster(Monster& monster);
    void handleMisfortune();
};

#endif // ACTION_H
