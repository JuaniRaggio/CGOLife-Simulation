#include "../include/simulation.hpp"
#include "../include/formats.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

Simulation::Simulation(SDL_Window& window, SDL_Surface& window_surface)
    : window(window), window_surface(window_surface) {
        env = Environment();
};

void Simulation::run_simulation(void) {
    bool simulation_running = true;
    SDL_Event event;
    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            simulation_running = event_reaction(event);
        }
        show_environment();
        SDL_UpdateWindowSurface(&window);
    }
    return;
}

bool Simulation::event_reaction(SDL_Event& event) {
    if (env.get_state()) {
        env.apply_rules();
    }
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            click_reaction(event.button);
            break;
        case SDL_KEYDOWN:
            keyboard_reaction(event.key);
            break;
        case SDL_QUIT:
            return false;
    }
    return true;
}

void Simulation::click_reaction(SDL_MouseButtonEvent& mouse_event) {
    if (env.get_state() != RUNNING) {
        // Get mouse coords, swap value
        int x_coord = mouse_event.x/CELL_SIZE, y_coord = mouse_event.y/CELL_SIZE;
        env.swap_cell_value(y_coord, x_coord);
        return;
    }
    env.swap_state();
}

void Simulation::keyboard_reaction(SDL_KeyboardEvent& keyboard_event){
    switch (keyboard_event.keysym.sym) {
        case SDLK_r:
            env.generate_random_environment();
            break;
        case SDLK_SPACE:
            env.swap_state();
            break;
        // Add key bindings for more features
    }
}

void Simulation::simulation_step(void) {
    return;
}

void Simulation::show_environment(void) {
    return;
}


