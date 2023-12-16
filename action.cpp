#include "action.h"
#include "merchant.h"
#include "map.h"
#include "party.h"
#include "status.h"
#include "fight.h"
#include "player.h"
#include "misfortune.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

Action::Action(Party &party, Inventory &inventory, Map& map, Cook &cook, Fight &fight, Player &player, Status &status, Merchant& merchant, Misfortune& misfortune)
    : party_(party), inventory_(inventory), map_(map), cook_(cook), fight_(fight), player_(player), status(status), merchant_(merchant), misfortune_(misfortune) {}


bool alive(Party party_) {
    for(int i = 0; i < 4; i++) {
        int count = 0;
            if(party_.getMember(i).getFullness() == 0) {
                count++;
            }
            if(count > 2) {
                return false;
            }
        }
        return true;
}


bool Action::actionMenu(Status &status, Map &map_, Misfortune& misfortune_, Party& party)
{
    if (status.angerLevel == 100)
    {
        cout << "Sorcerer destroyed you... Game over" << endl;
        return false;
    }
    int playerRow = map_.getPlayerRow();
    int playerCol = map_.getPlayerCol();
    //char spaceType = map_.getSpaceType(playerRow, playerCol);
    if (map_.isNPCLocation(playerRow, playerCol) == true) {
        cout << "NPC: If you just solve the riddle move on" << endl;
        return npcSpaceActions(status, inventory_, merchant_, misfortune_);
    }
    else if (map_.isRoomLocation(playerRow, playerCol) == true)
    {
        cout << "ROOM: If you just passed this room move on" << endl;
        
        return roomSpaceActions(status, fight_, misfortune_);
    }
    else if(map_.isDungeonExit(playerRow, playerCol) == true && status.getRooms() == 5 && alive(party_) == true) {
        cout << "Congratulations!!! You won the game" << endl;
        return false;
    }
    else {
        return normalSpaceActions(status, misfortune_);
    }
    return true;
}
std::vector<std::pair<std::string, std::string>> parseRiddlesFromFile(const std::string &filename)
{
    std::vector<std::pair<std::string, std::string>> riddles;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return riddles;
    }

    std::string line;
    while (std::getline(file, line))
    {
        size_t delimiterPos = line.find('~');

        if (delimiterPos != std::string::npos)
        {
            std::string riddle = line.substr(0, delimiterPos);
            std::string answer = line.substr(delimiterPos + 1);
            riddles.push_back(std::make_pair(riddle, answer));
        }
    }

    file.close();
    return riddles;
}

