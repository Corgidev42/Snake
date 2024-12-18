#include "player.h"

void	init_players(t_user_data *player1, t_user_data *player2)
{
	int	i = 0;

	player1->id = 1;
	player1->is_ready = 0;
	player1->score = 0;
	player1->life = LIFE_MAX;
	player1->head_snake = malloc(sizeof(t_snake_part));
	if (!player1->head_snake)
		exit(1);
	player1->head_snake->coords.x = -1;
	player1->head_snake->coords.y = -1;
	player1->head_snake->orientation = UP;
	player1->head_snake->speed = BASE_SPEED;
	player1->head_snake->skin = 1;
	player1->head_snake->next = NULL;

	player2->id = 2;
	player2->is_ready = 0;
	player2->score = 0;
	player2->life = LIFE_MAX;
	player2->head_snake = malloc(sizeof(t_snake_part));
	if (!player2->head_snake)
		exit(1);
	player2->head_snake->coords.x = -1;
	player2->head_snake->coords.y = -1;
	player2->head_snake->orientation = UP;
	player2->head_snake->speed = BASE_SPEED;
	player2->head_snake->skin = 1;
	player2->head_snake->next = NULL;

	while (i < INVENTORY_SIZE)
	{
		player1->inventory[i] = BONUS_EMPTY;
		player2->inventory[i] = BONUS_EMPTY;
		i++;
	}
}

void free_players(t_user_data *player1, t_user_data *player2)
{
	t_snake_part *current;
	t_snake_part *next;

	current = player1->head_snake;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	player1->head_snake = NULL;

	current = player2->head_snake;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}
