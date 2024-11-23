#include "../include/app.h"
#include "../include/defs.h"
#include "../include/structs.h"

static free_all_game(t_grid grid);

void	game_window(t_user_data player1, t_user_data player2)
{
	t_grid		grid;
	t_gametick	gametick;
	SDL_Rect	scoreboard_rect_pos;

	scoreboard_rect_pos.x = SCOREBOARD_POS_X; scoreboard_rect_pos.y = SCOREBOARD_POS_Y; scoreboard_rect_pos.h = SCREEN_HEIGHT - (CONTAINER_MARGING * 2) ; scoreboard_rect_pos.w = SCREEN_WIDTH - (CONTAINER_MARGING * 2);
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
		print_snake(grid, player1.head_snake);
		print_snake(grid, player2.head_snake);

		print_scoreboard(scoreboard_rect_pos, player1, player2);

		SDL_RenderPresent(App.renderer);
	}
	free_all_game(grid);
}
