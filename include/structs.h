#ifndef STRUCTS_H
# define STRUCTS_H
# include "defs.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>

typedef enum e_skin
{
	EMPTY,
	YELLOW,
	BLUE,
	GREEN
}						t_skin;

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

typedef struct	t_texture_snake
{
	SDL_Texture		*body[10];
	SDL_Texture		*head[NB_SNAKE_STATES][NB_ORIENTATIONS][8];
}				t_texture_snake;

typedef struct	s_texture
{
	SDL_Texture		*tile[NB_COLORS][8];
	SDL_Texture		*obstacle[NB_COLORS][12];
	t_texture_snake	snake[NB_COLORS];
	SDL_Texture		*apple[3];
}				t_texture;

typedef struct s_app
{
	SDL_bool			running;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	TTF_Font			*font;
	t_texture_snake		textures;
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
	t_skin				skin;
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
	t_skin				texture;
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
