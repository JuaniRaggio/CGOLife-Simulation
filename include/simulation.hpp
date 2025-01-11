#pragma once

#include "formats.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <array>

#define INIT 0
#define DEAD_CELL 0
#define LIVE_CELL 1

class Grid {
    private:
        // zero-value initialization
        std::array<std::array<int, COLUMNS>, ROWS> grid = {};
    public:
        Grid();
        bool set_cell_value(int value, int i, int j);
};

// Using int because SDL uses int
class Environment {
    private:
        Grid grid;
        size_t generations;
        size_t live_cells;
    public:
        Environment();
};

class Simulation {
    private:
        SDL_Window * window;
        SDL_Surface * window_surface;
    public:
        Simulation(SDL_Window * window, SDL_Surface * window_surface);
        void run_simulation(void);
        bool event_reaction(SDL_Event event, SDL_Window * window, SDL_Surface * window_surface);
        void simulation_step(Environment env);
        void show_environment(Environment env);
};

