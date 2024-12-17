#include <assert.h>
#include <stdio.h>
#include "game.h"
#include "player.h"

void test_init_map(void)
{
	t_grid grid;
	init_map(&grid);
	// Check grid dimensions
	assert(grid.rect_pos.x == GRID_POS_X);
	assert(grid.rect_pos.y == GRID_POS_Y);
	assert(grid.rect_pos.w == GRID_WIDTH);
	assert(grid.rect_pos.h == GRID_HEIGHT);

	// Check grid cells initialization
	for (int x = 0; x < GRID_COLS; x++)
	{
		for (int y = 0; y < GRID_ROWS; y++)
		{
			// printf("%d\n", grid.cells[x][y].coords.x);
			// printf("%d\n", x);
			assert(grid.cells[x][y].coords.x == x);
			assert(grid.cells[x][y].coords.y == y);
			if (x == 0 || y == 0 || x == GRID_COLS - 1 || y == GRID_ROWS - 1)
				assert(grid.cells[x][y].obstacle == 1);
			else
				assert(grid.cells[x][y].obstacle == 0);
			assert(grid.cells[x][y].has_apple == SDL_FALSE);
			assert(grid.cells[x][y].has_bomb == SDL_FALSE);
			assert(grid.cells[x][y].bonus == EMPTY);
			assert(grid.cells[x][y].texture == EMPTY);
			assert(grid.cells[x][y].is_pending == SDL_FALSE);
		}
	}

	free_all_game(grid);
	printf(__FILE__ " / test_init_map() \033[32m[OK]\033[30m\n");
}

