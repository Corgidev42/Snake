#include "../include/app.h"
#include "../include/structs.h"
#include "../include/defs.h"

void	menu_window(t_user_data *player1, t_user_data *player2)
{
	SDL_Rect	rect_left;
	SDL_Rect	rect_right;

	rect_left.x = 0, rect_left.y = 0, rect_left.h = SCREEN_HEIGHT, rect_left.w = SCREEN_WIDTH / 2;
	rect_right.x = 0, rect_right.y = 0, rect_right.h = SCREEN_HEIGHT, rect_right.w = SCREEN_WIDTH / 2;

	while (App.running && !player1->is_ready && !player2->is_ready)
	{
		SDL_RenderClear(App.renderer);

		do_input(player1, player2);

		print_player_choice(rect_left, player1);
		print_player_choice(rect_left, player2);

		SDL_RenderPresent(App.renderer);
	}
}
