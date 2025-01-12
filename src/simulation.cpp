#include "../include/simulation.hpp"
#include "../include/formats.hpp"
#include <random>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

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
            std::bernoulli_distribution bernoulli_dist(0.5);
            element = bernoulli_dist(gen);
        }
    }
}

// Remember grid is zero-value initialized
Environment::Environment() : grid(), live_cells(INIT), generations(INIT) {};

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

Simulation::Simulation(SDL_Window * window, SDL_Surface * window_surface)
    : window(window), window_surface(window_surface) {
        env = Environment();
};

void Simulation::run_simulation(void) {
    bool simulation_running = window && window_surface;
    SDL_Event event;
    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            simulation_running = event_reaction(event, window, window_surface);
        }
        show_environment();
        SDL_UpdateWindowSurface(window);
    }
    return;
}

bool Simulation::event_reaction(SDL_Event event, SDL_Window * window, SDL_Surface * window_surface) {
    if (env.get_state()) {
        env.apply_rules();
    }
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            click_reaction(event.button, window, window_surface);
            break;
        case SDL_KEYDOWN:
            keyboard_reaction(event.key, window, window_surface);
            break;
        case SDL_QUIT:
            return false;
    }
    return true;
}

void Simulation::click_reaction(SDL_MouseButtonEvent mouse_event, SDL_Window * window, SDL_Surface * window_surface) {
    if (env.get_state() != RUNNING) {
        // Get mouse coords, swap value
        int x_coord = mouse_event.x/CELL_SIZE, y_coord = mouse_event.y/CELL_SIZE;
        env.swap_cell_value(y_coord, x_coord);
    }
    env.swap_state();
}

void Simulation::keyboard_reaction(SDL_KeyboardEvent keyboard_event, SDL_Window * window, SDL_Surface * window_surface){
    switch (keyboard_event.keysym.sym) {
        case SDLK_r:
            env.generate_random_environment();
            break;
        case SDLK_SPACE:
            break;
    }
}

void Simulation::simulation_step(void) {
    return;
}

void Simulation::show_environment(void) {
    return;
}


