#ifndef MERCHANT_H
#define MERCHANT_H

#include "inventory.h"
#include "status.h"

class Merchant {
public:
    Inventory& player_inventory;
    Status& status;
    int rooms_cleared = status.getRooms();

    Merchant(Inventory& inv, Status& status);

    bool merchant_menu();

    void buy_ingredients();

    void buy_cookware();

    void buy_weapons();

    void buy_armor();

    void sell_treasures();
    
    int adjusted_price(int base_price);
};

#endif // MERCHANT_H
