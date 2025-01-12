#pragma once

#include "formats.hpp"
#include <array>
#include <random>
#include <SDL2/SDL.h>

#define INIT 0
#define RUNNING true

class Grid {
    private:
        // zero-value initialization
        std::array<std::array<int, COLUMNS>, ROWS> grid = {};
        bool valid_id(int i, int j);
    public:
        Grid();
        void assign_new_grid(std::array<const std::array<int, COLUMNS>, ROWS> new_values);
        bool set_cell_value(int value, int i, int j);
        int get_cell(int i, int j);
        void grid_randomizer(void);
};

// Using int because SDL uses int
class Environment {
    private:
        Grid grid;
        bool running_state = {!RUNNING};
        size_t generations;
        size_t live_cells;
    public:
        Environment();
        bool get_state(void);
        void swap_state(void);
        void swap_cell_value(Sint32 i, Sint32 j);
        void apply_rules(void);
        void generate_random_environment(void);
};

