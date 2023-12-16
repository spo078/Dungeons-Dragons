#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "merchant.h"
#include "misfortune.h"
#include "player.h"
#include "party.h"
#include "status.h"
#include "action.h"
#include "map.h"
#include "randomizer.h"
#include "monster.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


std::pair<std::string, int> getRandomMonster(const std::string& fileName) {
    std::ifstream file(fileName);
    std::vector<std::string> lines;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cout << "Unable to open file " << fileName << std::endl;
        return std::make_pair("", -1);
    }

    srand(static_cast<unsigned>(time(nullptr)));

    // Randomly choose one of the lines from the file
    int randomLineIndex = rand() % lines.size();
    std::string chosenLine = lines[randomLineIndex];

    // Extract monster name and difficulty
    std::string monsterName;
    int difficulty;
    size_t delimiter = chosenLine.find(',');

    if (delimiter != std::string::npos) {
        monsterName = chosenLine.substr(0, delimiter);
        difficulty = std::stoi(chosenLine.substr(delimiter + 1));
    } else {
        std::cout << "Unable to parse monster information" << std::endl;
        return std::make_pair("", -1);
    }

    return std::make_pair(monsterName, difficulty);
}

void enterNames(string main_player, string player_1, string player_2, string player_3, Party &party) {
    cout << "Enter the name of main player" << endl;
    cin >> main_player;
    cout << "Enter party player name" << endl;
    cin >> player_1;
    cout << "Enter party player name" << endl;
    cin >> player_2;
    cout << "Enter party player name" << endl;
    cin >> player_3;
    Player leader;
    leader.setName(main_player);
    Player p1;
    p1.setName(player_1);
    Player p2;
    p2.setName(player_2);
    Player p3;
    p3.setName(player_3);
    
    party.addMember(leader);
    party.addMember(p1);
    party.addMember(p2);
    party.addMember(p3);
}
void placeRandomEntities(Map& map) {
    int numRows = map.getNumRows();
    int numCols = map.getNumCols();
    Randomizer randomizer(0, numRows, 0, numCols);

    // Randomly place rooms
    for (int i = 0; i < 5; ++i) {
        int row, col;
        do {
            row = randomizer.getRandomRow();
            col = randomizer.getRandomCol();
        } while (!map.addRoom(row, col));
    }

    // Randomly place NPCs
    for (int i = 0; i < 5; ++i) {
        int row, col;
        do {
            row = randomizer.getRandomRow();
            col = randomizer.getRandomCol();
        } while (!map.addNPC(row, col));
    }
}

std::vector<Monster> readMonstersFromFile(const std::string& filename) {
    std::vector<Monster> monsters;
    std::ifstream inFile(filename);

    if (!inFile) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return monsters;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        size_t commaPos = line.find(',');
        std::string name = line.substr(0, commaPos);
        int difficulty = std::stoi(line.substr(commaPos + 1));
        monsters.push_back(Monster(name, difficulty));
    }

    inFile.close();
    return monsters;
}


void fight(Party& party, const Monster& monster) {
    // Implement the fight logic here based on the monster's difficulty level
    // and the party members' abilities, weapons, and armor
}


int main() {
    Player player;
    vector<Monster> monsters = readMonstersFromFile("monsters.txt");
    Map map;
    placeRandomEntities(map);
    Party party;
    string leader;
    string p1;
    string p2;
    string p3;
    enterNames(leader, p1, p2, p3, party);
    cout << "Between the 4 of you, you have 100 gold pieces.\nYou will need to spend the some of your money on the following items:\n- INGREDIENTS. To make food, you have to cook raw ingredients.\n- COOKWARE. If you want to cook, you have to have cookware first.\n- WEAPONS. You'll want at least one weapon per party member to fend off monsters.\n- ARMOR. Armor increases the chances of surviving a monster attack." << endl;
    Inventory inventory;
    Status status;
    Merchant start_merchant(inventory, status);
    start_merchant.merchant_menu();
    Misfortune misfortune(party, inventory);
    Cook cook(party, inventory, status);
    Fight fight(party, inventory, status, player);
    Action game_action(party, inventory, map, cook, fight, player, status, start_merchant, misfortune); // Create an Action object with necessary references
    bool isPlaying = true;

    while (isPlaying) {
    //status.displayStatus(party, inventory); // Call displayStatus() method
    //map.displayMap(); // Call displayMap() method
    isPlaying = game_action.actionMenu(status, map, misfortune, party); // Call the actionMenu() method

        // Check if the user has chosen the "Give up" option or another end condition is met
        // If yes, set isPlaying to false
        // For example, if the "Give up" option sets a flag in the Action class:
        // isPlaying = !game_action.hasGivenUp();
    }
    cout << "Your Achievments!" << endl;
    cout << "Numbers of rooms cleared: "<< status.getRooms() << endl;
    cout << "Gold pieces remaining: " << inventory.gold << endl;
    cout << "Number of turns elapsed: " << status.getAnger() << endl;
    cout << "Players who survived: ";
    for(int i = 0; i < 4; i++) {
        if(party.getMember(i).getName() != "Dead") {
            cout << party.getMember(i).getName() << " ";
        }
    }
    cout << endl;
    cout << "Here are treasures you got" << endl;
    std::cout << "| Treasures   | R: " << inventory.treasures[0] << " | N: " << inventory.treasures[1] << " | B: " << inventory.treasures[2] << " | C: " << inventory.treasures[3] << " | G: " << inventory.treasures[4] << "\n\n";
    cout << "The hightest level of Monster you fought: " << status.getRooms() << endl;


    return 0;
}