bool Action::normalSpaceActions(Status &status, Misfortune& misfotune)
{
    srand(time(0));
    int choice = 0;
    while ((choice > 1 && choice < 5) || (choice < 1 || choice > 5))
    {
        status.displayStatus(party_, inventory_); // Call displayStatus() method
        map_.displayMap();                        // Call displayMap() method
        char direction;
        cout << " Select one:\n"
             << "1. Move\n"
             << "2. Investigate\n"
             << "3. Pick a Fight\n"
             << "4. Cook and Eat\n"
             << "5. Give up" << endl;
        int playerRow = map_.getPlayerRow();
        int playerCol = map_.getPlayerCol();
        cout << "Your Position on map" << endl;
        cout << playerCol << ", " << playerRow << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Choose the direction\n"
                 << "1. w\n"
                 << "2. s\n"
                 << "3. a\n"
                 << "4. d\n"
                 << endl;
            cin >> direction;
            map_.move(direction);
            cout << "Let'go" << endl;
            status.updAnger();

            // Handle fullness level drop chance
            for (int i = 0; i < 3; i++)
            {
                int dropChance = rand() % 100;
                if (dropChance < 20)
                {
                    party_.decreaseFullness(i, 1);
                }
            }
            break;
        case 2:
        {
            int playerRow = map_.getPlayerRow();
            int playerCol = map_.getPlayerCol();
            if (map_.isExplored(playerRow, playerCol) == false)
            {
                map_.exploreSpace(playerRow, playerCol);

                int investigateChance = rand() % 100;

                if (investigateChance < 10)
                {
                    // 10% chance to find the key
                    status.updKeys();
                    cout << "You found a key!!!" << endl;
                }
                else if (investigateChance < 30 && investigateChance > 10)
                {
                    // 20% chance to find treasure
                    int treasure = map_.getClearedRooms();
                    inventory_.addTreasure();
                    cout << "You found a treasure!!!" << endl;
                }
                else if (investigateChance < 50 && investigateChance > 30)
                {
                    // 20% chance to fight a monster
                    // ... (code for fighting a monster and potentially getting a key)
                    cout << "MONSTER!!!" << endl;
                    //fighting a moster
                    {
                        string monsternum = fight_.chooseMonster(status);
                        int choice_;
                        int chance = rand() % 4;
                        vector<pair<string, int>> monsterstats = fight_.monsterOption(monsternum);
                        cout << "You are going to fight " << monsterstats[chance].first << ", the rating of monster " << monsterstats[chance].second << endl;
                        cout << "1.Attack\n"
                             << "2.Surrender" << endl;
                        cin >> choice_;
                        if (choice_ == 1)
                        {
                            if (fight_.attackMonster(inventory_, party_, status) == true)
                            {
                                fight_.winCase(inventory_, status);
                            }
                            else
                            {
                                fight_.loseCase(inventory_, party_, player_);
                            }
                        }
                        else if (choice_ == 2)
                        {
                            fight_.Surrender(party_);
                        }
                        else
                        {
                            cout << "Wrong Input, try again" << endl;
                            return true;
                        }
                    }
                }
                else
                {
                    cout << "The place is now explored!, you are lucky to not fight mosnter but not enough lucky to get treasure or key :)" << endl;
                }

                // Decrease fullness level with 50% chance
                for (int i = 0; i < party_.getPartySize(); i++)
                {
                    int dropChance = rand() % 100;
                    if (dropChance < 50)
                    {
                        party_.decreaseFullness(i, 1);
                    }
                }
            }
            else
            {
                cout << "This space has already been explored. Please choose another option." << endl;
            }
        misfortune_.triggerMisfortune();
        }
        break;
        case 3:
        {
            cout << "Fighting is the only way to be remembered!!!" << endl;
            //fight.cpp
            {
                string monsternum = fight_.chooseMonster(status);
                int choice_;
                int chance = rand() % 4;
                vector<pair<string, int>> monsterstats = fight_.monsterOption(monsternum);
                cout << "You are going to fight " << monsterstats[chance].first << ", the rating of monster " << monsterstats[chance].second << endl;
                cout << "1.Attack\n"
                     << "2.Surrender" << endl;
                cin >> choice_;
                if (choice_ == 1)
                {
                    if (fight_.attackMonster(inventory_, party_, status) == true)
                    {
                        fight_.winCase(inventory_, status);
                    }
                    else
                    {
                        fight_.loseCase(inventory_, party_, player_);
                        if (party_.getMember(0).getFullness() + party_.getMember(1).getFullness() + party_.getMember(2).getFullness() + party_.getMember(3).getFullness() == party_.getMember(0).getFullness())
                        {
                            cout << "You are alone.. Game over" << endl;
                            return false;
                        }
                    }
                }
                else if (choice_ == 2)
                {
                    fight_.Surrender(party_);
                    if (party_.getMember(0).getFullness() + party_.getMember(1).getFullness() + party_.getMember(2).getFullness() + party_.getMember(3).getFullness() == party_.getMember(0).getFullness())
                    {
                        cout << "You are alone.. Game over" << endl;
                        return false;
                    }
                }
                else
                {
                    cout << "Wrong Input, try again" << endl;
                    return true;
                }
            }
            //countng the players rate
            //if rate > winCase, if rate < loseCase
        }
        misfortune_.triggerMisfortune();
        break;
        case 4:
            cout << "You can't be ready for adventures if you are hungry (─‿‿─)" << endl;
            cook_.display();
            misfortune_.triggerMisfortune();
            break;
        case 5:
            cout << "Game Over... Noboody will remember you (╥╯﹏╰╥)" << endl;
            return false;
            break;
        default:
            cout << "Enter correct number" << endl;
            return true;
            break;
        }
    }
    return true;
}

