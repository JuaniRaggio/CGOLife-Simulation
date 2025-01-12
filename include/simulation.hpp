#pragma once

#include "formats.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <array>

#define RUNNING true
#define INIT 0
#define DEAD_CELL 0
#define LIVE_CELL 1

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

class Simulation {
    private:
        Environment env;
        SDL_Window * window;
        SDL_Surface * window_surface;
    public:
        Simulation(SDL_Window * window, SDL_Surface * window_surface);
        void run_simulation(void);
        bool event_reaction(SDL_Event event, SDL_Window * window, SDL_Surface * window_surface);
        void click_reaction(SDL_MouseButtonEvent mouse_event, SDL_Window * window, SDL_Surface * window_surface);
        void keyboard_reaction(SDL_KeyboardEvent keyboard_event, SDL_Window * window, SDL_Surface * window_surface);
        void simulation_step(void);
        void show_environment(void);
};

