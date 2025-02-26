#include "snake_together.h"

// Module Game Logic

// Les fonctions qui gèrent les collisions et interactions liées aux joueurs (inventaire, bonus, vitesse…).

// ------- Gestion des collisions et interactions -------
void	do_collision(t_grid *grid, t_user_data *player1, t_user_data *player2)
{
	kill_collision(grid, player1, player2); /* mur, bombe,
		collision entre snake [tete contre tete, tete apres tete,
		tete contre corps]*/
	if (player1->life == 0 || player2->life == 0)
	{
		printf("Player %d won !!!\n", player1->life ? 1 : 2);
		return ;
	}
	score_collision(grid, player1, player2); // pomme, bonus
}

void	kill_collision(t_grid *grid, t_user_data *player1, t_user_data *player2)
{
	t_snake_part	*current1;
	t_snake_part	*current2;

	current1 = player1->head_snake;
	current2 = player2->head_snake;
	if (current1->coords.x < 0 || current1->coords.x >= GRID_COLS
		|| current1->coords.y < 0 || current1->coords.y >= GRID_ROWS)
		colls_to_bonk(grid, player1);
	if (current2->coords.x < 0 || current2->coords.x >= GRID_COLS
		|| current2->coords.y < 0 || current2->coords.y >= GRID_ROWS)
		colls_to_bonk(grid, player2);
	if (are_snakes_facing(current1, current2))
	{
		if ((current1->coords.x == current2->coords.x
				&& current1->coords.y == current2->coords.y)
			|| ((current1->coords.x == current2->next->coords.x
					&& current1->coords.y == current2->next->coords.y)
				&& (current2->coords.x == current1->next->coords.x
					&& current2->coords.y == current1->next->coords.y)))
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
		grid->cells[current1->coords.x][current1->coords.y].has_bomb = SDL_FALSE;
		colls_to_bonk(grid, player1);
	}
	if (grid->cells[current2->coords.x][current2->coords.y].obstacle == SDL_TRUE
		|| grid->cells[current2->coords.x][current2->coords.y].has_bomb == SDL_TRUE
		|| has_snake_in_coords(player1->head_snake, current2->coords)
		|| has_snake_tail_in_coords(player2->head_snake, current2->coords))
	{
		grid->cells[current2->coords.x][current2->coords.y].has_bomb = SDL_FALSE;
		colls_to_bonk(grid, player2);
	}
}

void	score_collision(t_grid *grid, t_user_data *player1,
		t_user_data *player2)
{
	t_snake_part	*current1;
	t_snake_part	*current2;

	current1 = player1->head_snake;
	current2 = player2->head_snake;
	if (grid->cells[current1->coords.x][current1->coords.y].bonus != BONUS_EMPTY)
	{
		add_inventory_bonus(player1,
			grid->cells[current1->coords.x][current1->coords.y].bonus);
		grid->cells[current1->coords.x][current1->coords.y].bonus = BONUS_EMPTY;
	}
	if (grid->cells[current2->coords.x][current2->coords.y].bonus != BONUS_EMPTY)
	{
		add_inventory_bonus(player2,
			grid->cells[current2->coords.x][current2->coords.y].bonus);
		grid->cells[current2->coords.x][current2->coords.y].bonus = BONUS_EMPTY;
	}
	if (grid->cells[current1->coords.x][current1->coords.y].has_apple == SDL_TRUE)
	{
		player1->score += 1;
		if (current1->coords.x >= 0 && current1->coords.x < GRID_COLS
			&& current1->coords.y >= 0 && current1->coords.y < GRID_ROWS)
			grid->cells[current1->coords.x][current1->coords.y].has_apple = SDL_FALSE;
		add_behind_snake_part(player1, SDL_TRUE);
		if (!player1->is_speed && NB_APPLE_SPEED > player1->nb_apple_speed)
			player1->nb_apple_speed += 1;
	}
	if (grid->cells[current2->coords.x][current2->coords.y].has_apple == SDL_TRUE)
	{
		player2->score += 1;
		if (current2->coords.x >= 0 && current2->coords.x < GRID_COLS
			&& current2->coords.y >= 0 && current2->coords.y < GRID_ROWS)
			grid->cells[current2->coords.x][current2->coords.y].has_apple = SDL_FALSE;
		add_behind_snake_part(player2, SDL_TRUE);
		if (!player2->is_speed && NB_APPLE_SPEED > player2->nb_apple_speed)
			player2->nb_apple_speed += 1;
	}
}

// ------- Fonctions de conditions  -------

SDL_bool	has_snake_in_coords(t_snake_part *head_snake, t_coords coords)
{
	t_snake_part	*current;

	current = head_snake;
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
	t_snake_part	*current;

	current = head_snake->next;
	while (current)
	{
		if (current->coords.x == coords.x && current->coords.y == coords.y)
			return (SDL_TRUE);
		current = current->next;
	}
	return (SDL_FALSE);
}

SDL_bool	are_snakes_facing(t_snake_part *head_snake_1,
		t_snake_part *head_snake_2)
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
