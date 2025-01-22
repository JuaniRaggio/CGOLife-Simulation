# CGOLife-Simulation
---
![showcase](assets/output.gif)
### Supported keybinds
- SPACE_BAR: Start game with current initial state / Stop game
- Click: Add new live cell / Stop game if running
- r: New randomized state
- x: Sets all cells to Dead mode
- c: Cool initial state with glinders and well-known patterns

### Rules
The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

### Compilation process
1. Source *env.sh*
```sh
source env.sh
```
2. Execute *build.sh* to compile main file
```sh
./build.sh main.cpp
```
3. Execute game
```sh
./a.out
```

