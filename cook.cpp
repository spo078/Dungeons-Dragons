#include "cook.h"
#include "party.h"
#include "inventory.h"
#include "status.h"
#include <random>
#include <ctime>
#include <iostream>

using namespace std;
Cook::Cook(Party& party, Inventory& inventory, Status& status)
    : party_(party), inventory_(inventory), status_(status) {}

/*void Cook::cookAndEat() {
    if (Inventory::ingredients == 0) {
        cout << "You have no food to cook." << endl;
        return;
    }

    inventory_.displayCookware();
    int cookwareChoice;
    cout << "Select the cookware you want to use (enter the corresponding number):" << endl;
    cin >> cookwareChoice;

    Cookware selectedCookware = inventory_.getCookwareByIndex(cookwareChoice - 1);

    int kgToCook;
    cout << "How many kg of food do you want to cook (in increments of 5 kg)? ";
    cin >> kgToCook;

    if (kgToCook % 5 != 0 || kgToCook > inventory_.getFood()) {
        cout << "Invalid amount of food to cook." << endl;
        return;
    }

    int fullnessIncrease = kgToCook / 5;
    int successChance = rand() % 100;

    if (successChance < selectedCookware.successRate) {
        cout << "Successfully cooked a meal!" << endl;
        party_.increaseFullnessForAll(fullnessIncrease);
        inventory_.consumeFood(kgToCook);
    } else {
        cout << "Cooking failed. The cookware broke, and the ingredients are lost." << endl;
        inventory_.removeCookware(cookwareChoice - 1);
        inventory_.consumeFood(kgToCook);
    }

    party_.displayFullnessLevels();
    cout << "Remaining kg of food: " << inventory_.getFood() << endl;
}*/
void Cook::display() {
    std::srand(std::time(0));

// Generate a random number between 0 and 99
    int chance = std::rand() % 100;
    int foodamount;
    int cookware;
    cout << "Great Idea to cook and recover your fullness!!!" << endl;
    cout << "Here is the amount of food you have! " << inventory_.getIngredients() << " and here are you cookware1 P: " << inventory_.cookware[0] << " F: " << inventory_.cookware[1] << " C: " << inventory_.cookware[2] << endl;
    cout << "Enter the amount of food you want to cook(in increments of 5kg)" << endl;
    cin >> foodamount;
    if(foodamount % 5 == 0) {
        cout << "Choose your cookware(Options - 1, 2, 3)" << endl;
        cin >> cookware;
        inventory_.consumeFood(cookware);
        if((cookware == 1 || cookware == 2 || cookware == 3) && (inventory_.cookware[0] > 0 || inventory_.cookware[1] > 0 || inventory_.cookware[2] > 0)) {
            switch (cookware)
            {
            case 1:
                status_.fullnessByCook(party_, foodamount);
                inventory_.ingredients -= foodamount;
                if (chance < 25) {
                    inventory_.cookware[0] -= 1;
                } 
                return;
            break;
            case 2:
                status_.fullnessByCook(party_, foodamount);
                inventory_.ingredients -= foodamount;
                if (chance < 10) {
                    inventory_.cookware[1] -= 1;
                }
                return;
            break;
            case 3:
                status_.fullnessByCook(party_, foodamount);
                inventory_.ingredients -= foodamount;
                if (chance < 2) {
                    inventory_.cookware[2] -= 1;
                }
                return;
            break;
            
            default:
             cout << "Enter correct number" << endl;
             return;
            break;
            }
        }
        else{
            cout << "Please follow the instructios you need to have at least one cookware and select correct number 1, 2 or 3" << endl;
            return;
        }
    }
    else{
        cout << "Please follow instructions you need to enter in ingredients as increments of 5 kg" << endl;
        return;
    }
    
}