bool Action::npcSpaceActions(Status& status, Inventory& inventory, Merchant& merchant, Misfortune& misfortune)
{
    // Implement the NPC Space Actions as described in the question
    srand(time(0));
    int choice = 0;
    while ((choice > 1 && choice < 3) || (choice < 1 || choice > 3))
    {
        status.displayStatus(party_, inventory_); // Call displayStatus() method
        map_.displayMap();                        // Call displayMap() method
        char direction;
        cout << " Select one:\n"
             << "1. Move\n"
             << "2. Speak to NPC\n"
             << "3. Give up\n"
             << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Choose the direction\n"
                 << "1. w\n"
                 << "2. s\n"
                 << "3. a\n"
                 << "4. d\n"
                 << endl;
            cin >> direction;
            map_.move(direction);
            if (map_.isRoomLocation(map_.getNumRows(), map_.getNumCols()) == false)
            {
                cout << "Room Actions" << endl;
                status.updAnger();
            }

            // Handle fullness level drop chance
            for (int i = 0; i < 4; i++)
            {
                int dropChance = rand() % 100;
                if (dropChance < 20)
                {
                    party_.decreaseFullness(i, 1);
                }
            }
            break;
        case 2:
        {
            string answer;
            cout << "Hi, I'm asking riddles to all my guests" << endl;
            srand(time(0)); // Seed the random number generator
            int randnum = rand() % 20 + 1;
            vector<pair<string, string>> riddle = parseRiddlesFromFile("riddle.txt");
            cout << riddle[randnum].first << endl;
            cout << "What is your answer" << endl;
            cin >> answer;
            if (answer == riddle[randnum].second)
            {
                cout << "Right Answer!" << endl;
                merchant.merchant_menu();
                map_.removeNPC(map_.getPlayerRow(), map_.getPlayerCol());
                
            }
            else
            {
                cout << "Wrong Answer!" << endl;
                map_.removeNPC(map_.getPlayerRow(), map_.getPlayerCol());
                {
                    string monsternum = fight_.chooseMonster(status);
                    int choice_;
                    int chance = rand() % 4;
                    vector<pair<string, int>> monsterstats = fight_.monsterOption(monsternum);
                    cout << "You are going to fight " << monsterstats[chance].first << ", the rating of monster " << monsterstats[chance].second << endl;
                    cout << "1.Attack\n"
                         << "2.Surrender" << endl;
                    cin >> choice_;
                    if (choice_ == 1)
                    {
                        if (fight_.attackMonster(inventory_, party_, status) == true)
                        {
                            fight_.winCase(inventory_, status);
                            map_.removeNPC(map_.getPlayerRow(), map_.getPlayerCol());
                        }
                        else
                        {
                            fight_.loseCase(inventory_, party_, player_);
                            map_.removeNPC(map_.getPlayerRow(), map_.getPlayerCol());
                            if (party_.getMember(0).getFullness() + party_.getMember(1).getFullness() + party_.getMember(2).getFullness() + party_.getMember(3).getFullness() == party_.getMember(0).getFullness())
                            {
                                cout << "You are alone.. Game over" << endl;
                                return false;
                            }
                        }
                    }
                    else if (choice_ == 2)
                    {
                        fight_.Surrender(party_);
                        if (party_.getMember(0).getFullness() + party_.getMember(1).getFullness() + party_.getMember(2).getFullness() + party_.getMember(3).getFullness() == party_.getMember(0).getFullness())
                        {
                            cout << "You are alone.. Game over" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        cout << "Wrong Input, try again" << endl;
                        return true;
                    }
                }
            }
            misfortune_.triggerMisfortune();
        }
        break;
        case 3:
            cout << "Game Over... Noboody will remember you (╥╯﹏╰╥)" << endl;
            return false;
        break;
        default:
            cout << "Enter correct number" << endl;
            return true;
        break;
        }
    }
    return true;
}
bool Action::roomSpaceActions(Status& status, Fight& fight, Misfortune& misfortune)
{
    // Implement the Room Space Actions as described in the question
    srand(time(0));
    int choice = 0;
    while ((choice > 1 && choice < 3) || (choice < 1 || choice > 3))
    {
        status.displayStatus(party_, inventory_); // Call displayStatus() method
        map_.displayMap();                        // Call displayMap() method
        char direction;
        cout << " Select one:\n"
             << "1. Move\n"
             << "2. Open the door\n"
             << "3. Give up\n"
             << endl;
        cin >> choice;
        //////
        switch (choice)
        {
        case 1:
            cout << "Choose the direction\n"
                 << "1. w\n"
                 << "2. s\n"
                 << "3. a\n"
                 << "4. d\n"
                 << endl;
            cin >> direction;
            map_.move(direction);
            if (map_.isRoomLocation(map_.getNumRows(), map_.getNumCols()) == false)
            {
                cout << "Room Actions" << endl;
                status.updAnger();
            }

            // Handle fullness level drop chance
            for (int i = 0; i < 3; i++)
            {
                int dropChance = rand() % 100;
                if (dropChance < 20)
                {
                    party_.decreaseFullness(i, 1);
                }
            }
            break;
        case 2:
            map_.removeRoom(map_.getPlayerRow(), map_.getPlayerCol());
            if (status.getKeys() == 0)
            {
                int num;
                cout << "You don't have enough keys, so now you need to solve a puzzle" << endl;
                srand(time(0));
                int rando = rand() % 3;
                vector<int> puzzle = {1, 2, 3};
                int opponent = puzzle[rando];
                int count = 0;
                while (count < 3)
                {
                    cout << "Choose\n"
                         << "1.Boulder\n"
                         << "2.Parchment\n"
                         << "3.Shears\n"
                         << endl;
                    cin >> num;
                    if (opponent == num)
                    {
                        cout << "It's tie" << endl;
                        count++;
                    }
                    else if ((opponent == 1 && num == 3) || (opponent == 2 && num == 1) || (opponent == 3 && num == 2))
                    {
                        cout << "You lose" << endl;
                        count++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (count == 3)
                {
                    cout << "You lost member" << endl;
                    int j = rand() % 3 + 1;
                    party_.getMember(j).setFullness(0);
                    party_.getMember(j).setName("Dead");
                }
                else
                {
                    map_.exploreSpace(map_.getPlayerRow(), map_.getPlayerCol());
                    status.updRooms();
                    cout << "You won!!!" << endl;
                    if(status.getKeys() > 0) {
                        status.minusKey();
                    }
                    string monsternum = fight_.chooseMonsterForRoom(status);
                    int choice_;
                    int chance = rand() % 4;
                    vector<pair<string, int>> monsterstats = fight_.monsterOption(monsternum);
                    cout << "You are going to fight " << monsterstats[chance].first << ", the rating of monster " << monsterstats[chance].second << endl;
                    cout << "1.Attack\n"
                         << "2.Surrender" << endl;
                    cin >> choice_;
                    map_.exploreSpace(map_.getPlayerRow(), map_.getPlayerCol());
                    if (choice_ == 1)
                    {
                        if (fight_.attackMonster(inventory_, party_, status) == true)
                        {
                            fight_.winCase(inventory_, status);
                            
                        }
                        else
                        {
                            fight_.loseCase(inventory_, party_, player_);
                            
                            if (party_.getMember(0).getFullness() + party_.getMember(1).getFullness() + party_.getMember(2).getFullness() + party_.getMember(3).getFullness() == party_.getMember(0).getFullness())
                            {
                                cout << "You are alone.. Game over" << endl;
                                return false;
                            }
                        }
                    }
                    else if (choice_ == 2)
                    {
                        fight_.Surrender(party_);
                        
                        if (party_.getMember(0).getFullness() + party_.getMember(1).getFullness() + party_.getMember(2).getFullness() + party_.getMember(3).getFullness() == party_.getMember(0).getFullness())
                        {
                            cout << "You are alone.. Game over" << endl;
                            return false;
                        }
                    }
                    else
                    {
                        cout << "Wrong Input, try again" << endl;
                        return true;
                    }
                }
            }
            else
            {
                status.updRooms();
                string monsternum = fight_.chooseMonsterForRoom(status);
                int choice_;
                int chance = rand() % 4;
                vector<pair<string, int>> monsterstats = fight_.monsterOption(monsternum);
                cout << "You are going to fight " << monsterstats[chance].first << ", the rating of monster " << monsterstats[chance].second << endl;
                cout << "1.Attack\n"
                     << "2.Surrender" << endl;
                cin >> choice_;
                map_.exploreSpace(map_.getPlayerRow(), map_.getPlayerCol());
                if (choice_ == 1)
                {
                    if (fight_.attackMonster(inventory_, party_, status) == true)
                    {
                        fight_.winCase(inventory_, status);
                        
                    }
                    else
                    {
                        fight_.loseCase(inventory_, party_, player_);
                        if (party_.getMember(0).getFullness() + party_.getMember(1).getFullness() + party_.getMember(2).getFullness() + party_.getMember(3).getFullness() == party_.getMember(0).getFullness())
                        {
                            cout << "You are alone.. Game over" << endl;
                            return false;
                        }
                    }
                }
                else if (choice_ == 2)
                {
                    fight_.Surrender(party_);
                    if (party_.getMember(0).getFullness() + party_.getMember(1).getFullness() + party_.getMember(2).getFullness() + party_.getMember(3).getFullness() == party_.getMember(0).getFullness())
                    {
                        cout << "You are alone.. Game over" << endl;
                        return false;
                    }
                }
                else
                {
                    cout << "Wrong Input, try again" << endl;
                    return true;
                }
            }
            misfortune_.triggerMisfortune();
            break;
        case 3:
            cout << "Game Over... Noboody will remember you (╥╯﹏╰╥)" << endl;
            return false;
            break;
        default:
            cout << "Enter correct number" << endl;
            return true;
        break;
        }
    }
    return true;
}