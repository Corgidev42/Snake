#include "app.h"
#include "game.h"
#include "player.h"
#include "menu.h"
#include "structs.h"

t_app App;

int	main(int argc, char const *argv[])
{
	t_user_data	player1;
	t_user_data	player2;

	init_app();
	while (App.running)
	{
		init_players(&player1, &player2);
		//menu_window(&player1, &player2);
		game_window(player1, player2);
	}
	free_players(&player1, &player2);
	kill_app();
	return (0);
}
