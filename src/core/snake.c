#include "snake_together.h"

// Module Snake et Mouvements (snake) Regrouper ici tout ce qui touche à la représentation,	la manipulation et l’animation des serpents.

// ------- Fonctions de création et modification d’un serpent -------
void	spawn_snake(t_grid *grid, t_user_data *player)
{
	t_snake_part	*head_snake;
	t_cell			*cell;
	int				i;

	head_snake = player->head_snake;
	if (!head_snake)
	{
		head_snake = malloc(sizeof(t_snake_part));
		if (!head_snake)
			SDL_ExitWithError("malloc head_snake");
		player->head_snake = head_snake;
	}
	i = 4;
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

t_snake_part	*add_behind_snake_part(t_snake_part *head_snake)
{
	t_snake_part	*new_snake_part;
	t_snake_part	*current;

	new_snake_part = malloc(sizeof(t_snake_part));
	if (!new_snake_part)
		SDL_ExitWithError("malloc new_snake_part");
	new_snake_part->skin = head_snake->skin;
	new_snake_part->next = NULL;
	current = head_snake;
	while (current && current->next)
		current = current->next;
	new_snake_part->orientation = current->orientation;
	switch (current->orientation)
	{
	case UP:
		new_snake_part->coords.x = current->coords.x;
		new_snake_part->coords.y = current->coords.y + 1;
		break ;
	case DOWN:
		new_snake_part->coords.x = current->coords.x;
		new_snake_part->coords.y = current->coords.y - 1;
		break ;
	case LEFT:
		new_snake_part->coords.x = current->coords.x + 1;
		new_snake_part->coords.y = current->coords.y;
		break ;
	case RIGHT:
		new_snake_part->coords.x = current->coords.x - 1;
		new_snake_part->coords.y = current->coords.y;
		break ;
	default:
		break ;
	}
	current->next = new_snake_part;
	return (new_snake_part);
}

void	remove_behind_snake_part(t_grid *grid, t_user_data *player)
{
	t_snake_part	*current;
	t_snake_part	*prev;

	current = player->head_snake;
	prev = player->head_snake;
	while (current && current->next)
	{
		prev = current;
		current = current->next;
	}
	grid->cells[current->coords.x][current->coords.y].has_snake = SDL_FALSE;
	free(current);
	prev->next = NULL;
	if (!player->head_snake->next)
	{
		player->life -= 1;
		kill_snake(grid, player);
		if (player->life == 0)
			return ;
		spawn_snake(grid, player);
	}
}

void	remove_snake_head_parts(t_grid *grid, t_user_data *player,
		int nb_removes)
{
	t_snake_part	*current;
	t_snake_part	*prev;

	current = player->head_snake;
	while (current && nb_removes > 0)
	{
		prev = current;
		if (prev->next == NULL)
		{
			current = prev;
			break ;
		}
		current = prev->next;
		if (prev->coords.x >= 0 && prev->coords.x < GRID_COLS
			&& prev->coords.y >= 0 && prev->coords.y < GRID_ROWS)
			grid->cells[prev->coords.x][prev->coords.y].has_snake = SDL_FALSE;
		free(prev);
		nb_removes--;
	}
	player->head_snake = current;
	if (nb_removes > 0 || !player->head_snake->next)
	{
		player->life -= 1;
		kill_snake(grid, player);
		if (player->life == 0)
			return ;
		spawn_snake(grid, player);
	}
}

void	kill_snake(t_grid *grid, t_user_data *player)
{
	t_snake_part	*current;
	t_snake_part	*prev;

	current = player->head_snake->next;
	while (current)
	{
		prev = current;
		current = prev->next;
		if (prev->coords.x >= 0 && prev->coords.x < GRID_COLS
			&& prev->coords.y >= 0 && prev->coords.y < GRID_ROWS)
			grid->cells[prev->coords.x][prev->coords.y].has_snake = SDL_FALSE;
		free(prev);
	}
}

// ------- Mouvements et rotations -------

void	rotate_snake(t_user_data *player, t_orientation orientation)
{
	t_snake_part	*second;

	second = player->head_snake->next;
	if (second)
	{
		if (second->orientation == UP && orientation == DOWN)
			return ;
		if (second->orientation == DOWN && orientation == UP)
			return ;
		if (second->orientation == LEFT && orientation == RIGHT)
			return ;
		if (second->orientation == RIGHT && orientation == LEFT)
			return ;
	}
	player->orientation_snake = orientation;
}

void	move_snake(t_grid *grid, int *snake_cooldown, t_user_data *player)
{
	t_snake_part	*current;
	t_snake_part	*prev;

	prev = player->head_snake;
	current = player->head_snake;
	if (*snake_cooldown > 0)
		return ;
	if (*snake_cooldown <= 0)
	{
		while (current)
		{
			prev = current;
			current = prev->next;
			if (current->next == NULL)
			{
				if (current->coords.x > 0 && current->coords.x < GRID_COLS
					&& current->coords.y > 0 && current->coords.y < GRID_ROWS)
					grid->cells[current->coords.x][current->coords.y].has_snake = SDL_FALSE;
				current->next = player->head_snake;
				prev->next = NULL;
				current->coords.x = player->head_snake->coords.x;
				current->coords.y = player->head_snake->coords.y;
				current->orientation = player->orientation_snake;
				player->head_snake = current;
				break ;
			}
		}
		current = player->head_snake->next;
		switch (player->orientation_snake)
		{
		case LEFT:
			player->head_snake->coords.x -= 1;
			if (current)
				current->orientation = LEFT;
			break ;
		case RIGHT:
			player->head_snake->coords.x += 1;
			if (current)
				current->orientation = RIGHT;
			break ;
		case UP:
			player->head_snake->coords.y -= 1;
			if (current)
				current->orientation = UP;
			break ;
		case DOWN:
			player->head_snake->coords.y += 1;
			if (current)
				current->orientation = DOWN;
			break ;
		default:
			break ;
		}
		if ((player->inventory[0] == TP || player->inventory[1] == TP)
			&& (player->head_snake->coords.x < 0
				|| player->head_snake->coords.x >= GRID_COLS
				|| player->head_snake->coords.y < 0
				|| player->head_snake->coords.y >= GRID_ROWS))
		{
			if (player->head_snake->coords.x < 0)
				player->head_snake->coords.x = GRID_COLS - 1;
			else if (player->head_snake->coords.x >= GRID_COLS)
				player->head_snake->coords.x = 0;
			else if (player->head_snake->coords.y < 0)
				player->head_snake->coords.y = GRID_ROWS - 1;
			else if (player->head_snake->coords.y >= GRID_ROWS)
				player->head_snake->coords.y = 0;
			if (player->inventory[0] == TP)
				remove_bonus_slot(player, 0);
			else
				remove_bonus_slot(player, 1);
		}
		if (player->head_snake->coords.x >= 0
			&& player->head_snake->coords.x < GRID_COLS
			&& player->head_snake->coords.y >= 0
			&& player->head_snake->coords.y < GRID_ROWS)
			grid->cells[player->head_snake->coords.x][player->head_snake->coords.y].has_snake = SDL_TRUE;
		*snake_cooldown += SNAKE_MOVE_TIME;
	}
}

// ------- Fonctions utilitaire -------
int	get_size_snake(t_snake_part *head_snake)
{
	t_snake_part	*current;
	int				size;

	current = head_snake;
	size = 0;
	while (current)
	{
		size += 1;
		current = current->next;
	}
	return (size);
}
