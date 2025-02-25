#include "snake.h"

void	handle_speed(t_user_data *player)
{
	if (!player->is_speed && player->nb_apple_speed > 0)
	{
		player->is_speed = SDL_TRUE;
		player->speed = SCALE_SPEED;
	}
}

void	do_speed(t_user_data *player, int *gametick)
{
	if (*gametick <= 0)
	{
		*gametick += SNAKE_SPEED_TIME;
		if (player->is_speed)
		{
			player->nb_apple_speed -= 1;
			if (player->nb_apple_speed == 0)
			{
				player->is_speed = SDL_FALSE;
				player->speed = BASE_SPEED;
			}
		}
	}
}

void	print_actions(SDL_Rect rect_pos, t_user_data player1, t_user_data player2)
{
	if(SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
		SDL_ExitWithError("print_actions : color in white");

	if(SDL_RenderDrawRect(App.renderer, &rect_pos))
		SDL_ExitWithError("print_actions : draw rect");

	// Print player 1 actions
	// Print player 1 speed -> jauge de vitesse en fonction de NB_APPLE_SPEED
	SDL_Rect speed_rect = {rect_pos.x + 20, rect_pos.y + 10, 50, 30};
	for (int i = 0; i < NB_APPLE_SPEED; i++)
	{
		int color[4] = {0, 0, 0, 255};
		if (player1.nb_apple_speed > i)
		{
			if (player1.head_snake->skin == YELLOW)
			{
				color[0] = 255;
				color[1] = 255;
				color[2] = 0;
			}
			else if (player1.head_snake->skin == GREEN)
			{
				color[0] = 0;
				color[1] = 255;
				color[2] = 0;
			}
			else if (player1.head_snake->skin == BLUE)
			{
				color[0] = 0;
				color[1] = 0;
				color[2] = 255;
			}
		}
		if(SDL_SetRenderDrawColor(App.renderer, color[0], color[1], color[2], color[3]))
			SDL_ExitWithError("print_actions : color");
		if(SDL_RenderFillRect(App.renderer, &speed_rect))
			SDL_ExitWithError("print_actions : fill rect");
		if(SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
			SDL_ExitWithError("print_actions : color in white");
		if(SDL_RenderDrawRect(App.renderer, &speed_rect))
			SDL_ExitWithError("print_actions : fill rect");
		speed_rect.x += 50;
	}

	// Print player 2 actions
	// Print player 2 speed -> jauge de vitesse en fonction de NB_APPLE_SPEED
	speed_rect.x = SCREEN_WIDTH - 20 - 50;
	speed_rect.y = rect_pos.y + 10;
	for (int i = 0; i < NB_APPLE_SPEED; i++)
	{
		int color[4] = {0, 0, 0, 255};
		if (player2.nb_apple_speed > i)
		{
			if (player2.head_snake->skin == YELLOW)
			{
				color[0] = 255;
				color[1] = 255;
				color[2] = 0;
			}
			else if (player2.head_snake->skin == GREEN)
			{
				color[0] = 0;
				color[1] = 255;
				color[2] = 0;
			}
			else if (player2.head_snake->skin == BLUE)
			{
				color[0] = 0;
				color[1] = 0;
				color[2] = 255;
			}
		}
		if(SDL_SetRenderDrawColor(App.renderer, color[0], color[1], color[2], color[3]))
			SDL_ExitWithError("print_actions : color in black");
		if(SDL_RenderFillRect(App.renderer, &speed_rect))
			SDL_ExitWithError("print_actions : fill rect");
		if(SDL_SetRenderDrawColor(App.renderer, 255, 255, 255, 255))
			SDL_ExitWithError("print_actions : color in black");
		if(SDL_RenderDrawRect(App.renderer, &speed_rect))
			SDL_ExitWithError("print_actions : fill rect");
		speed_rect.x -= 50;
	}
}