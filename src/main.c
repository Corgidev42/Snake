#include "app.h"
#include "game.h"
#include "menu.h"
#include "structs.h"



static void	init_players(t_user_data *player1, t_user_data *player2)
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
	player1->head_snake->speed = BASE_SPEED;
	player1->head_snake->skin = 1;
	player1->head_snake->next = NULL;

	player2->id = 1;
	player2->is_ready = 0;
	player2->score = 0;
	player2->life = LIFE_MAX;
	player2->head_snake = malloc(sizeof(t_snake_part));
	if (!player2->head_snake)
	{
		free(player1->head_snake);
		exit(1);
	}
	player2->head_snake->coords.x = -1;
	player2->head_snake->coords.y = -1;
	player2->head_snake->speed = BASE_SPEED;
	player2->head_snake->skin = 1;
	player2->head_snake->next = NULL;

	while (i < INVENTORY_SIZE)
	{
		player1->inventory[i] = EMPTY;
		player2->inventory[i] = EMPTY;
		i++;
	}
}

static void	free_players(t_user_data player1, t_user_data player2);

int	main(int argc, char const *argv[])
{
	t_user_data	player1;
	t_user_data	player2;

	init_app();
	while (App.running)
	{
		init_players(&player1, &player2);
		menu_window(&player1, &player2);
		game_window(player1, player2);
	}
	free_players(player1, player2);
	kill_app();
	return (0);
}
