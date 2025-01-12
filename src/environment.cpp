#include "../include/environment.hpp"
#include <random>

#define INVALID_IDX -1

Grid::Grid(): grid() {};

bool Grid::valid_id(int i, int j) {
    return ((i) >= 0 && (i) < (ROWS) && (j) >= 0 && (j) < (COLUMNS));
}

bool Grid::set_cell_value(int value, int i, int j) {
    // If out of range, return false and do nothing
    if (!valid_id(i, j)) return false;
    grid[i][j] = value;
    return true;
}

int Grid::get_cell(int i, int j) {
    // Using INVALID_IDX aka -1 might be problematic if the grid accepts -1 as a valid number. In this case, wi won't
    // be using negative values so works for now
    if (!valid_id(i, j)) return INVALID_IDX;
    return grid[i][j];
}

void Grid::assign_new_grid(std::array<const std::array<int, COLUMNS>, ROWS> new_values) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            grid[i][j] = new_values[i][j];
        }
    }
}

void Grid::grid_randomizer(void) {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (auto& row: grid) {
        for (int& element: row) {
            std::bernoulli_distribution bernoulli_dist(0.2);
            element = bernoulli_dist(gen);
        }
    }
}

// Remember grid is zero-value initialized
Environment::Environment() : grid(), live_cells(INIT), generations(INIT) {};

int Environment::get_cell_atidx(int i, int j) {
    return grid.get_cell(i, j);
}

bool Environment::get_state(void) {
    return running_state;
}
void Environment::swap_state(void) {
    running_state = !running_state;
}

void Environment::swap_cell_value(Sint32 i, Sint32 j) {
    int new_value = !grid.get_cell(i, j);
    grid.set_cell_value(new_value, i, j);
}

void Environment::apply_rules(void) {
    // Rules
}

void Environment::generate_random_environment(void) {
    grid.grid_randomizer();
}


