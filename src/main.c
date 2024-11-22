#include "../include/app.h"
#include "../include/game.h"
#include "../include/menu.h"
#include "../include/structs.h"

static void	init_players(t_user_data *player1, t_user_data *player2);

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
	kill_app();
	return (0);
}
