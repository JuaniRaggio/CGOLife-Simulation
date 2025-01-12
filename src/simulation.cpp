#include "../include/simulation.hpp"
#include "../include/formats.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

Simulation::Simulation(SDL_Window& window, SDL_Surface& window_surface)
    : window(window), window_surface(window_surface) {
        env = Environment();
};

void Simulation::run_simulation(void) {
    const int delay_ms = 100;
    bool simulation_running = true;
    SDL_Event event;
    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            simulation_running = event_reaction(event);
        }
        simulation_step();
        show_environment();
        SDL_UpdateWindowSurface(&window);
        SDL_Delay(delay_ms);
    }
    return;
}

bool Simulation::event_reaction(SDL_Event& event) {
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
            // To run the simulation with current environment as init state
            env.swap_state();
            break;
        // Add key bindings for more features
    }
}

void Simulation::simulation_step(void) {
    if (env.get_state() == RUNNING) {
        env.apply_rules();
    }
}

void Simulation::show_environment(void) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            cell_color color = env.get_cell_atidx(i, j) == LIVE_CELL ? live_color:dead_color;
            SDL_Rect cell = (SDL_Rect) {
                .x = j * CELL_SIZE,
                .y = i * CELL_SIZE,
                .w = CELL_SIZE,
                .h = CELL_SIZE,
            };
            SDL_FillRect(&window_surface, &cell, color);
        }
    }
    show_grid();
}

void Simulation::show_lines(Uint32 color, int x_init_point, int y_init_point, int limit,
        int line_length, int line_thickness) {
    for (int position = 1; position < limit; ++position) {
        SDL_Rect line = (SDL_Rect){
            .x = position*x_init_point,
            .y = position*y_init_point,
            .w = line_thickness,
            .h = line_length
        };
        SDL_FillRect(&window_surface, &line, color);
    }
}

void Simulation::show_grid(void) {
    show_lines(LINE_COLOR, 0, CELL_SIZE, ROWS, LINE_WIDTH, INIT_SCREEN_WIDTH);
    show_lines(LINE_COLOR, CELL_SIZE, 0, COLUMNS, INIT_SCREEN_HEIGHT, LINE_WIDTH);
}

