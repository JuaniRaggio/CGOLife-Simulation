#pragma once

#include "formats.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <array>

#define DEAD_CELL 0
#define LIVE_CELL 1

// Using int because SDL uses int
class Environment {
    private:
        // Environment will be initialize with zero-value initialization
        std::array<std::array<int, COLUMNS>, ROWS> environment {};
        size_t generations {};
        size_t live_cells {};
    public:
        Environment();
        void set_cell_value(int value, int i, int j);
};

class Simulation {
    private:
        SDL_Window * window;
        SDL_Surface * window_surface;
    public:
        Simulation(SDL_Window * window, SDL_Surface * window_surface);
        void run_simulation(void);
        void simulation_step(void);
};

