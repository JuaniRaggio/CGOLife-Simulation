#pragma once

#include "environment.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#define DEAD_CELL 0
#define LIVE_CELL 1


class Simulation {
    private:
        Environment env;
        SDL_Window * window;
        SDL_Surface * window_surface;
    public:
        Simulation(SDL_Window * window, SDL_Surface * window_surface);
        void run_simulation(void);
        bool event_reaction(SDL_Event event);
        void click_reaction(SDL_MouseButtonEvent mouse_event);
        void keyboard_reaction(SDL_KeyboardEvent keyboard_event);
        void simulation_step(void);
        void show_environment(void);
};

