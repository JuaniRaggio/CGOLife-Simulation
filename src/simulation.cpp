#include "../include/simulation.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>

Simulation::Simulation(SDL_Window * window, SDL_Surface * window_surface)
    : window(window), window_surface(window_surface) {};

void Simulation::run_simulation(void) {
    bool simulation_running = window && window_surface;
    Environment current_state;
    SDL_Event event;
    while(simulation_running) {
        while(SDL_PollEvent(&event)) {
            simulation_step();
        }
    }
    return;
}

void Simulation::simulation_step(void) {
    return;
}

