#include "randomizer.h"

Randomizer::Randomizer(int min_row, int max_row, int min_col, int max_col)
    : generator_(static_cast<unsigned>(std::time(nullptr))),
      row_distribution_(min_row, max_row - 1),
      col_distribution_(min_col, max_col - 1) {
}

int Randomizer::getRandomRow() {
    return row_distribution_(generator_);
}

int Randomizer::getRandomCol() {
    return col_distribution_(generator_);
}
