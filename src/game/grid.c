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
			if (grid.cells[x][y].bonus != BONUS_EMPTY)
			{
				SDL_Texture *bonus_texture = NULL;
				switch (grid.cells[x][y].bonus)
				{
					case LIFE_UP:
						bonus_texture = App.texture_bonus.life_up;
						break;
					case STAR:
						bonus_texture = App.texture_bonus.star;
						break;
					case SLOW:
						bonus_texture = App.texture_bonus.slow;
						break;
					case TP:
						bonus_texture = App.texture_bonus.tp;
						break;
					default:
						break;
				}
				SDL_RenderCopy(App.renderer, bonus_texture, NULL, &cell_rect);
			}

			cell_rect.y += CELL_HEIGHT;
			y++;
		}
		cell_rect.x += CELL_WIDTH;
		x++;
	}
}

void	print_is_pending(t_grid grid, int object_cooldown)
{
	SDL_Rect	cell_rect;
	SDL_Rect	text_rect;
	t_cell		*is_pending_cell;
	char		*cooldown_text;
	int			text_width;
	int			text_height;

	// Récupère la cellule en attente
	is_pending_cell = get_is_pending_cell(&grid);
	if (!is_pending_cell)
		return ;

	// Définition de la position de la cellule
	cell_rect.x = GRID_POS_X + CELL_WIDTH * is_pending_cell->coords.x;
	cell_rect.y = GRID_POS_Y + CELL_HEIGHT * is_pending_cell->coords.y;
	cell_rect.w = CELL_WIDTH;
	cell_rect.h = CELL_HEIGHT;

	// Convertit le cooldown en texte
	cooldown_text = ft_itoa((object_cooldown / 1000) + 1);

	// Calcule la taille du texte
	text_width = get_text_width(cooldown_text, App.font) * 2;
	text_height = get_text_height(cooldown_text, App.font) * 2;

	// Centre le texte dans la cellule
	text_rect.x = cell_rect.x + (cell_rect.w - text_width) / 2;
	text_rect.y = cell_rect.y + (cell_rect.h - text_height) / 2;
	text_rect.w = text_width;
	text_rect.h = text_height;

	// Affiche le texte centré
	render_text(App.renderer, cooldown_text, text_rect, App.font, (SDL_Color){255, 255, 255, 255});

	free(cooldown_text);
}
