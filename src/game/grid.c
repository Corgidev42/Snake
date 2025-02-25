#include "snake.h"

void	init_map(t_grid *grid)
{
	int	zone_limit = GRID_COLS / 3;
	int	yellow_obs_percent = 3;
	int	green_obs_percent = 9;
	int	blue_obs_percent = 6;
	int	x;
	int	y;

	y = 0;
	x = 0;
	grid->rect_pos.x = GRID_POS_X ; grid->rect_pos.y = GRID_POS_Y ; grid->rect_pos.w = GRID_WIDTH ; grid ->rect_pos.h = GRID_HEIGHT;

	grid->cells = malloc(sizeof(t_cell* ) * GRID_COLS);
	while (x < GRID_COLS)
	{
		grid->cells[x] = malloc(sizeof(t_cell) * GRID_COLS);
		y = 0;
		while (y < GRID_ROWS)
		{
			grid->cells[x][y].rand = rand();
			grid->cells[x][y].coords.x = x;
			grid->cells[x][y].coords.y = y;
			grid->cells[x][y].obstacle = OBS_EMPTY;
			if (y <= zone_limit)
				if (rand() % 100 < yellow_obs_percent)
					grid->cells[x][y].obstacle = WALL;
			if (y > zone_limit && y <= zone_limit * 2)
				if (rand() % 100 < green_obs_percent)
					grid->cells[x][y].obstacle = WALL;
			if (y > zone_limit * 2)
				if (rand() % 100 < blue_obs_percent)
					grid->cells[x][y].obstacle = WALL;
			grid->cells[x][y].has_apple = SDL_FALSE;
			grid->cells[x][y].has_bomb = SDL_FALSE;
			grid->cells[x][y].has_snake = SDL_FALSE;
			grid->cells[x][y].bonus = BONUS_EMPTY;
			grid->cells[x][y].texture = get_map_color(grid, x, y);
			grid->cells[x][y].is_pending = SDL_FALSE;
			y++;
		}
		x++;
	}
}

void	print_obstacles(t_grid grid)
{
	int	x;
	int	y;
	SDL_Rect cell_rect = {GRID_POS_X, GRID_POS_Y, CELL_WIDTH, CELL_HEIGHT};

	x = 0;
	while (x < GRID_COLS)
	{
		y = 0;
		cell_rect.y = GRID_POS_Y;
		while (y < GRID_ROWS)
		{
			if (grid.cells[x][y].obstacle == SDL_TRUE)
			{
				cell_rect.y -= CELL_HEIGHT;
				cell_rect.h += CELL_HEIGHT;
				SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.obstacle[grid.cells[x][y].texture][grid.cells[x][y].rand % 12], &cell_rect);
				cell_rect.y += CELL_HEIGHT;
				cell_rect.h -= CELL_HEIGHT;
			}
			cell_rect.y += CELL_HEIGHT;
			y++;
		}
		cell_rect.x += CELL_WIDTH;
		x++;
	}
}

void	print_grid(t_grid grid)
{
	int	x;
	int	y;
	SDL_Rect cell_rect = {GRID_POS_X, GRID_POS_Y, CELL_WIDTH, CELL_HEIGHT};

	x = 0;
	while (x < GRID_COLS)
	{
		y = 0;
		cell_rect.y = GRID_POS_Y;
		while (y < GRID_ROWS)
		{
			int is_light;
			if (grid.cells[x][y].texture == YELLOW)
				is_light = App.seed.is_yellow_light;
			else if (grid.cells[x][y].texture == GREEN)
				is_light = App.seed.is_green_light;
			else
				is_light = App.seed.is_blue_light;
			SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.tile[grid.cells[x][y].texture][(is_light ? 0 : 4) + (grid.cells[x][y].rand % 4)], &cell_rect);

			if (grid.cells[x][y].has_apple == SDL_TRUE)
				SDL_RenderCopy(App.renderer, App.spritesheet_texture, &App.texture_rects.apple[grid.cells[x][y].rand % 3], &cell_rect);
			if (grid.cells[x][y].has_bomb == SDL_TRUE)
				SDL_RenderCopy(App.renderer, App.texture_bomb.a3, &App.texture_bomb.r, &cell_rect);

			cell_rect.y += CELL_HEIGHT;
			y++;
		}
		cell_rect.x += CELL_WIDTH;
		x++;
	}
}

void	print_is_pending(t_grid grid, int object_cooldown)
{
	SDL_Rect	cell_rect = {GRID_POS_X, GRID_POS_Y, CELL_WIDTH, CELL_HEIGHT};
	t_cell		*is_pending_cell;

	is_pending_cell = get_is_pending_cell(&grid);
	if (!is_pending_cell)
		return ;
	cell_rect.x = GRID_POS_X + CELL_WIDTH * is_pending_cell->coords.x;
	cell_rect.y = GRID_POS_Y + CELL_HEIGHT * is_pending_cell->coords.y;
	render_text(App.renderer, ft_itoa((object_cooldown / 1000) + 1), cell_rect, App.font, (SDL_Color){255, 255, 255, 255});
}
