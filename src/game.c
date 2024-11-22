#include "../include/app.h"
#include "../include/defs.h"
#include "../include/structs.h"

void	game_window(t_user_data player1, t_user_data player2)
{
	t_grid		grid;
	t_gametick	gametick;

	init_map(&grid);
	spawn_snake(grid, player1.head_snake, player2.head_snake);
	init_gametick(&gametick);
	while (App.running && player1.life && player2.life)
	{
		SDL_RenderClear(App.renderer);

		do_input(&player1, &player2);

		move_snake(&player1);
		move_snake(&player2);

		do_collision(grid, &player1, &player2);

		update_gametick(&gametick);
		generate_apple(grid, gametick);
		generate_object(grid, gametick);

		print_snake(grid, player1);
		print_snake(grid, player2);
		print_objets(grid);

		print_scoreboard(player1, player2);

		SDL_RenderPresent(App.renderer);
	}
}
