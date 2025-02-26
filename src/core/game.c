#include "snake_together.h"

void	game_window(t_user_data player1, t_user_data player2)
{
	t_grid			grid;
	t_gametick		gametick;
	SDL_Rect		scoreboard_rect_pos = {SCOREBOARD_POS_X, SCOREBOARD_POS_Y, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT};
	SDL_Rect		actions_rect_pos = {ACTIONS_POS_X, ACTIONS_POS_Y, ACTIONS_WIDTH, ACTIONS_HEIGHT};
	SDL_Rect		grid_rect_pos = {GRID_POS_X, GRID_POS_Y, GRID_WIDTH, GRID_HEIGHT};

	init_map(&grid);
	spawn_snake(&grid, &player1);
	spawn_snake(&grid, &player2);
	init_gametick(&gametick);

	countdown_transition(grid, player1, player2, &gametick, actions_rect_pos, scoreboard_rect_pos);

	while (App.running && player1.life && player2.life)
	{
		update_gametick(&gametick, &player1, &player2);
		if (SDL_SetRenderDrawColor(App.renderer, 0, 0, 0, 255))
			SDL_ExitWithError("Color set in black");
		if (SDL_RenderClear(App.renderer))
			SDL_ExitWithError("Render clear");

		do_input(&player1, &player2);

		died_animation(&grid, &gametick.snake_1_died_cooldown, &player1);
		died_animation(&grid, &gametick.snake_2_died_cooldown, &player2);

		move_snake(&grid, &gametick.snake_1_cooldown, &player1);
		move_snake(&grid, &gametick.snake_2_cooldown, &player2);

		do_actions(&player1, &player2, &gametick);
		do_collision(&grid, &player1, &player2);
		if (!player1.life || !player2.life)
			break ;

		generate_apple(&grid, &gametick.apple_cooldown);
		generate_object(&grid, &gametick.object_cooldown);

		print_grid(grid);
		print_snake(grid, player1.head_snake, gametick.snakes_animation);
		print_snake(grid, player2.head_snake, gametick.snakes_animation);
		print_obstacles(grid);
		print_is_pending(grid, gametick.object_cooldown);
		print_actions(actions_rect_pos, player1, player2);
		print_scoreboard(scoreboard_rect_pos, player1, player2);

		SDL_RenderPresent(App.renderer);
		SDL_Delay(1000 / 60);
	}
}
