#include "party.h"
#include "inventory.h"
#include "status.h"
class Cook {
public:
    Cook(Party& party, Inventory& inventory, Status& status);
    //void cookAndEat();
    Cook();
    void display();

private:
    Party& party_;
    Inventory& inventory_;
    Status& status_;
};
