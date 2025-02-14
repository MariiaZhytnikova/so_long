# so_long
42 school project

So_Long is a 2D puzzle game where the player navigates through a grid-based environment to reach a goal while avoiding obstacles. The game is built using the C programming language, and it uses the MLX42 library for graphical rendering.

## Features

- **Player Movement**: Move the player using arrow or W, A, S, and D keys in the 2D world.
- **Level Design**: Explore different maze-like levels, each with unique challenges.
- **Objective**: Collect all items and reach the exit point.
- **Graphics**: Simple yet engaging 2D graphics rendered using the MLX42 library.

  The bonus part includes the enemies: Watch out for enemies that move around the level. If the player touches an enemy, the game is over. Enemies patrol specific paths, so timing and strategy are key to avoiding them.

## Requirements

- C compiler (GCC recommended)
- Make tool
- [MLX42](https://github.com/codam-coding-college/MLX42) for graphical rendering
- Linux-based operating system (or compatible environment with MiniLibX support)

## Installation

### Clone the repository

    github.com/MariiaZhytnikova/so_long.git
    cd so_long

### Compile the project

Make sure you have make and the required dependencies installed. Then, run the following command to build the project:

    make

For bonus run:

    make bonus

### Run the game

Once the project is compiled, you can run the game with:

    ./so_long map.ber
    ./so_long_bonus map.ber

### Map is the level map file (you can create your own or use the default ones).

• The map is constructed with 3 components: walls, collectibles, and free space.
  The bonus part contain enemies.
  
• The map can be composed of only these characters:
    0 for an empty space,
    1 for a wall,
    C for a collectible,
    E for a map exit,
    P for the player’s starting position
    A for the enemies

