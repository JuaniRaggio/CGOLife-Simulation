#pragma once

#include "environment.hpp"
#include <SDL2/SDL.h>

#define DEAD_CELL 0
#define LIVE_CELL 1


class Simulation {
    private:
        Environment env;
        SDL_Window& window;
        SDL_Surface& window_surface;
        void show_grid(void);
        void show_lines(Uint32 color, int x_init_point, int y_init_point, int limit,
                int line_length, int line_thickness);
        bool event_reaction(SDL_Event& event);
        void click_reaction(SDL_MouseButtonEvent& mouse_event);
        void keyboard_reaction(SDL_KeyboardEvent& keyboard_event);
        void simulation_step(void);
        void show_environment(void);
    public:
        Simulation(SDL_Window & window, SDL_Surface & window_surface);
        void run_simulation(void);
};

