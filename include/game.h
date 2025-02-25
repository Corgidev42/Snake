#ifndef GAME_H
# define GAME_H

# include "snake.h"

void			do_collision(t_grid *grid, t_user_data *player1,
					t_user_data *player2);
void			generate_object(t_grid *grid, int *object_cooldown);
int				get_seed_number(int x, int y, int max);
void			move_snake(t_grid *grid, int *snake_cooldown,
					t_user_data *player);
SDL_bool		cell_is_empty(t_cell *cell);
SDL_bool		recursive_neighbourg_empty_cells(t_grid *grid, int x, int y,
					int r, int i);
t_cell			*get_rand_empty_cell(t_grid *grid, int r);
void			generate_apple(t_grid *grid, int *apple_cooldown);
void			spawn_snake(t_grid *grid, t_user_data *player);
void			print_grid(t_grid grid, t_gametick gametick);
t_snake_part	*add_behind_snake_part(t_snake_part *head_snake);
void			print_snake(t_grid grid, t_snake_part *head_snake,
					int snake_animation);
void			print_obstacles(t_grid grid);
void			do_input(t_user_data *player1, t_user_data *player2);
void			init_gametick(t_gametick *gametick);
void			update_gametick(t_gametick *gametick, int speed1, int speed2);
void			print_scoreboard(SDL_Rect rect_pos, t_user_data player1,
					t_user_data player2);
void			free_all_game(t_grid grid);
void			init_map(t_grid *grid);
void			game_window(t_user_data player1, t_user_data player2);
void			print_is_pending(t_grid grid, int object_cooldown);
void			rotate_snake(t_user_data *player, t_orientation orientation);
t_cell			*get_is_pending_cell(t_grid *grid);

#endif
