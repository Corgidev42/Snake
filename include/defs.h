#ifndef DEFS_H
# define DEFS_H

// SIZE AND POS
# define SCREEN_WIDTH 1100
# define SCREEN_HEIGHT 900
# define SCOREBOARD_HEIGHT 50
# define SCOREBOARD_WIDTH SCREEN_WIDTH
# define GRID_HEIGHT (SCREEN_HEIGHT - SCOREBOARD_HEIGHT)
# define GRID_WIDTH SCREEN_WIDTH
# define SCOREBOARD_POS_X 0
# define SCOREBOARD_POS_Y 0//position du scoreboard
# define GRID_POS_X 0//position de la gride d'origine
# define GRID_POS_Y SCOREBOARD_HEIGHT
# define GRID_COLS 50
# define GRID_ROWS 50
# define SIZE_CELL 16

// ITEMS
# define INVENTORY_SIZE 2
# define LIFE_MAX 3
# define BASE_SPEED 1

# define LEFT 0
# define UP 1
# define RIGHT 2
# define DOWN 3


// A DEFINIR
# define APPLE_GENERATION_TIME 2000
# define OBJECT_GENERATION_TIME 20000
# define SNAKE_MOVE_TIME 1000
# define CONTAINER_MARGING 1000

# define NB_COLORS 3
# define NB_SNAKE_STATES 2
# define NB_ORIENTATIONS 4

#endif
