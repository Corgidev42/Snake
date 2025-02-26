#ifndef STRUCT_H
# define STRUCT_H

# include "snake_together.h"

typedef enum e_bonus
{
	BONUS_EMPTY,
	LIFE_UP,
	TP,   // permet de passer de l'autre cote de la map
	STAR, // rend invincible ( annule tout effet negatif)
	SLOW,
	MISSILE, // V3
	MINE     // V3
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
	GREEN,
	BLUE
}						t_color;

typedef enum e_orientation
{
	UP,
	LEFT,
	DOWN,
	RIGHT
}						t_orientation;

typedef enum e_snake_state
{
	NORMAL,
	BONKED,
	DEAD
}						t_snake_state;

typedef struct s_texture_rects
{
	SDL_Rect			tile[NB_COLORS][NB_TILES];
	SDL_Rect			obstacle[NB_COLORS][NB_OBSTACLES];
	SDL_Rect			snake_body[NB_COLORS][10];
	SDL_Rect			snake_head[NB_COLORS][NB_SNAKE_STATES][NB_ORIENTATIONS][8];
	SDL_Rect			apple[NB_APPLES];
}						t_texture_rects;

typedef struct s_texture_bomb
{
	SDL_Rect			r;
	SDL_Texture			*a1;
	SDL_Texture			*a2;
	SDL_Texture			*a3;
}						t_texture_bomb;

typedef struct s_texture_bonus
{
	SDL_Rect			r;
	SDL_Texture			*life_up;
	SDL_Texture			*tp;
	SDL_Texture			*star;
	SDL_Texture			*slow;
}						t_texture_bonus;

typedef struct s_seed
{
	int					number;
	char				*pi_decimals;
	SDL_bool			is_yellow_light;
	SDL_bool			is_green_light;
	SDL_bool			is_blue_light;
	SDL_bool			smooth;
	int					tree_percent;
	int					rock_percent;
}						t_seed;

typedef struct s_app
{
	t_seed				seed;
	SDL_bool			running;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	TTF_Font			*font;
	SDL_Texture			*spritesheet_texture;
	t_texture_bomb		texture_bomb;
	t_texture_bonus		texture_bonus;
	t_texture_rects		texture_rects;
	SDL_Texture			*texture_cross;
	SDL_Texture			*texture_crown;
	int					available_bonus[NB_BONUS];
	int					nb_bonus;
}						t_app;

typedef struct s_coords
{
	int					x;
	int					y;
}						t_coords;

typedef struct s_snake_part
{
	t_coords			coords;
	t_orientation		orientation;
	t_color				skin;
	struct s_snake_part	*next;
	t_snake_state		snake_state;
}						t_snake_part;

typedef struct s_gametick
{
	int					elapsed_time;
	int					apple_cooldown;
	int					snakes_animation;

	int					snake_1_cooldown;
	int					snake_1_speed_cooldown;
	int					snake_1_star_cooldown;
	int					snake_1_slow_cooldown;
	int					snake_1_died_cooldown;

	int					snake_2_speed_cooldown;
	int					snake_2_cooldown;
	int					snake_2_star_cooldown;
	int					snake_2_slow_cooldown;
	int					snake_2_died_cooldown;

	int					object_cooldown;

	int					timer;
}						t_gametick;

typedef struct s_cell
{
	int					rand;
	t_coords			coords;
	t_obstable			obstacle;
	SDL_bool			has_apple;
	SDL_bool			has_bomb;
	SDL_bool			has_snake;
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
	SDL_bool			is_speed;
	SDL_bool			is_star;
	SDL_bool			is_slow;
	float				speed;
	int					nb_apple_speed;
	int					max_snake_size;
	t_bonus				inventory[INVENTORY_SIZE];
	t_snake_part		*head_snake;
	t_orientation		orientation_snake;
	Uint32				bonked_start_time;
	Uint32				last_bonk_removal;
}						t_user_data;

#endif
