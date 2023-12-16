#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Map
{
private:
    

    static const int num_rows_ = 12; // number of rows in map
    static const int num_cols_ = 12; // number of columns in map
    static const int max_npcs_ = 5;  // max non-player characters
    static const int max_rooms_ = 5; // max number of rooms
    

    int player_position_[2];              // player position (row,col)
    int dungeon_exit_[2];                 // exit location of the dungeon
    int npc_positions_[max_npcs_][3];     // stores the (row,col) positions of NPCs present on map and if they have been found
    int room_positions_[max_rooms_][2];   // stores the (row,col) positions of rooms present on map
    char map_data_[num_rows_][num_cols_]; // stores the character that will be shown at a given (row,col)

    int npc_count_;  // stores number of misfortunes currently on map
    int room_count_; // stores number of sites currently on map
    int startingRow_ = 0;
    int startingCol_ = 0;
public:
    static const char UNEXPLORED = '-'; // marker for unexplored spaces
    static const char EXPLORED = ' ';   // marker for explored spaces
    static const char ROOM = 'R';       // marker for room locations
    static const char NPC = 'N';        // marker for NPC locations
    static const char PARTY = 'X';      // marker for party position
    static const char EXIT = 'E';       // marker for dungeon exit
    static const char INVALID = '!';
    Map();

    void resetMap();
    void print() const;
    void investigateSpace();

    // getters
    int getPlayerRow();
    int getPlayerCol();
    int getDungeonExitRow();
    int getDungeonExitCol();
    int getRoomCount();
    int getNPCCount();
    int getNumRows();
    int getNumCols();
    bool isOnMap(int row, int col);
    bool isNPCLocation(int row, int col);
    bool isRoomLocation(int row, int col);
    bool isExplored(int row, int col);
    bool isFreeSpace(int row, int col);
    bool isDungeonExit(int row, int col);
    char getSpaceType(int row, int col);
    int getClearedRooms() const;

    // setters
    void setPlayerPosition(int row, int col);
    void setDungeonExit(int row, int col);

    // other
    void displayMap();
    bool move(char);
    bool addNPC(int row, int col);
    bool addRoom(int row, int col);
    void removeNPC(int row, int col);
    void removeRoom(int row, int col);
    void exploreSpace(int row, int col);
    int getStartingRow() const;
    int getStartingCol() const;
};

#endif