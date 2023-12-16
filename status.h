#ifndef STATUS_H
#define STATUS_H

#include <vector>
#include <string>
#include "party.h"
#include "inventory.h"
using namespace std;

class Status {
    public:
        void updRooms();
        void updKeys();
        void updAnger();
        void displayStatus(Party& party, Inventory& inv);
        int getRooms();
        int getKeys();
        int getAnger();
        void minusKey();
        void fullnessByCook(Party& party, int add);
        int angerLevel  = 0;
    private:
        int roomsCleared = 0;
        int keys = 0;
};

#endif // STATUS_H
