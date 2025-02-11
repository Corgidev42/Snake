#include "snake.h"

t_cell	*get_is_pending_cell(t_grid *grid)
{
	int x;
	int	y;
	t_cell *cell_is_pending;

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
	if (cell->obstacle == OBS_EMPTY
		&& cell->has_apple == SDL_FALSE
		&& cell->has_bomb == SDL_FALSE
		&& cell->has_snake == SDL_FALSE
		&& cell->bonus == BONUS_EMPTY)
		return (SDL_TRUE);
	return (SDL_FALSE);
}

SDL_bool	recursive_neighbourg_empty_cells(t_grid *grid, int x, int y, int r, int i)
{
	SDL_bool	result = SDL_TRUE;

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