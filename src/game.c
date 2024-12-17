#include "app.h"
#include "defs.h"
#include "structs.h"

static	free_all_game(t_grid grid)
{
	int	x;

	x = 0;
	while (x < GRID_COLS)
	{
		free(grid.cells[x]);
		x++;
	}
	free(grid.cells);
}
void	init_map(t_grid *grid)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	grid->rect_pos.x = GRID_POS_X ; grid->rect_pos.y = GRID_POS_Y ; grid->rect_pos.w = GRID_WIDTH ; grid ->rect_pos.h = GRID_HEIGHT;

	grid->cells = malloc(sizeof(t_cell* ) * GRID_COLS);
	while (x < GRID_COLS)
	{
		grid->cells[y] = malloc(sizeof(t_cell) * GRID_COLS);
		while (y < GRID_ROWS)
		{
			grid->cells[x][y].coords.x = x;
			grid->cells[x][y].coords.y = y;
			if (x == 0 || y == 0 || x == GRID_COLS - 1 || y == GRID_ROWS - 1)
				grid->cells[x][y].obstacle = 1;
			else
				grid->cells[x][y].obstacle = 0;
			grid->cells[x][y].has_apple = SDL_FALSE;
			grid->cells[x][y].has_bomb = SDL_FALSE;
			grid->cells[x][y].bonus = EMPTY;
			grid->cells[x][y].texture = EMPTY;
			grid->cells[x][y].is_pending = SDL_FALSE;
			y++;
		}
		x++;
	}
}

void	game_window(t_user_data player1, t_user_data player2)
{
	t_grid		grid;
	t_gametick	gametick;
	SDL_Rect	scoreboard_rect_pos;

	scoreboard_rect_pos.x = SCOREBOARD_POS_X; scoreboard_rect_pos.y = SCOREBOARD_POS_Y; scoreboard_rect_pos.h = SCREEN_HEIGHT - (CONTAINER_MARGING * 2) ; scoreboard_rect_pos.w = SCREEN_WIDTH - (CONTAINER_MARGING * 2);
	init_map(&grid);
	spawn_snake(grid, &player1.head_snake);
	spawn_snake(grid, &player2.head_snake);
	init_gametick(&gametick);
	while (App.running && player1.life && player2.life)
	{
		update_gametick(&gametick);
		SDL_RenderClear(App.renderer);

		do_input(&player1, &player2);

		move_snake(&gametick.snake_1_cooldown, &player1.head_snake);
		move_snake(&gametick.snake_2_cooldown, &player2.head_snake);

		do_collision(grid, &player1, &player2);

		generate_apple(&grid, &gametick.apple_cooldown);
		generate_object(&grid,&gametick.object_cooldown);

		print_grid(grid);
		print_snake(grid, player1.head_snake);
		print_snake(grid, player2.head_snake);

		print_scoreboard(scoreboard_rect_pos, player1, player2);

		SDL_RenderPresent(App.renderer);
	}
	free_all_game(grid);
}
