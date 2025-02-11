#include "snake.h"

int	seed_hash(int x, int y)
{
	int seed_number = App.seed.number;
	int hash;
	int result = 0;

	hash = (seed_number * x + seed_number * y) % 10000;
	printf("hash = %d\n", hash);
	result += App.seed.pi_decimals[hash] - '0';
	result *= 10;
	result += App.seed.pi_decimals[hash + 1] - '0';
	result *= 10;
	result += App.seed.pi_decimals[hash + 2] - '0';
	return (abs(result));
}

int	get_map_color(t_grid *grid, int x, int y)
{
	int zone = GRID_COLS / 3;
	int is_in_zone = 0;
	int smooth = App.seed.smooth + 1;

	t_cell *current_cell = &grid->cells[x][y];
	t_cell *left_cell = NULL;
	if (x > 0)
		left_cell = &grid->cells[x - 1][y];

	if ((x >= zone - smooth && x < zone + smooth)
		|| (x >= zone * 2 - smooth && x < zone * 2 + smooth))
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
}

int	get_map_tile(int x, int y)
{
	int	hash = seed_hash(x, y);
	return (hash % 4);
}