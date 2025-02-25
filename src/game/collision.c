#include "snake.h"

void	kill_snake(t_grid *grid, t_user_data *player)
{
	t_snake_part	*current = player->head_snake->next;
	t_snake_part	*prev;

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

SDL_bool	has_snake_in_coords(t_snake_part *head_snake, t_coords coords)
{
	t_snake_part	*current = head_snake;

	while (current)
	{
		if (current->coords.x == coords.x && current->coords.y == coords.y)
			return (SDL_TRUE);
		current = current->next;
	}
	return (SDL_FALSE);
}

SDL_bool	has_snake_tail_in_coords(t_snake_part *head_snake, t_coords coords)
{
	t_snake_part	*current = head_snake->next;

	while (current)
	{
		if (current->coords.x == coords.x && current->coords.y == coords.y)
			return (SDL_TRUE);
		current = current->next;
	}
	return (SDL_FALSE);
}

SDL_bool are_snakes_facing(t_snake_part *head_snake_1, t_snake_part *head_snake_2)
{
	if (head_snake_1->orientation == UP && head_snake_2->orientation == DOWN)
		return (SDL_TRUE);
	if (head_snake_1->orientation == DOWN && head_snake_2->orientation == UP)
		return (SDL_TRUE);
	if (head_snake_1->orientation == LEFT && head_snake_2->orientation == RIGHT)
		return (SDL_TRUE);
	if (head_snake_1->orientation == RIGHT && head_snake_2->orientation == LEFT)
		return (SDL_TRUE);
	return (SDL_FALSE);
}

void	remove_snake_head_parts(t_grid *grid, t_user_data *player, int nb_removes)
{
	t_snake_part	*current = player->head_snake;
	t_snake_part	*prev;

	while (current && nb_removes > 0)
	{
		prev = current;
		if (prev->next == NULL)
		{
			current = prev;
			break;
		}
		current = prev->next;
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

void	kill_collision(t_grid *grid, t_user_data *player1, t_user_data *player2)
{
	t_snake_part	*current1 = player1->head_snake;
	t_snake_part	*current2 = player2->head_snake;

	if (current1->coords.x < 0 || current1->coords.x >= GRID_COLS
		|| current1->coords.y < 0 || current1->coords.y >= GRID_ROWS)
	{
		player1->life -= 1;
		kill_snake(grid, player1);
		if (player1->life == 0)
			return ;
		spawn_snake(grid, player1);
	}
	if (current2->coords.x < 0 || current2->coords.x >= GRID_COLS
		|| current2->coords.y < 0 || current2->coords.y >= GRID_ROWS)
	{
		player2->life -= 1;
		kill_snake(grid, player2);
		if (player2->life == 0)
			return ;
		spawn_snake(grid, player2);
	}

	if (are_snakes_facing(current1, current2))
	{
		if ((current1->coords.x == current2->coords.x && current1->coords.y == current2->coords.y)
			|| ((current1->coords.x == current2->next->coords.x && current1->coords.y == current2->next->coords.y)
			&& (current2->coords.x == current1->next->coords.x && current2->coords.y == current1->next->coords.y)))
		{
			remove_snake_head_parts(grid, player1, 3);
			remove_snake_head_parts(grid, player2, 3);
		}
	}

	current1 = player1->head_snake;
	current2 = player2->head_snake;

	if (grid->cells[current1->coords.x][current1->coords.y].obstacle == SDL_TRUE
		|| grid->cells[current1->coords.x][current1->coords.y].has_bomb == SDL_TRUE
		|| has_snake_tail_in_coords(player1->head_snake, current1->coords)
		|| has_snake_in_coords(player2->head_snake, current1->coords))
	{
		player1->life -= 1;
		kill_snake(grid, player1);
		if (player1->life == 0)
			return ;
		spawn_snake(grid, player1);
	}
	if (grid->cells[current2->coords.x][current2->coords.y].obstacle == SDL_TRUE
		|| grid->cells[current2->coords.x][current2->coords.y].has_bomb == SDL_TRUE
		|| has_snake_in_coords(player1->head_snake, current2->coords)
		|| has_snake_tail_in_coords(player2->head_snake, current2->coords))
	{
		player2->life -= 1;
		kill_snake(grid, player2);
		if (player2->life == 0)
			return ;
		spawn_snake(grid, player2);
	}
}

void	score_collision(t_grid *grid, t_user_data *player1, t_user_data *player2)
{
	t_snake_part	*current1 = player1->head_snake;
	t_snake_part	*current2 = player2->head_snake;

	if (grid->cells[current1->coords.x][current1->coords.y].has_apple == SDL_TRUE)
	{
		player1->score += 1;
		if (current1->coords.x >= 0 && current1->coords.x < GRID_COLS
			&& current1->coords.y >= 0 && current1->coords.y < GRID_ROWS)
		grid->cells[current1->coords.x][current1->coords.y].has_apple = SDL_FALSE;
		add_behind_snake_part(current1);
		if (!player1->is_speed && NB_APPLE_SPEED > player1->nb_apple_speed)
			player1->nb_apple_speed += 1;
	}
	if (grid->cells[current2->coords.x][current2->coords.y].has_apple == SDL_TRUE)
	{
		player2->score += 1;
		if (current2->coords.x >= 0 && current2->coords.x < GRID_COLS
			&& current2->coords.y >= 0 && current2->coords.y < GRID_ROWS)
		grid->cells[current2->coords.x][current2->coords.y].has_apple = SDL_FALSE;
		add_behind_snake_part(current2);
		if (!player2->is_speed && NB_APPLE_SPEED > player2->nb_apple_speed)
			player2->nb_apple_speed += 1;
	}
}

void	do_collision(t_grid *grid, t_user_data *player1, t_user_data *player2)
{
	kill_collision(grid, player1, player2); //mur, bombe, collision entre snake [tete contre tete, tete apres tete, tete contre corps]
	if (player1->life == 0 || player2->life == 0)
	{
		printf("Player %d won !!!\n", player1->life ? 1 : 2);
		return ;
	}
	score_collision(grid, player1, player2); // pomme, bonus
}
