#include "snake_together.h"

// Module de Gestion de la Grille (grid) Ici se regroupera tout ce qui concerne la création et la gestion de la grille du jeu.

// ------- Initialisation de la grille -------
void	init_map(t_grid *grid)
{
	int	zone_limit;
	int	yellow_obs_percent;
	int	green_obs_percent;
	int	blue_obs_percent;
	int	x;
	int	y;

	zone_limit = GRID_COLS / 3;
	yellow_obs_percent = 3;
	green_obs_percent = 9;
	blue_obs_percent = 6;
	y = 0;
	x = 0;
	grid->rect_pos.x = GRID_POS_X;
	grid->rect_pos.y = GRID_POS_Y;
	grid->rect_pos.w = GRID_WIDTH;
	grid->rect_pos.h = GRID_HEIGHT;
	grid->cells = malloc(sizeof(t_cell *) * GRID_COLS);
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

// ------- Fonctions d’accès et de recherche sur la grille -------
t_cell	*get_is_pending_cell(t_grid *grid)
{
	int		x;
	int		y;
	t_cell	*cell_is_pending;

	x = 0;
	while (x < GRID_COLS)
	{
		y = 0;
		while (y < GRID_ROWS)
		{
			if (grid->cells[x][y].is_pending == SDL_TRUE)
			{
				cell_is_pending = &grid->cells[x][y];
				return (cell_is_pending);
			}
			y++;
		}
		x++;
	}
	return (NULL);
}

SDL_bool	cell_is_empty(t_cell *cell)
{
	if (cell->obstacle == OBS_EMPTY && cell->has_apple == SDL_FALSE
		&& cell->has_bomb == SDL_FALSE && cell->has_snake == SDL_FALSE
		&& cell->bonus == BONUS_EMPTY)
		return (SDL_TRUE);
	return (SDL_FALSE);
}

// ------- Génération d'entité -------

void	generate_object(t_grid *grid, int *object_cooldown)
{
	t_cell	*cell;
	int		hot;

	if (*object_cooldown > 0)
		return ;
	if (*object_cooldown <= 0)
	{
		if ((cell = get_is_pending_cell(grid)))
		{
			hot = rand() % 2;
			if (hot || App.nb_bonus == 0)
				cell->has_bomb = SDL_TRUE;
			else
				cell->bonus = get_random_bonus();
			cell->is_pending = SDL_FALSE;
		}
		cell = get_rand_empty_cell(grid, 0);
		cell->is_pending = SDL_TRUE;
		*object_cooldown += OBJECT_GENERATION_TIME;
	}
}

void	generate_apple(t_grid *grid, int *apple_cooldown)
{
	t_cell	*cell;

	if (*apple_cooldown > 0)
		return ;
	if (*apple_cooldown <= 0)
	{
		cell = get_rand_empty_cell(grid, 0);
		cell->has_apple = SDL_TRUE;
		*apple_cooldown += APPLE_GENERATION_TIME;
	}
}

// ------- Les fonctions qui gèrent la grille, la sélection de cellules et la détermination de la couleur ou du type d’un élément de la carte. -------
t_cell	*get_rand_empty_cell(t_grid *grid, int r)
{
	int	x;
	int	y;
	int	i;
	int	nb_iter;

	nb_iter = 0;
	i = 0;
	while (SDL_TRUE && nb_iter++ < GRID_COLS * GRID_ROWS * 2)
	{
		x = rand() % GRID_COLS;
		y = rand() % GRID_ROWS;
		if (recursive_neighbourg_empty_cells(grid, x, y, r, 0))
			return (&grid->cells[x][y]);
	}
	return (NULL);
}

SDL_bool	recursive_neighbourg_empty_cells(t_grid *grid, int x, int y, int r,
		int i)
{
	SDL_bool	result;

	result = SDL_TRUE;
	if (x < 0 || x > GRID_COLS - 1 || y < 0 || y > GRID_ROWS - 1)
		return (SDL_FALSE);
	if (!cell_is_empty(&grid->cells[x][y]))
		return (SDL_FALSE);
	if (i < r)
	{
		if (!recursive_neighbourg_empty_cells(grid, x - 1, y, r, i + 1))
			result = SDL_FALSE;
		if (!recursive_neighbourg_empty_cells(grid, x + 1, y, r, i + 1))
			result = SDL_FALSE;
		if (!recursive_neighbourg_empty_cells(grid, x, y - 1, r, i + 1))
			result = SDL_FALSE;
		if (!recursive_neighbourg_empty_cells(grid, x, y + 1, r, i + 1))
			result = SDL_FALSE;
	}
	return (result);
}

int	get_map_color(t_grid *grid, int x, int y)
{
	int		zone;
	int		is_in_zone;
	int		smooth;
	t_cell	*current_cell;
	t_cell	*left_cell;

	zone = GRID_COLS / 3;
	is_in_zone = 0;
	smooth = App.seed.smooth + 1;
	current_cell = &grid->cells[x][y];
	left_cell = NULL;
	if (x > 0)
		left_cell = &grid->cells[x - 1][y];
	if ((x >= zone - smooth && x < zone + smooth) || (x >= zone * 2 - smooth
			&& x < zone * 2 + smooth))
		is_in_zone = 1;
	if (!is_in_zone)
	{
		if (x < zone - smooth)
			return (GREEN);
		else if (x < zone * 2 - smooth)
			return (YELLOW);
		else
			return (BLUE);
	}
	if (x >= zone - smooth && x < zone + smooth)
	{
		if (left_cell->texture == GREEN)
			return (rand() % 2 == 0 ? GREEN : YELLOW);
		return (YELLOW);
	}
	if (x >= zone * 2 - smooth && x < zone * 2 + smooth)
	{
		if (left_cell->texture == YELLOW)
			return (rand() % 2 == 0 ? YELLOW : BLUE);
		return (BLUE);
	}
	return (0);
}

int	get_map_tile(int x, int y)
{
	int	hash;

	hash = seed_hash(x, y);
	return (hash % 4);
}
