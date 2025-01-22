#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include "include/simulation.hpp"
#include "include/error_management.hpp"
#include "include/formats.hpp"

int main(void) {
    CHECK_ERRORS(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());

    SDL_Window * window = SDL_CreateWindow("Welcome to Conway's Game Of Life",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    CHECK_ERRORS(window == NULL, SDL_GetError());

    SDL_Surface * window_surface = SDL_GetWindowSurface(window);
    CHECK_ERRORS(window_surface == NULL, SDL_GetError());

    Simulation(*window, *window_surface).run_simulation();

    SDL_DestroyWindowSurface(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game over!" << std::endl;
    return 0;
}

