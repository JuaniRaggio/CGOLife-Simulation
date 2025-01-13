#pragma once

#include "formats.hpp"
#include <array>
#include <SDL2/SDL.h>

#define DEAD_CELL 0
#define LIVE_CELL 1
#define INIT 0
#define RUNNING true
#define COLOR_DEAD_CELL 0x00000000
#define COLOR_LIVE_CELL 0xffffffff

typedef enum {
    dead_color = COLOR_DEAD_CELL,
    live_color = COLOR_LIVE_CELL
} cell_color;

class Grid {
    private:
        // zero-value initialization
        std::array<std::array<int, COLUMNS>, ROWS> grid = {};
        bool valid_id(int i, int j);
    public:
        Grid();
        int assign_new_grid(std::array<std::array<int, COLUMNS>, ROWS> new_values);
        bool set_cell_value(int value, int i, int j);
        int get_cell(int i, int j);
        void grid_randomizer(void);
};

// Adapter
// Using int because SDL uses int
class Environment {
    private:
        Grid grid;
        bool running_state = {!RUNNING};
        size_t generations;
        size_t live_cells;
        int value_at_next_step(int current_value, int i, int j);
        int get_normalization(int idx, int upper_limit);
    public:
        Environment();
        int get_cell_atidx(int i, int j);
        bool get_state(void);
        void swap_state(void);
        void swap_cell_value(Sint32 i, Sint32 j);
        void apply_rules(void);
        void generate_random_environment(void);
        void set_environment_to(std::array<std::array<int, COLUMNS>, ROWS> value);
};

