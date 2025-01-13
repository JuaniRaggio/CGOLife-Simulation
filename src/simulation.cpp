#include "../include/simulation.hpp"
#include "../include/formats.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

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
        simulation_step();
        show_environment();
        SDL_UpdateWindowSurface(&window);
        SDL_Delay(100);
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

static void createPatternMatrix(std::array<std::array<int, COLUMNS>, ROWS>& matrix) {
    // **Gosper Glider Gun**
    int gunX = 5, gunY = 5;
    int gosperGun[][2] = {
        {0, 24}, {1, 22}, {1, 24}, {2, 12}, {2, 13}, {2, 20}, {2, 21}, {2, 34}, {2, 35},
        {3, 11}, {3, 15}, {3, 20}, {3, 21}, {3, 34}, {3, 35}, {4, 0},  {4, 1},  {4, 10},
        {4, 16}, {4, 20}, {4, 21}, {5, 0},  {5, 1},  {5, 10}, {5, 14}, {5, 16}, {5, 17},
        {5, 22}, {5, 24}, {6, 10}, {6, 16}, {6, 24}, {7, 11}, {7, 15}, {8, 12}, {8, 13}
    };
    for (auto &cell : gosperGun) {
        matrix[gunY + cell[0]][gunX + cell[1]] = 1;
    }

    // **Glider**
    int gliderX = 50, gliderY = 50;
    int glider[][2] = {
        {0, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}
    };
    for (auto &cell : glider) {
        matrix[gliderY + cell[0]][gliderX + cell[1]] = 1;
    }

    // **Lightweight Spaceship (LWSS)**
    int lwssX = 80, lwssY = 30;
    int lwss[][2] = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 0}, {1, 4}, {2, 4}, {3, 0}, {3, 3}
    };
    for (auto &cell : lwss) {
        matrix[lwssY + cell[0]][lwssX + cell[1]] = 1;
    }
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
        case SDLK_c:
            std::array<std::array<int, COLUMNS>, ROWS> mat;
            createPatternMatrix(mat);
            env.set_environment_to(mat);
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

