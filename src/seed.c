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

int	get_map_color(t_cell *cell)
{
	int zone = GRID_COLS / 3;
	int smooth = App.seed.smooth;

	if (cell->coords.x < zone - (App.seed.smooth + 1))
		return (GREEN);
	else if (cell->coords.x >= zone - (App.seed.smooth + 1) && cell->coords.x < zone + (App.seed.smooth + 1))
		return (cell->rand % 2 == 0 ? YELLOW : GREEN);
	else if (cell->coords.x < zone * 2 - (App.seed.smooth + 1))
		return (YELLOW);
	else if (cell->coords.x >= zone * 2 - (App.seed.smooth + 1) && cell->coords.x < zone * 2 + (App.seed.smooth + 1))
		return (cell->rand % 2 == 0 ? YELLOW : BLUE);
	else
		return (BLUE);
}

int	get_map_tile(int x, int y)
{
	int	hash = seed_hash(x, y);
	return (hash % 4);
}