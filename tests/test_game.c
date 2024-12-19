#include <stdio.h>
#include "game.h"
#include "player.h"
#include "tests.h"

/*Fonction qui test update_gametick*/
void test_update_gametick(void)
{
	int	assert_file = 1;
	t_gametick	gametick;
	int speed1 = 1;
	int speed2 = 1;

	SDL_Init(SDL_INIT_EVERYTHING);
	init_gametick(&gametick);
	update_gametick(&gametick, speed1, speed2);
	
	assert(gametick.elapsed_time > 0);
	assert(gametick.apple_cooldown < APPLE_GENERATION_TIME);
	assert(gametick.object_cooldown < OBJECT_GENERATION_TIME);
	assert(gametick.snake_1_cooldown < SNAKE_MOVE_TIME);
	assert(gametick.snake_2_cooldown < SNAKE_MOVE_TIME);

	SDL_Quit();
	printf( __FILE__ " / update_gametick() %s\033[0m\n", assert_file ? "\033[32m[OK]" : "\033[31m[KO]");
}

void test_init_gametick(void)
{
	int	assert_file = 1;
	t_gametick	gametick;

	init_gametick(&gametick);

	assert(gametick.elapsed_time == 0);
	assert(gametick.apple_cooldown == APPLE_GENERATION_TIME);
	assert(gametick.object_cooldown == OBJECT_GENERATION_TIME);
	assert(gametick.snake_1_cooldown == SNAKE_MOVE_TIME);
	assert(gametick.snake_2_cooldown == SNAKE_MOVE_TIME);

	printf( __FILE__ " / init_gametick() %s\033[0m\n", assert_file ? "\033[32m[OK]" : "\033[31m[KO]");
}

void test_init_map(void)
{
	int	assert_file = 1;
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
			assert(grid.cells[x][y].bonus == BONUS_EMPTY);
			// A modifier pour les textures
			assert(grid.cells[x][y].texture == YELLOW);
			assert(grid.cells[x][y].is_pending == SDL_FALSE);
		}
	}

	free_all_game(grid);
	printf( __FILE__ " / init_map() %s\033[0m\n", assert_file ? "\033[32m[OK]" : "\033[31m[KO]");
}

