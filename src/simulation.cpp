#include <../include/simulation.hpp>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

Grid::Grid(): grid() {};

bool Grid::set_cell_value(int value, int i, int j) {
    if (i < 0 || i >= ROWS || j < 0 || j >= COLUMNS) return false;
    grid[i][j] = value;
    return true;
}

// Remember grid is zero-value initialized
Environment::Environment() : grid(), live_cells(INIT), generations(INIT) {};

Simulation::Simulation(SDL_Window * window, SDL_Surface * window_surface)
    : window(window), window_surface(window_surface) {};

void Simulation::run_simulation(void) {
    bool simulation_running = window && window_surface;
    Environment current_state;
    SDL_Event event;
    while(simulation_running) {
        while(SDL_PollEvent(&event)) {
            simulation_step(current_state);
        }
        show_environment(current_state);
        SDL_UpdateWindowSurface(window);
    }
    return;
}

void Simulation::simulation_step(Environment env) {
    return;
}

