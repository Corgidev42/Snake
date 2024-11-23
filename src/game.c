#include "../include/app.h"
#include "../include/defs.h"
#include "../include/structs.h"

void	game_window(t_user_data player1, t_user_data player2)
{
	t_grid		grid;
	t_gametick	gametick;

	init_map(&grid);
	spawn_snake(grid, &player1.head_snake);
	spawn_snake(grid, &player2.head_snake);
	init_gametick(&gametick);
	while (App.running && player1.life && player2.life)
	{
		update_gametick(&gametick);
		SDL_RenderClear(App.renderer);

		do_input(&player1, &player2);

		move_snake(&gametick.snake_1_cooldown, &player1.head_snake);
		move_snake(&gametick.snake_2_cooldown, &player2.head_snake);

		do_collision(grid, &player1, &player2);

		generate_apple(&grid, &gametick.apple_cooldown);
		generate_object(&grid,&gametick.object_cooldown);

		print_grid(grid);
		print_snake(grid, player1);
		print_snake(grid, player2);
		print_objets(grid);

		print_scoreboard(player1, player2);

		SDL_RenderPresent(App.renderer);
	}
}
