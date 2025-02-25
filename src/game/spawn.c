#include "snake.h"

t_cell	*get_rand_empty_cell(t_grid *grid, int r)
{
	int	x;
	int	y;
	int	i;
	int	nb_iter = 0;

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

void	generate_apple(t_grid *grid, int *apple_cooldown)
{
	t_cell *cell;
	if (*apple_cooldown > 0)
		return;
	if (*apple_cooldown <= 0)
	{
		cell = get_rand_empty_cell(grid, 0);
		cell->has_apple = SDL_TRUE;
		*apple_cooldown += APPLE_GENERATION_TIME;
	}
}

t_bonus	get_random_bonus(void)
{
	int	random = rand() % App.nb_bonus;

	if (App.available_bonus[random] == LIFE_UP)
	{
		if (rand() % 10 == 0)
			return LIFE_UP;
		return get_random_bonus();
	}
	return App.available_bonus[random];
}

void	generate_object(t_grid *grid, int *object_cooldown)
{
	t_cell	*cell;
	int		hot;
	if (*object_cooldown > 0)
		return;
	if (*object_cooldown <= 0)
	{
		if((cell = get_is_pending_cell(grid)))
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

void	spawn_snake(t_grid *grid, t_user_data *player)
{
	t_snake_part	*head_snake = player->head_snake;
	t_cell			*cell;

	if (!head_snake)
	{
		head_snake = malloc(sizeof(t_snake_part));
		if (!head_snake)
			SDL_ExitWithError("malloc head_snake");
		player->head_snake = head_snake;
	}
	int	i = 4;
	cell = get_rand_empty_cell(grid, i);
	while (!cell)
		cell = get_rand_empty_cell(grid, --i);
	player->head_snake->snake_state = NORMAL;
	player->speed = BASE_SPEED;
	head_snake->coords.x = cell->coords.x;
	head_snake->coords.y = cell->coords.y;
	head_snake->orientation = rand() % 4;
	player->orientation_snake = head_snake->orientation;
	head_snake->next = NULL;
	add_behind_snake_part(head_snake);
	cell->has_snake = SDL_TRUE;
	grid->cells[head_snake->next->coords.x][head_snake->next->coords.y].has_snake = SDL_TRUE;
}
