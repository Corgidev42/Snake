#ifndef DEF_H
# define DEF_H

// SIZE AND POS
# define SCREEN_WIDTH 1100
# define SCREEN_HEIGHT 900
# define SCOREBOARD_HEIGHT 50
# define SCOREBOARD_WIDTH SCREEN_WIDTH
# define ACTIONS_HEIGHT 50
# define ACTIONS_WIDTH SCREEN_WIDTH
# define GRID_HEIGHT (SCREEN_HEIGHT - SCOREBOARD_HEIGHT)
# define GRID_WIDTH SCREEN_WIDTH
# define SCOREBOARD_POS_X 0
# define SCOREBOARD_POS_Y 0
# define ACTIONS_POS_X 0
# define ACTIONS_POS_Y SCOREBOARD_HEIGHT
# define GRID_POS_X 0
# define GRID_POS_Y (SCOREBOARD_HEIGHT + ACTIONS_HEIGHT)
# define GRID_COLS 25
# define GRID_ROWS 20
# define CELL_WIDTH GRID_WIDTH / GRID_COLS
# define CELL_HEIGHT GRID_HEIGHT / GRID_ROWS

// ITEMS
# define INVENTORY_SIZE 2
# define LIFE_MAX 3
# define BASE_SPEED 1.0f
# define SCALE_SPEED 2.7f

// A DEFINIR
# define APPLE_GENERATION_TIME 2000
# define OBJECT_GENERATION_TIME 10000
# define SNAKE_MOVE_TIME 400
# define CONTAINER_MARGING 1000
# define SNAKE_SPEED_TIME 650

# define NB_COLORS 3
# define NB_TILES 8
# define NB_OBSTACLES 12
# define NB_APPLES 3
# define NB_SNAKE_STATES 2
# define NB_ORIENTATIONS 4
# define NB_BONUS 6
# define SNAKES_ANIMATION_TIME 2000

# define SPRITE_WIDTH 16
# define SPRITE_HEIGHT 16

# define NB_APPLE_SPEED 5

#endif
