#ifndef STRUCT_H
# define STRUCT_H

# include "snake.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>

typedef enum e_bonus
{
	BONUS_EMPTY,
	LIFE_UP,
	TP, // permet de passer de l'autre cote de la map
	STAR, // rend invincible ( annule tout effet negatif)
	MISSILE,
	SLOW,
	POISON //DOT
}						t_bonus;

typedef enum e_obstacle
{
	OBS_EMPTY,
	WALL,
	TREE,
	ROCK
}						t_obstable;

typedef enum e_color
{
	YELLOW,
	BLUE,
	GREEN
}			t_color;

typedef enum e_orientation
{
	LEFT,
	UP,
	RIGHT,
	DOWN
}			t_orientation;

typedef enum e_snake_state
{
	NORMAL,
	BONKED,
	DEAD
}			t_snake_state;

typedef struct	s_texture_rects
{
	SDL_Rect	tile[NB_COLORS][8];
	SDL_Rect	obstacle[NB_COLORS][12];
	SDL_Rect	snake_body[NB_COLORS][10];
	SDL_Rect	snake_head[NB_COLORS][NB_SNAKE_STATES][NB_ORIENTATIONS][8];
	SDL_Rect	apple[3];
}				t_texture_rects;

typedef struct s_app
{
	SDL_bool			running;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	TTF_Font			*font;
	SDL_Texture			*spritesheet_texture;
	t_texture_rects		texture_rects;
}						t_app;

typedef struct s_coords
{
	int					x;
	int					y;
}						t_coords;

typedef struct s_snake_part
{
	t_coords			coords;
	int					orientation;
	int					speed;
	t_color				skin;
	struct s_snake_part	*next;
}						t_snake_part;

typedef struct s_gametick
{
	int					elapsed_time;
	int					apple_cooldown;
	int					snake_1_cooldown;
	int					snake_2_cooldown;
	int					object_cooldown;
}						t_gametick;

typedef struct s_cell
{
	t_coords			coords;
	t_obstable			obstacle;
	SDL_bool			has_apple;
	SDL_bool			has_bomb;
	t_bonus				bonus;
	t_color				texture;
	SDL_bool			is_pending;
}						t_cell;

typedef struct s_grid
{
	SDL_Rect			rect_pos;
	t_cell				**cells;
}						t_grid;

typedef struct s_user_data
{
	int					id;
	SDL_bool			is_ready;
	int					score;
	int					life;
	t_bonus				inventory[INVENTORY_SIZE];
	t_snake_part		*head_snake;
}						t_user_data;

#endif
