#!/bin/bash

clang++ -o a.out $1 src/* -std=c++20 -fsanitize=address -g -fno-omit-frame-pointer -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2

