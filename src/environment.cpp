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

int Grid::assign_new_grid(std::array<std::array<int, COLUMNS>, ROWS> new_values) {
    int live_cells = 0;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            grid[i][j] = new_values[i][j];
            live_cells += grid[i][j];
        }
    }
    return live_cells;
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

int Environment::value_at_next_step(int current_value, int i, int j) {
    int live_neighbours = 0;
    for (int sub_i = i - 1; sub_i <= i + 1; ++sub_i) {
        for (int sub_j = j - 1; sub_j <= j + 1; ++sub_j) {
            if ((sub_i != i || sub_j != j) && sub_i > 0 && sub_j > 0 && sub_i < ROWS && sub_j < COLUMNS)
                live_neighbours += grid.get_cell(sub_i, sub_j) == LIVE_CELL;
        }
    }
    if (current_value == DEAD_CELL) {
        return live_neighbours == 3 ? LIVE_CELL:DEAD_CELL;
    }
    return (live_neighbours < 2 || live_neighbours > 3) ?
        DEAD_CELL:((live_neighbours == 2 || live_neighbours == 3) ? LIVE_CELL:DEAD_CELL);
    /* 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation. */
    /* 2. Any live cell with two or three live neighbours lives on to the next generation. */
    /* 3. Any live cell with more than three live neighbours dies, as if by overpopulation. */
    /* 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. */
}

void Environment::apply_rules(void) {
    // Rules
    std::array<std::array<int, COLUMNS>, ROWS> aux_grid = {};
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            aux_grid[i][j] = value_at_next_step(grid.get_cell(i, j), i, j);
        }
    }
    live_cells = grid.assign_new_grid(aux_grid);
    generations++;
}

void Environment::generate_random_environment(void) {
    grid.grid_randomizer();
}


