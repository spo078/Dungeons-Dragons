#include "status.h"
#include "inventory.h"
#include "party.h"
#include <iostream>
#include <iomanip>
void Status::minusKey() {
    keys--;
}
void Status::updRooms() {
    roomsCleared++;
}
void Status::updKeys() {
    keys++;
}
void Status::updAnger() {
    angerLevel++;
}
int Status::getRooms() {
    return roomsCleared;
}
int Status::getKeys() {
    return keys;
}
int Status::getAnger() {
    return angerLevel;
}
void Status::displayStatus(Party& party, Inventory& inv){
        std::cout << "+-------------+\n"
                << "| STATUS      |\n"
                << "+-------------+\n"
                << "| Rooms Cleared: " << getRooms() << " | Keys: " << getKeys() << " | Anger Level: " << getAnger() << "\n";
        inv.print();
        std::cout << "+-------------+\n"
                << "| PARTY       |\n"
                << "+-------------+\n";
        for (int i = 0; i < 4; i++) {
            std::cout << "| " << party.getMember(i).getName() << " | Fullness: " << party.getMember(i).getFullness() << "\n";
        }
        std::cout << "+-------------+\n";
}
void Status::fullnessByCook(Party& party, int add) {
    for(int i = 0; i < 4; i++) {
        if(party.getMember(i).getFullness() > 0 && party.getMember(i).getFullness() < 50) {
            party.getMember(i).addFullness(add/5);
        }
        else{
            return; 
        }
    }
}

