#include "snake_together.h"

// Module Game Logic

// Les fonctions qui gèrent les collisions et interactions liées aux joueurs (inventaire, bonus, vitesse…).

// ------- Gestion des collisions et interactions -------

void	do_collision(t_grid *grid, t_user_data *player1, t_user_data *player2, t_score_anim **score_anims)
{
	kill_collision(grid, player1, player2, score_anims); /* mur, bombe,
		collision entre snake [tete contre tete, tete apres tete,
		tete contre corps]*/
	if (player1->life == 0 || player2->life == 0)
	{
		printf("Player %d won !!!\n", player1->life ? 1 : 2);
		return ;
	}
	score_collision(grid, player1, player2, score_anims); // pomme, bonus
}

void	kill_collision(t_grid *grid, t_user_data *player1, t_user_data *player2, t_score_anim **score_anims)
{
	t_snake_part	*current1;
	t_snake_part	*current2;
	int				player1_life;
	int				player2_life;

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
			player1_life = player1->life;
			player2_life = player2->life;
			remove_snake_head_parts(grid, player1, 3);
			if (player1_life != player1->life)
			{
				add_snake_score_anim(score_anims, player2->head_snake, SCORE_KILL_SNAKE, player2->head_snake->skin);
				player2->score += SCORE_KILL_SNAKE;
			}
			remove_snake_head_parts(grid, player2, 3);
			if (player2_life != player2->life)
			{
				add_snake_score_anim(score_anims, player1->head_snake, SCORE_KILL_SNAKE, player1->head_snake->skin);
				player1->score += SCORE_KILL_SNAKE;
			}

		}
	}
	current1 = player1->head_snake;
	current2 = player2->head_snake;
	if (grid->cells[current1->coords.x][current1->coords.y].obstacle == SDL_TRUE
		|| grid->cells[current1->coords.x][current1->coords.y].has_bomb == SDL_TRUE
		|| has_snake_tail_in_coords(player1->head_snake, current1->coords))
	{
		grid->cells[current1->coords.x][current1->coords.y].has_bomb = SDL_FALSE;
		colls_to_bonk(grid, player1);
	}
	if (has_snake_in_coords(player2->head_snake, current1->coords))
	{
		colls_to_bonk(grid, player1);
		add_snake_score_anim(score_anims, player2->head_snake, SCORE_KILL_SNAKE, player2->head_snake->skin);
		player2->score += SCORE_KILL_SNAKE;
	}
	if (grid->cells[current2->coords.x][current2->coords.y].obstacle == SDL_TRUE
		|| grid->cells[current2->coords.x][current2->coords.y].has_bomb == SDL_TRUE
		|| has_snake_tail_in_coords(player2->head_snake, current2->coords))
	{
		grid->cells[current2->coords.x][current2->coords.y].has_bomb = SDL_FALSE;
		colls_to_bonk(grid, player2);
	}
	if (has_snake_in_coords(player1->head_snake, current2->coords))
	{
		colls_to_bonk(grid, player2);
		add_snake_score_anim(score_anims, player1->head_snake, SCORE_KILL_SNAKE, player1->head_snake->skin);
		player1->score += SCORE_KILL_SNAKE;
	}
}

void	score_collision(t_grid *grid, t_user_data *player1,
		t_user_data *player2, t_score_anim **score_anims)
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
		add_snake_score_anim(score_anims, player1->head_snake, SCORE_BONUS_EAT, player1->head_snake->skin);
		player1->score += SCORE_BONUS_EAT;
	}
	if (grid->cells[current2->coords.x][current2->coords.y].bonus != BONUS_EMPTY)
	{
		add_inventory_bonus(player2,
			grid->cells[current2->coords.x][current2->coords.y].bonus);
		grid->cells[current2->coords.x][current2->coords.y].bonus = BONUS_EMPTY;
		add_snake_score_anim(score_anims, player2->head_snake, SCORE_BONUS_EAT, player2->head_snake->skin);
		player2->score += SCORE_BONUS_EAT;
	}
	if (grid->cells[current1->coords.x][current1->coords.y].has_apple == SDL_TRUE)
	{
		player1->score += 1;
		if (current1->coords.x >= 0 && current1->coords.x < GRID_COLS
			&& current1->coords.y >= 0 && current1->coords.y < GRID_ROWS)
			grid->cells[current1->coords.x][current1->coords.y].has_apple = SDL_FALSE;
		add_behind_snake_part(player1, SDL_TRUE);
		if (NB_APPLE_SPEED > player1->nb_apple_speed)
			player1->nb_apple_speed += 1;
		add_snake_score_anim(score_anims, player1->head_snake, SCORE_APPLE_EAT, player1->head_snake->skin);
	}
	if (grid->cells[current2->coords.x][current2->coords.y].has_apple == SDL_TRUE)
	{
		player2->score += 1;
		if (current2->coords.x >= 0 && current2->coords.x < GRID_COLS
			&& current2->coords.y >= 0 && current2->coords.y < GRID_ROWS)
			grid->cells[current2->coords.x][current2->coords.y].has_apple = SDL_FALSE;
		add_behind_snake_part(player2, SDL_TRUE);
		if (NB_APPLE_SPEED > player2->nb_apple_speed)
			player2->nb_apple_speed += 1;
		add_snake_score_anim(score_anims, player2->head_snake, SCORE_APPLE_EAT, player2->head_snake->skin);
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
