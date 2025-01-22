#!/bin/bash

g++ $1 src/* -g -std=c++20 -fsanitize=address -O2 -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
