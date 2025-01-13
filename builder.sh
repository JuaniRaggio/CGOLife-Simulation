#!/bin/bash

clang++ -o a.out $1 src/* -std=c++20 -fsanitize=address -O2 -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2

