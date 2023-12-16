#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>
#include <ctime>

class Randomizer {
public:
    Randomizer(int min_row, int max_row, int min_col, int max_col);
    int getRandomRow();
    int getRandomCol();

private:
    std::default_random_engine generator_;
    std::uniform_int_distribution<int> row_distribution_;
    std::uniform_int_distribution<int> col_distribution_;
};

#endif // RANDOMIZER_H
